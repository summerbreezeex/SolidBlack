#pragma once

#include <OgreCompositorInstance.h>

#include "Engine/StlCommon.h"

class SsaoListener :
            public Ogre::CompositorInstance::Listener {
public:
    SsaoListener(Ogre::CompositorInstance* instance);

    void notifyMaterialRender(Ogre::uint32 passId, Ogre::MaterialPtr& material);

private:
    Ogre::CompositorInstance* instance;
};