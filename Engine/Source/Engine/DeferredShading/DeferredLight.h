#pragma once

#include <OgreSimpleRenderable.h>

#include "Engine/StlCommon.h"

class MaterialGenerator;

class DeferredLight :
            public Ogre::SimpleRenderable {
public:
    DeferredLight(MaterialGenerator* generator, Ogre::Light* parentLight);
    ~DeferredLight();

    void updateFromParent();
    void updateFromCamera(Ogre::Camera* camera);

    virtual bool getCastChadows() const;

    virtual Ogre::Real getBoundingRadius() const;
    virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* camera) const;
    virtual const Ogre::MaterialPtr& getMaterial() const;
    virtual void getWorldTransforms(Ogre::Matrix4* transform) const;

private:
    bool isCameraInsideLight(Ogre::Camera* camera);

    void rebuildGeometry(Ogre::Real radius);
    void createSphere(Ogre::Real radius, int numRings, int numSegments);
    void createRectangle2D();
    void createCone(Ogre::Real radius, Ogre::Real height, int numVerticesInBase);
    void setAttenuation(Ogre::Real c, Ogre::Real b, Ogre::Real a);
    void setSpecularColour(const Ogre::ColourValue& colour);

    Ogre::Light* parentLight;

    bool ignoreWorld;
    Ogre::Real radius;
    MaterialGenerator* generator;
    Ogre::uint32 permutation;
};
