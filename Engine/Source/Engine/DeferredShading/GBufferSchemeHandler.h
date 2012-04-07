#pragma once

#include "Engine/DeferredShading/GBufferMaterialGenerator.h"

class GBufferSchemeHandler :
            public Ogre::MaterialManager::Listener {
public:
    virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend);

protected:
    struct PassProperties {
        PassProperties() : isDeferred(true), normalMap(0), isSkinned(false) { }

        bool isDeferred;
        Ogre::vector<Ogre::TextureUnitState*>::type regularTextures;
        Ogre::TextureUnitState* normalMap;
        bool isSkinned;
        bool hasDiffuseColour;
    };

    PassProperties inspectPass(Ogre::Pass* pass, unsigned short lodIndex, const Ogre::Renderable* rend);
    MaterialGenerator::Perm getPermutation(const PassProperties& props);
    void fillPass(Ogre::Pass* gBufferPass, Ogre::Pass* originalPass, const PassProperties& props);
    bool checkNormalMap(Ogre::TextureUnitState* tus, PassProperties& props);

    GBufferMaterialGenerator materialGenerator;

    static const Ogre::String normalMapPattern;
};
