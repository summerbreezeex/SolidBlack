#include <Ogre.h>

#include "Engine/DeferredShading/AmbientLight.h"
#include "Engine/DeferredShading/DeferredLight.h"
#include "Engine/DeferredShading/LightMaterialGenerator.h"

#include "DeferredLightRenderOperation.h"

DeferredLightRenderOperation::DeferredLightRenderOperation(Ogre::CompositorInstance* instance, const Ogre::CompositionPass* pass) {
    viewport = instance->getChain()->getViewport();

    const Ogre::CompositionPass::InputTex& input0 = pass->getInput(0);
    texName0 = instance->getTextureInstanceName(input0.name, input0.mrtIndex);
    const Ogre::CompositionPass::InputTex& input1 = pass->getInput(1);
    texName1 = instance->getTextureInstanceName(input1.name, input1.mrtIndex);

    materialGenerator = new LightMaterialGenerator();

    ambientLight = new AmbientLight();
    ambientLight->getMaterial()->load();
}

DeferredLightRenderOperation::~DeferredLightRenderOperation() {
    for (auto it = lights.begin(); it != lights.end(); ++it) {
        delete it->second;
    }
    lights.clear();

    delete ambientLight;
    delete materialGenerator;
}

DeferredLight* DeferredLightRenderOperation::createDeferredLight(Ogre::Light* light) {
    DeferredLight* deferredLight = new DeferredLight(materialGenerator, light);
    lights[light] = deferredLight;
    return deferredLight;
}

void DeferredLightRenderOperation::execute(Ogre::SceneManager* sceneManager, Ogre::RenderSystem* renderSystem) {
    Ogre::Camera* camera = viewport->getCamera();

    ambientLight->updateFromCamera(camera);

    Ogre::Technique* technique = ambientLight->getMaterial()->getBestTechnique();
    injectTechnique(sceneManager, technique, ambientLight, 0);

    const Ogre::LightList& lightList = sceneManager->_getLightsAffectingFrustum();
    foreach (it, lightList) {
        Ogre::Light* light = *it;
        Ogre::LightList ll;
        ll.push_back(light);

        LightsMap::iterator dLightIt = lights.find(light);
        DeferredLight* dLight = 0;
        if (dLightIt == lights.end()) {
            dLight = createDeferredLight(light);
        } else {
            dLight = dLightIt->second;
            dLight->updateFromParent();
        }
        dLight->updateFromCamera(camera);
        technique = dLight->getMaterial()->getBestTechnique();

        // Update shadow texture
        if (dLight->getCastChadows()) {
            Ogre::SceneManager::RenderContext* context = sceneManager->_pauseRendering();

            sceneManager->prepareShadowTextures(camera, viewport, &ll);
            sceneManager->_resumeRendering(context);

            Ogre::Pass* pass = technique->getPass(0);
            Ogre::TextureUnitState* tus = pass->getTextureUnitState("ShadowMap");
            assert(tus);
            const Ogre::TexturePtr& shadowTex = sceneManager->getShadowTexture(0);
            if (tus->_getTexturePtr() != shadowTex) {
                tus->_setTexturePtr(shadowTex);
            }

        }

        injectTechnique(sceneManager, technique, dLight, &ll);
    }
}

void DeferredLightRenderOperation::injectTechnique(Ogre::SceneManager* sceneManager, Ogre::Technique* technique, Ogre::Renderable* renderable, const Ogre::LightList* lightList) {
    for (unsigned short i = 0; i < technique->getNumPasses(); ++i) {
        Ogre::Pass* pass = technique->getPass(i);

        if (lightList != 0) {
            sceneManager->_injectRenderWithPass(pass, renderable, false, false, lightList);
        } else {
            sceneManager->_injectRenderWithPass(pass, renderable, false);
        }
    }
}