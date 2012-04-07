#pragma once

#include "Engine/Noise/NoiseFunction.h"

class NoiseModule :
            public NoiseFunction {
public:
    NoiseModule();
    NoiseModule(int seed, Ogre::Real scale);
    virtual ~NoiseModule() { }

    virtual Ogre::Real getValue(const Ogre::Vector3& position) const = 0;

    int getSeed() const;
    void setSeed(int seed);

    Ogre::Real getScale() const;
    void setScale(Ogre::Real scale);

    virtual void initialise();

protected:
    void invalidate();

    bool isInitialised() const;

private:
    int seed;
    Ogre::Real scale;

    bool initialised;
};