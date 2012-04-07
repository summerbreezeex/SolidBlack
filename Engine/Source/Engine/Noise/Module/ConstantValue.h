#pragma once

#include "Engine/Noise/NoiseModule.h"

class ConstantValue :
            public NoiseModule {
public:
    ConstantValue();
    ConstantValue(Ogre::Real value);

    Ogre::Real getValue(const Ogre::Vector3& position) const;
    void setValue(Ogre::Real value);

private:
    Ogre::Real value;
};