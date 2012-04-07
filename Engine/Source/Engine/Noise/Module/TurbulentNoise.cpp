#include "TurbulentNoise.h"

TurbulentNoise::TurbulentNoise() :
        octaveCount(5),
        persistance(0.5) {
}

TurbulentNoise::TurbulentNoise(int seed, Ogre::Real scale, int octaveCount, Ogre::Real persistance) :
        NoiseModule(seed, scale),
        octaveCount(octaveCount),
        persistance(persistance) {
}

Ogre::Real TurbulentNoise::getValue(const Ogre::Vector3& position) const {
    assert(isInitialised());

    Ogre::Real total = noise.getValue(position * getScale());

    Ogre::Real frequency = 2.0;
    Ogre::Real amplitude = 1.0;

    for (int i = 1; i < octaveCount; ++i) {
        frequency *= 2.0;
        amplitude *= persistance;

        total += noise.getValue(position * getScale() * frequency) * amplitude;
    }

    return total;
}

int TurbulentNoise::getOctaveCount() const {
    return octaveCount;
}

void TurbulentNoise::setOctaveCount(int octaveCount) {
    invalidate();
    this->octaveCount = octaveCount;
}

Ogre::Real TurbulentNoise::getPersistance() const {
    return persistance;
}

void TurbulentNoise::setPersistance(Ogre::Real persistance) {
    invalidate();
    this->persistance = persistance;
}

void TurbulentNoise::initialise() {
    NoiseModule::initialise();
    noise.initialise();
}