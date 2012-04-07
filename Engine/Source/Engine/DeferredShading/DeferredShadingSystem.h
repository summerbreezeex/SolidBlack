#pragma once

#include <OgreCompositorInstance.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreMaterial.h>
#include <OgreRenderTargetListener.h>

#include "Engine/StlCommon.h"

class GBufferSchemeHandler;
class NullSchemeHandler;
class SsaoCompositorLogic;
class DeferredLightCompositionPass;

class DeferredShadingSystem :
            public Ogre::RenderTargetListener {
public:
    enum DSMode {
        DSM_SHOWLIT = 0,
        DSM_SHOWCOLOUR = 1,
        DSM_SHOWNORMALS = 2,
        DSM_SHOWDSP = 3,
        DSM_COUNT = 4
    };

    static const Ogre::uint8 PRE_GBUFFER_RENDER_QUEUE;
    static const Ogre::uint8 POST_GBUFFER_RENDER_QUEUE;

    DeferredShadingSystem(Ogre::Viewport* viewport, Ogre::SceneManager* sceneManager, Ogre::Camera* camera);

    void initialize();
    void cleanUp();

    void setMode(DSMode mode);
    DSMode getMode() const;

    void setSsao(bool ssao);
    bool getSsao() const;

    void setActive(bool active);

protected:
    void createResources();

    Ogre::Viewport* viewport;
    Ogre::SceneManager* sceneManager;
    Ogre::Camera* camera;

    Ogre::CompositorInstance* gbufferInstances;

    Ogre::CompositorInstance* instances[DSM_COUNT];
    Ogre::CompositorInstance* ssaoInstances;

    GBufferSchemeHandler* gbufferSchemeHandler;
    NullSchemeHandler* nullSchemeHandler;

    SsaoCompositorLogic* ssaoCompositorLogic;
    DeferredLightCompositionPass* deferredLightCompositionPass;

    bool activeFlag;
    bool ssaoFlag;

    DSMode currentMode;
};