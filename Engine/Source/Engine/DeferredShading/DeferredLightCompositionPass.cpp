#include "Engine/DeferredShading/DeferredLightRenderOperation.h"

#include "DeferredLightCompositionPass.h"

Ogre::CompositorInstance::RenderSystemOperation* DeferredLightCompositionPass::createOperation(Ogre::CompositorInstance* instance, const Ogre::CompositionPass* pass) {
    return new DeferredLightRenderOperation(instance, pass);
}