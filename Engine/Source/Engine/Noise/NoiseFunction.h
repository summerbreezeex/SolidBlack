#pragma once

#include <OgreVector3.h>

#include "Engine/StlCommon.h"

class NoiseFunction {
public:
    virtual ~NoiseFunction() { }

    virtual Ogre::Real getValue(const Ogre::Vector3& position) const = 0;
};

typedef std::shared_ptr<NoiseFunction> NoiseFunctionPtr;