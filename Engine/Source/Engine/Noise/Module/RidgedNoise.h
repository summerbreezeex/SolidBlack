#pragma once

#include "Engine/Noise/Module/SimplexNoise.h"

class RidgedNoise :
            public NoiseModule {
public:
    RidgedNoise();
    RidgedNoise(int seed, Ogre::Real scale, int octaveCount, Ogre::Real lacunarity, Ogre::Real gain);

    Ogre::Real getValue(const Ogre::Vector3& position) const;

    int getOctaveCount() const;
    void setOctaveCount(int octaveCount);

    Ogre::Real getLacunarity() const;
    void setLacunarity(Ogre::Real lacunarity);

    Ogre::Real getGain() const;
    void setGain(Ogre::Real gain);

    void initialize();

private:
    int octaveCount;

    Ogre::Real lacunarity;
    Ogre::Real gain;

    std::vector<SimplexNoise> noises;
};