#pragma once

#include <OgreMaterialManager.h>

class NullSchemeHandler :
            public Ogre::MaterialManager::Listener {
public:
    virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend);
};