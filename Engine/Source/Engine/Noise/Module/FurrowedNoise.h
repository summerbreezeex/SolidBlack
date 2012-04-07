#pragma once

#include "Engine/Noise/Module/SimplexNoise.h"

class FurrowedNoise :
            public NoiseModule {
public:
    FurrowedNoise();
    FurrowedNoise(int seed, Ogre::Real scale, int octaveCount, Ogre::Real frequency, Ogre::Real lacunarity);

    Ogre::Real getValue(const Ogre::Vector3& position) const;

    int getOctaveCount() const;
    void setOctaveCount(int octaveCount);

    Ogre::Real getFrequency() const;
    void setFrequency(Ogre::Real frequency);

    Ogre::Real getLacunarity() const;
    void setLacunarity(Ogre::Real lacunarity);

    void initialise();

private:
    int octaveCount;

    Ogre::Real frequency;
    Ogre::Real lacunarity;

    std::vector<Ogre::Real> spectralWeights;

    std::vector<SimplexNoise> coherentNoises;
};