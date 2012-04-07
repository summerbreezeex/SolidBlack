#include <OgreTechnique.h>

#include "NullSchemeHandler.h"

Ogre::Technique* NullSchemeHandler::handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend) {
    Ogre::Technique* emptyTech = originalMaterial->createTechnique();
    emptyTech->removeAllPasses();
    emptyTech->setSchemeName(schemeName);

    return emptyTech;
}