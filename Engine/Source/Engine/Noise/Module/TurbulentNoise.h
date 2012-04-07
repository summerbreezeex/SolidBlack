#pragma once

#include "Engine/Noise/NoiseModule.h"
#include "Engine/Noise/RandomSequence.h"
#include "Engine/Noise/Module/SimplexNoise.h"

class TurbulentNoise :
            public NoiseModule {
public:
    TurbulentNoise();
    TurbulentNoise(int seed, Ogre::Real scale, int octaveCount, Ogre::Real persistance);

    Ogre::Real getValue(const Ogre::Vector3& position) const;

    int getOctaveCount() const;
    void setOctaveCount(int octaveCount);

    Ogre::Real getPersistance() const;
    void setPersistance(Ogre::Real persistance);

    void initialise();

private:
    int octaveCount;
    Ogre::Real persistance;

    SimplexNoise noise;
};