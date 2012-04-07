#include "Engine/DeferredShading/SsaoListener.h"

#include "SsaoCompositorLogic.h"

Ogre::CompositorInstance::Listener* SsaoCompositorLogic::createListener(Ogre::CompositorInstance* instance) {
    return new SsaoListener(instance);
}
