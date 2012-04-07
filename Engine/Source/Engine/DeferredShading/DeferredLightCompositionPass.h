#pragma once

#include <OgreCompositorInstance.h>
#include <OgreCustomCompositionPass.h>

class DeferredLightCompositionPass :
            public Ogre::CustomCompositionPass {
public:
    virtual ~DeferredLightCompositionPass() { }

    virtual Ogre::CompositorInstance::RenderSystemOperation* createOperation(Ogre::CompositorInstance* instance, const Ogre::CompositionPass* pass);
};