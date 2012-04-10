#include "NoiseModule.h"

NoiseModule::NoiseModule() :
        seed(0),
        scale(1.0),
        initialized(false) {
}

NoiseModule::NoiseModule(int seed, Ogre::Real scale) :
        seed(seed),
        scale(scale),
        initialized(false) {
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

void NoiseModule::initialize() {
    initialized = true;
}

void NoiseModule::invalidate() {
    initialized = false;
}

bool NoiseModule::isInitialised() const {
    return initialized;
}