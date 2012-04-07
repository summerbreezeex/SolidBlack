#pragma once

#include "Engine/Noise/NoiseFunction.h"

class NoiseOperator :
            public NoiseFunction {
public:
    virtual ~NoiseOperator() { }

    virtual Ogre::Real getValue(const Ogre::Vector3& position) const = 0;
};