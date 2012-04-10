#pragma once

#include "Engine/Noise/NoiseModule.h"

class SimplexNoise :
            public NoiseModule {
public:
    SimplexNoise();
    SimplexNoise(int seed, Ogre::Real scale);

    Ogre::Real getValue(const Ogre::Vector3& position) const;

    void initialize();

private:
    static Ogre::Real dot(int g[], Ogre::Real x, Ogre::Real y, Ogre::Real z);
    static __forceinline int __stdcall fastFloor(Ogre::Real x);

    int permTable[512];
};