#pragma once

#include "Engine/Noise/NoiseOperator.h"

class SelectOperator :
            public NoiseOperator {
public:
    SelectOperator();

    Ogre::Real getValue(const Ogre::Vector3& position) const;

    Ogre::Real getFalloff() const;
    void setFalloff(Ogre::Real falloff);

    Ogre::Real getControlPoint() const;
    void setControlPoint(Ogre::Real controlPoint);

    void setControlFunction(NoiseFunction* function);
    void setTopFunction(NoiseFunction* function);
    void setBottomFunction(NoiseFunction* function);

private:
    Ogre::Real falloff;
    Ogre::Real controlPoint;

    NoiseFunctionPtr controlFunction;

    NoiseFunctionPtr topFunction;
    NoiseFunctionPtr bottomFunction;
};