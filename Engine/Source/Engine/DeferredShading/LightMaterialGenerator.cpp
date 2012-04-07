#pragma once

#include <OgreStringConverter.h>
#include <OgreException.h>
#include <OgreMaterialManager.h>

#include <OgrePass.h>
#include <OgreTechnique.h>

#include <OgreHighLevelGpuProgram.h>
#include <OgreHighLevelGpuProgramManager.h>

#include "Engine/DeferredShading/DeferredLight.h"

#include "LightMaterialGenerator.h"

LightMaterialGenerator::LightMaterialGenerator() {
    vertexShaderMask = 0x00000004;
    fragmentShaderMask = 0x0000003F;
    materialMask = LightMaterialGenerator::MI_DIRECTIONAL | LightMaterialGenerator::MI_SHADOW_CASTER;

    materialBaseName = "DeferredShading/LightMaterial/";
    impl = new LightMaterialGeneratorCG("DeferredShading/LightMaterial/");
}

LightMaterialGeneratorCG::LightMaterialGeneratorCG(const Ogre::String &baseName):
        baseName(baseName) {
}

Ogre::GpuProgramPtr LightMaterialGeneratorCG::generateVertexShader(Perm permutation) {
    Ogre::String programName = "DeferredShading/post/";

    if (permutation & LightMaterialGenerator::MI_DIRECTIONAL) {
        programName += "vs";
    } else {
        programName += "LightMaterial_vs";
    }

    Ogre::GpuProgramPtr ptr = Ogre::HighLevelGpuProgramManager::getSingleton().getByName(programName);
    assert(!ptr.isNull());
    return ptr;
}

Ogre::GpuProgramPtr LightMaterialGeneratorCG::generateFragmentShader(Perm permutation) {
    if (masterSource.empty()) {
        Ogre::DataStreamPtr masterSourcePtr = Ogre::ResourceGroupManager::getSingleton().openResource("DeferredShading/post/LightMaterial_ps.cg");
        assert(!masterSourcePtr.isNull());
        masterSource = masterSourcePtr->getAsString();
    }

    assert(!masterSource.empty());

    Ogre::String name = baseName + Ogre::StringConverter::toString(permutation) + "_ps";

    Ogre::HighLevelGpuProgramPtr programPtr =
        Ogre::HighLevelGpuProgramManager::getSingleton().createProgram(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "cg", Ogre::GPT_FRAGMENT_PROGRAM);

    programPtr->setSource(masterSource);
    programPtr->setParameter("entry_point", "main");
    programPtr->setParameter("profiles", "ps_2_x arbfp1");

    programPtr->setParameter("compile_arguments", getPPDefines(permutation));

    setUpBaseParameters(programPtr->getDefaultParameters());

    return Ogre::GpuProgramPtr(programPtr);
}

Ogre::MaterialPtr LightMaterialGeneratorCG::generateTemplateMaterial(Perm permutation) {
    Ogre::String materialName = baseName;

    if (permutation & LightMaterialGenerator::MI_DIRECTIONAL) {
        materialName += "Quad";
    } else {
        materialName += "Geometry";
    }

    if (permutation & LightMaterialGenerator::MI_SHADOW_CASTER) {
        materialName += "Shadow";
    }
    return Ogre::MaterialManager::getSingleton().getByName(materialName);
}

Ogre::String LightMaterialGeneratorCG::getPPDefines(Perm permutation) {
    Ogre::String strPPD;

    // Get the type of light.
    Ogre::String lightType;
    if (permutation & LightMaterialGenerator::MI_POINT) {
        lightType = "POINT";
    } else if (permutation & LightMaterialGenerator::MI_SPOTLIGHT) {
        lightType = "SPOT";
    } else if (permutation & LightMaterialGenerator::MI_DIRECTIONAL) {
        lightType = "DIRECTIONAL";
    } else {
        assert(false && "Permutation must have a light type");
    }

    strPPD += "-DLIGHT_TYPE=LIGHT_" + lightType + " ";

    // Optional parameters.
    if (permutation & LightMaterialGenerator::MI_SPECULAR) {
        strPPD += "-DIS_SPECULAR ";
    }
    if (permutation & LightMaterialGenerator::MI_ATTENUATED) {
        strPPD += "-DIS_ATTENUATED ";
    }
    if (permutation & LightMaterialGenerator::MI_SHADOW_CASTER) {
        strPPD += "-DIS_SHADOW_CASTER ";
    }
    return strPPD;
}

void LightMaterialGeneratorCG::setUpBaseParameters(const Ogre::GpuProgramParametersSharedPtr& params) {
    assert(!params.isNull());

    struct AutoParamPair {
        Ogre::String name;
        Ogre::GpuProgramParameters::AutoConstantType type;
    };

    static const AutoParamPair autoParams[] = {
        { "vpWidth",            Ogre::GpuProgramParameters::ACT_VIEWPORT_WIDTH },
        { "vpHeight",            Ogre::GpuProgramParameters::ACT_VIEWPORT_HEIGHT },
        { "worldView",            Ogre::GpuProgramParameters::ACT_WORLDVIEW_MATRIX },
        { "invProj",            Ogre::GpuProgramParameters::ACT_INVERSE_PROJECTION_MATRIX },
        { "invView",            Ogre::GpuProgramParameters::ACT_INVERSE_VIEW_MATRIX },
        { "flip",                Ogre::GpuProgramParameters::ACT_RENDER_TARGET_FLIPPING },
        { "lightDiffuseColor",    Ogre::GpuProgramParameters::ACT_LIGHT_DIFFUSE_COLOUR },
        { "lightSpecularColor", Ogre::GpuProgramParameters::ACT_LIGHT_SPECULAR_COLOUR },
        { "lightFalloff",        Ogre::GpuProgramParameters::ACT_LIGHT_ATTENUATION },
        { "lightPos",            Ogre::GpuProgramParameters::ACT_LIGHT_POSITION_VIEW_SPACE },
        { "lightDir",            Ogre::GpuProgramParameters::ACT_LIGHT_DIRECTION_VIEW_SPACE },
        { "spotParams",            Ogre::GpuProgramParameters::ACT_SPOTLIGHT_PARAMS },
        { "farClipDistance",    Ogre::GpuProgramParameters::ACT_FAR_CLIP_DISTANCE },
        { "shadowViewProjMat",    Ogre::GpuProgramParameters::ACT_TEXTURE_VIEWPROJ_MATRIX }
    };
    int numParams = sizeof(autoParams) / sizeof(AutoParamPair);

    for (int i = 0; i < numParams; i++) {
        if (params->_findNamedConstantDefinition(autoParams[i].name)) {
            params->setNamedAutoConstant(autoParams[i].name, autoParams[i].type);
        }
    }
}
