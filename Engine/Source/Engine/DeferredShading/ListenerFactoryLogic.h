#pragma once

#include "Engine/StlCommon.h"

#include <OgreCompositorInstance.h>
#include <OgreCompositorLogic.h>

class ListenerFactoryLogic :
            public Ogre::CompositorLogic {
public:
    virtual void compositorInstanceCreated(Ogre::CompositorInstance* newInstance);
    virtual void compositorInstanceDestroyed(Ogre::CompositorInstance* destroyedInstance);

protected:
    virtual Ogre::CompositorInstance::Listener* createListener(Ogre::CompositorInstance* instance) = 0;

private:
    typedef std::map<Ogre::CompositorInstance*, Ogre::CompositorInstance::Listener*> ListenerMap;
    ListenerMap listeners;
};
