#pragma once

#include <OgreCompositorInstance.h>

#include "Engine/StlCommon.h"

class AmbientLight;
class DeferredLight;
class MaterialGenerator;

class DeferredLightRenderOperation :
            public Ogre::CompositorInstance::RenderSystemOperation {
public:
    DeferredLightRenderOperation(Ogre::CompositorInstance* instance, const Ogre::CompositionPass* pass);
    virtual ~DeferredLightRenderOperation();

    virtual void execute(Ogre::SceneManager* sceneManager, Ogre::RenderSystem* renderSystem);

private:
    static void injectTechnique(Ogre::SceneManager* sceneManager, Ogre::Technique* technique, Ogre::Renderable* renderable, const Ogre::LightList* lightList);

    DeferredLight* createDeferredLight(Ogre::Light* light);

    std::string texName0;
    std::string texName1;

    MaterialGenerator* materialGenerator;

    typedef std::map<Ogre::Light*, DeferredLight*> LightsMap;
    LightsMap lights;

    AmbientLight* ambientLight;

    Ogre::Viewport* viewport;
};