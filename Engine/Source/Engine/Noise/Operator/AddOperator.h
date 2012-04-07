#pragma once

#include "Engine/Noise/NoiseOperator.h"

class AddOperator :
            public NoiseOperator {
public:
    Ogre::Real getValue(const Ogre::Vector3& position) const;

    void addFunction(NoiseFunction* function);

private:
    std::vector<NoiseFunctionPtr> functions;
};