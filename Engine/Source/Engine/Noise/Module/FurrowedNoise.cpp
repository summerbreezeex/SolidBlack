#include <OgreMath.h>

#include "FurrowedNoise.h"

FurrowedNoise::FurrowedNoise() :
        octaveCount(5),
        frequency(1.0),
        lacunarity(2.0) {
}

FurrowedNoise::FurrowedNoise(int seed, Ogre::Real scale, int octaveCount, Ogre::Real frequency, Ogre::Real lacunarity) :
        NoiseModule(seed, scale),
        octaveCount(octaveCount),
        frequency(frequency),
        lacunarity(lacunarity) {
}

Ogre::Real FurrowedNoise::getValue(const Ogre::Vector3& position) const {
    assert(isInitialised());

    Ogre::Vector3 adjustedPosition(position * getScale() * frequency);

    Ogre::Real signal = 0.0, value = 0.0, weight = 1.0;
    Ogre::Real offset = 1.0, gain = 2.0;

    for (int i = 0; i < octaveCount; ++i) {
        signal = coherentNoises[i].getValue(adjustedPosition);

        signal = fabs(signal);
        signal = offset - signal;

        signal *= weight;
        signal *= weight;

        weight = Ogre::Math::Clamp(signal * gain, 0.0, 1.0);

        value += signal * spectralWeights[i];

        adjustedPosition = adjustedPosition * lacunarity;
    }

    return (value * 1.25) - 1.0;
}

int FurrowedNoise::getOctaveCount() const {
    return octaveCount;
}

void FurrowedNoise::setOctaveCount(int octaveCount) {
    invalidate();
    this->octaveCount = octaveCount;
}

Ogre::Real FurrowedNoise::getFrequency() const {
    return frequency;
}

void FurrowedNoise::setFrequency(Ogre::Real frequency) {
    invalidate();
    this->frequency = frequency;
}

Ogre::Real FurrowedNoise::getLacunarity() const {
    return lacunarity;
}

void FurrowedNoise::setLacunarity(Ogre::Real lacunarity) {
    invalidate();
    this->lacunarity = lacunarity;
}

void FurrowedNoise::initialise() {
    NoiseModule::initialise();

    coherentNoises.clear();

    // Compute spectral weights table.
    Ogre::Real h = 1.0, f = 1.0;

    for (int i = 0; i < octaveCount; ++i) {
        spectralWeights.push_back(pow(f, -h));
        f *= lacunarity;

        // Also add a coherent noise std::function for each octave.
        coherentNoises.push_back(SimplexNoise((getSeed() + i) & 0x7fffffff, 1.0));
        coherentNoises[i].initialise();
    }
}