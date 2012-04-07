#include <OgreMaterialManager.h>
#include <OgreTechnique.h>

#include "GBufferSchemeHandler.h"

const Ogre::String GBufferSchemeHandler::normalMapPattern = "normal";

Ogre::Technique* GBufferSchemeHandler::handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend) {
    Ogre::MaterialManager& matMgr = Ogre::MaterialManager::getSingleton();
    Ogre::String curSchemeName = matMgr.getActiveScheme();
    matMgr.setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
    Ogre::Technique* originalTechnique = originalMaterial->getBestTechnique(lodIndex, rend);
    matMgr.setActiveScheme(curSchemeName);

    Ogre::Technique* gBufferTech = originalMaterial->createTechnique();
    gBufferTech->removeAllPasses();
    gBufferTech->setSchemeName(schemeName);

    Ogre::Technique* noGBufferTech = originalMaterial->createTechnique();
    noGBufferTech->removeAllPasses();
    noGBufferTech->setSchemeName("NoGBuffer");

    for (unsigned short i=0; i<originalTechnique->getNumPasses(); i++) {
        Ogre::Pass* originalPass = originalTechnique->getPass(i);
        PassProperties props = inspectPass(originalPass, lodIndex, rend);

        if (!props.isDeferred) {
            Ogre::Pass* clonePass = noGBufferTech->createPass();
            *clonePass = *originalPass;
            continue;
        }

        Ogre::Pass* newPass = gBufferTech->createPass();
        MaterialGenerator::Perm perm = getPermutation(props);

        const Ogre::MaterialPtr& templateMat = materialGenerator.getMaterial(perm);

        *newPass = *(templateMat->getTechnique(0)->getPass(0));
        fillPass(newPass, originalPass, props);
    }

    return gBufferTech;
}

bool GBufferSchemeHandler::checkNormalMap(Ogre::TextureUnitState* tus, GBufferSchemeHandler::PassProperties& props) {
    bool isNormal = false;
    Ogre::String lowerCaseAlias = tus->getTextureNameAlias();
    Ogre::StringUtil::toLowerCase(lowerCaseAlias);
    if (lowerCaseAlias.find(normalMapPattern) != Ogre::String::npos) {
        isNormal = true;
    } else {
        Ogre::String lowerCaseName = tus->getTextureName();
        Ogre::StringUtil::toLowerCase(lowerCaseName);
        if (lowerCaseName.find(normalMapPattern) != Ogre::String::npos) {
            isNormal = true;
        }
    }

    if (isNormal) {
        if (props.normalMap == 0) {
            props.normalMap = tus;
        } else {
            OGRE_EXCEPT(Ogre::Exception::ERR_DUPLICATE_ITEM, "Multiple normal map patterns matches", "GBufferSchemeHandler::inspectPass");
        }
    }
    return isNormal;
}

GBufferSchemeHandler::PassProperties GBufferSchemeHandler::inspectPass(Ogre::Pass* pass, unsigned short lodIndex, const Ogre::Renderable* rend) {
    PassProperties props;

    if (pass->hasVertexProgram()) {
        props.isSkinned = pass->getVertexProgram()->isSkeletalAnimationIncluded();
    } else {
        props.isSkinned = false;
    }

    for (unsigned short i=0; i<pass->getNumTextureUnitStates(); i++) {
        Ogre::TextureUnitState* tus = pass->getTextureUnitState(i);
        if (!checkNormalMap(tus, props)) {
            props.regularTextures.push_back(tus);
        }
        if (tus->getEffects().size() > 0) {
            props.isDeferred = false;
        }

    }

    if (pass->getDiffuse() != Ogre::ColourValue::White) {
        props.hasDiffuseColour = true;
    }

    // Check transparency
    if (pass->getDestBlendFactor() != Ogre::SBF_ZERO) {
        props.isDeferred = false;
    }

    return props;
}

MaterialGenerator::Perm GBufferSchemeHandler::getPermutation(const PassProperties& props) {
    MaterialGenerator::Perm perm = 0;
    switch (props.regularTextures.size()) {
        case 0:
            perm |= GBufferMaterialGenerator::GBP_NO_TEXTURES;

            if (props.normalMap != 0) {
                perm |= GBufferMaterialGenerator::GBP_ONE_TEXCOORD;
            } else {
                perm |= GBufferMaterialGenerator::GBP_NO_TEXCOORDS;
            }
            break;
        case 1:
            perm |= GBufferMaterialGenerator::GBP_ONE_TEXTURE;
            perm |= GBufferMaterialGenerator::GBP_ONE_TEXCOORD;
            break;
        case 2:
            perm |= GBufferMaterialGenerator::GBP_TWO_TEXTURES;
            perm |= GBufferMaterialGenerator::GBP_ONE_TEXCOORD;
            break;
        case 3:
            perm |= GBufferMaterialGenerator::GBP_THREE_TEXTURES;
            perm |= GBufferMaterialGenerator::GBP_ONE_TEXCOORD;
            break;
        default:
            OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED, "Can not generate G-Buffer materials for '>3 regular-texture' objects", "GBufferSchemeHandler::inspectPass");
    }

    if (props.isSkinned) {
        perm |= GBufferMaterialGenerator::GBP_SKINNED;
    }

    if (props.normalMap != 0) {
        perm |= GBufferMaterialGenerator::GBP_NORMAL_MAP;
    }

    if (props.hasDiffuseColour) {
        perm |= GBufferMaterialGenerator::GBP_HAS_DIFFUSE_COLOUR;
    }
    return perm;
}

void GBufferSchemeHandler::fillPass(Ogre::Pass* gbufferPass, Ogre::Pass* originalPass, const PassProperties& props) {
    int texUnitIndex = 0;
    if (props.normalMap != 0) {
        *(gbufferPass->getTextureUnitState(texUnitIndex)) = *(props.normalMap);
        texUnitIndex++;
    }

    for (size_t i = 0; i < props.regularTextures.size(); i++) {
        *(gbufferPass->getTextureUnitState(texUnitIndex)) = *(props.regularTextures[i]);
        texUnitIndex++;
    }

    gbufferPass->setAmbient(originalPass->getAmbient());
    gbufferPass->setDiffuse(originalPass->getDiffuse());
    gbufferPass->setSpecular(originalPass->getSpecular());
    gbufferPass->setShininess(originalPass->getShininess());
    gbufferPass->setCullingMode(originalPass->getCullingMode());
    gbufferPass->setLightingEnabled(false);
}
