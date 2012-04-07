#include "NoiseModule.h"

NoiseModule::NoiseModule() :
        seed(0),
        scale(1.0),
        initialised(false) {
}

NoiseModule::NoiseModule(int seed, Ogre::Real scale) :
        seed(seed),
        scale(scale),
        initialised(false) {
}

int NoiseModule::getSeed() const {
    return seed;
}

void NoiseModule::setSeed(int seed) {
    invalidate();
    this->seed = seed;
}

Ogre::Real NoiseModule::getScale() const {
    return scale;
}

void NoiseModule::setScale(Ogre::Real scale) {
    invalidate();
    this->scale = scale;
}

void NoiseModule::initialise() {
    initialised = true;
}

void NoiseModule::invalidate() {
    initialised = false;
}

bool NoiseModule::isInitialised() const {
    return initialised;
}