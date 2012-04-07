#include <OgreMath.h>

#include "RidgedNoise.h"

RidgedNoise::RidgedNoise() :
        octaveCount(5),
        lacunarity(2.0),
        gain(0.5) {
}

RidgedNoise::RidgedNoise(int seed, Ogre::Real scale, int octaveCount, Ogre::Real lacunarity, Ogre::Real gain) :
        NoiseModule(seed, scale),
        octaveCount(octaveCount),
        lacunarity(lacunarity),
        gain(gain) {
}

Ogre::Real RidgedNoise::getValue(const Ogre::Vector3& position) const {
    assert(isInitialised());

    Ogre::Vector3 adjustedPosition(position * getScale());

    Ogre::Real sum = 0.0;
    Ogre::Real f = 1.0;
    Ogre::Real a = 1.0;

    for (int i = 0; i < octaveCount; ++i) {
        Ogre::Real noise = noises[i].getValue(adjustedPosition * f);
        sum += a * (1.0 - Ogre::Math::Abs(noise));
        f *= lacunarity;
        a *= gain;
    }

    return sum;
}

int RidgedNoise::getOctaveCount() const {
    return octaveCount;
}

void RidgedNoise::setOctaveCount(int octaveCount) {
    invalidate();
    this->octaveCount = octaveCount;
}

Ogre::Real RidgedNoise::getLacunarity() const {
    return lacunarity;
}

void RidgedNoise::setLacunarity(Ogre::Real lacunarity) {
    invalidate();
    this->lacunarity = lacunarity;
}

Ogre::Real RidgedNoise::getGain() const {
    return gain;
}

void RidgedNoise::setGain(Ogre::Real gain) {
    invalidate();
    this->gain = gain;
}

void RidgedNoise::initialise() {
    NoiseModule::initialise();

    noises.clear();
    for (int i = 0; i < octaveCount; ++i) {
        noises.push_back(SimplexNoise((getSeed() + i) & 0x7fffffff, 1.0));
        noises[i].initialise();
    }
}