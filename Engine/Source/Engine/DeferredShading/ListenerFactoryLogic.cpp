#include "ListenerFactoryLogic.h"

void ListenerFactoryLogic::compositorInstanceCreated(Ogre::CompositorInstance* newInstance) {
    Ogre::CompositorInstance::Listener* listener = createListener(newInstance);
    newInstance->addListener(listener);
    listeners[newInstance] = listener;
}

void ListenerFactoryLogic::compositorInstanceDestroyed(Ogre::CompositorInstance* destroyedInstance) {
    delete listeners[destroyedInstance];
    listeners.erase(destroyedInstance);
}