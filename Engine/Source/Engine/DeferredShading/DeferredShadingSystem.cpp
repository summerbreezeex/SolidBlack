#include <OgreConfigFile.h>
#include <OgreStringConverter.h>
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgreRoot.h>
#include <OgreCompositor.h>
#include <OgreCompositorManager.h>
#include <OgreCompositorChain.h>
#include <OgreCompositorInstance.h>
#include <OgreLogManager.h>

#include "Engine/DeferredShading/DeferredLightCompositionPass.h"
#include "Engine/DeferredShading/DeferredLightRenderOperation.h"
#include "Engine/DeferredShading/GBufferSchemeHandler.h"
#include "Engine/DeferredShading/NullSchemeHandler.h"
#include "Engine/DeferredShading/SsaoCompositorLogic.h"

#include "DeferredShadingSystem.h"

const Ogre::uint8 DeferredShadingSystem::PRE_GBUFFER_RENDER_QUEUE = Ogre::RENDER_QUEUE_1;
const Ogre::uint8 DeferredShadingSystem::POST_GBUFFER_RENDER_QUEUE = Ogre::RENDER_QUEUE_8;

DeferredShadingSystem::DeferredShadingSystem(Ogre::Viewport* viewport, Ogre::SceneManager* sceneManager, Ogre::Camera* camera) :
        viewport(viewport),
        sceneManager(sceneManager),
        camera(camera),
        gbufferSchemeHandler(nullptr),
        nullSchemeHandler(nullptr),
        ssaoCompositorLogic(nullptr),
        deferredLightCompositionPass(nullptr),
        activeFlag(false),
        ssaoFlag(false),
        currentMode(DSM_SHOWLIT) {
    sceneManager->setShadowTextureCasterMaterial("DeferredShading/Shadows/Caster");
    sceneManager->setShadowFarDistance(150);
    sceneManager->setShadowTextureSize(512);
    sceneManager->setShadowTextureCount(1);
    sceneManager->setShadowTexturePixelFormat(Ogre::PF_FLOAT16_R);
    sceneManager->setShadowDirectionalLightExtrusionDistance(75);
}

void DeferredShadingSystem::initialize() {
    for (int i = 0; i < DSM_COUNT; ++i) {
        instances[i] = 0;
    }

    createResources();

    setActive(true);
}

void DeferredShadingSystem::cleanUp() {
    Ogre::CompositorManager* compositorManager = Ogre::CompositorManager::getSingletonPtr();
    Ogre::CompositorChain* chain = compositorManager->getCompositorChain(viewport);

    for (int i = 0; i < DSM_COUNT; ++i) {
        chain->_removeInstance(instances[i]);
    }

    compositorManager->removeCompositorChain(viewport);

    Ogre::MaterialManager* materialManager = Ogre::MaterialManager::getSingletonPtr();
    materialManager->removeListener(gbufferSchemeHandler, "GBuffer");
    materialManager->removeListener(nullSchemeHandler, "NoGBuffer");
    delete gbufferSchemeHandler;
    delete nullSchemeHandler;

    delete ssaoCompositorLogic;
    delete deferredLightCompositionPass;
}

void DeferredShadingSystem::setMode(DSMode mode) {
    assert(0 <= mode && mode < DSM_COUNT);

    if (currentMode == mode && instances[mode]->getEnabled() == activeFlag) {
        return;
    }

    for (int i = 0; i < DSM_COUNT; ++i) {
        if (i == mode) {
            instances[i]->setEnabled(activeFlag);
        } else {
            instances[i]->setEnabled(false);
        }
    }

    currentMode = mode;

    ssaoInstances->setEnabled(activeFlag && ssaoFlag && currentMode == DSM_SHOWLIT);
}

void DeferredShadingSystem::setSsao(bool ssaoFlag) {
    if (this->ssaoFlag != ssaoFlag) {
        this->ssaoFlag = ssaoFlag;
        if (activeFlag && currentMode == DSM_SHOWLIT) {
            ssaoInstances->setEnabled(ssaoFlag);
        }
    }
}

bool DeferredShadingSystem::getSsao() const {
    return ssaoFlag;
}

void DeferredShadingSystem::setActive(bool activeFlag) {
    if (this->activeFlag != activeFlag) {
        this->activeFlag = activeFlag;
        gbufferInstances->setEnabled(activeFlag);

        setMode(currentMode);
    }
}

DeferredShadingSystem::DSMode DeferredShadingSystem::getMode() const {
    return currentMode;
}

void DeferredShadingSystem::createResources() {
    Ogre::CompositorManager* compositorManager = Ogre::CompositorManager::getSingletonPtr();
    Ogre::MaterialManager* materialManager = Ogre::MaterialManager::getSingletonPtr();

    // Hook up the compositor logic and scheme handlers.
    gbufferSchemeHandler = new GBufferSchemeHandler();
    nullSchemeHandler = new NullSchemeHandler();

    materialManager->addListener(gbufferSchemeHandler, "GBuffer");
    materialManager->addListener(nullSchemeHandler, "NoGBuffer");

    ssaoCompositorLogic = new SsaoCompositorLogic();
    deferredLightCompositionPass = new DeferredLightCompositionPass();

    compositorManager->registerCompositorLogic("SSAOLogic", ssaoCompositorLogic);
    compositorManager->registerCustomCompositionPass("DeferredLight", deferredLightCompositionPass);

    // Create the main GBuffer compositor.
    gbufferInstances = compositorManager->addCompositor(viewport, "DeferredShading/GBuffer");

    // Create filters.
    instances[DSM_SHOWLIT] = compositorManager->addCompositor(viewport, "DeferredShading/ShowLit");
    instances[DSM_SHOWNORMALS] = compositorManager->addCompositor(viewport, "DeferredShading/ShowNormals");
    instances[DSM_SHOWDSP] = compositorManager->addCompositor(viewport, "DeferredShading/ShowDepthSpecular");
    instances[DSM_SHOWCOLOUR] = compositorManager->addCompositor(viewport, "DeferredShading/ShowColour");

    ssaoInstances = compositorManager->addCompositor(viewport, "DeferredShading/SSAO");
}