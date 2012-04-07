#pragma once

#include <OgreSimpleRenderable.h>

#include "Engine/StlCommon.h"

class AmbientLight :
            public Ogre::SimpleRenderable {
public:
    AmbientLight();
    ~AmbientLight();

    virtual Ogre::Real getBoundingRadius() const;
    virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* camera) const;
    virtual const Ogre::MaterialPtr& getMaterial() const;
    virtual void getWorldTransforms(Ogre::Matrix4* transform) const;

    void updateFromCamera(Ogre::Camera* camera);

private:
    Ogre::Real radius;
    Ogre::MaterialPtr material;
};
