#pragma once

#include "ListenerFactoryLogic.h"

class SsaoCompositorLogic :
            public ListenerFactoryLogic {
private:
    virtual Ogre::CompositorInstance::Listener* createListener(Ogre::CompositorInstance* instance);
};
