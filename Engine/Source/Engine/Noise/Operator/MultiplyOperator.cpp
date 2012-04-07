#include "MultiplyOperator.h"

Ogre::Real MultiplyOperator::getValue(const Ogre::Vector3& position) const {
    Ogre::Real value = 1.0;

    foreach (function, functions) {
        value *= (*function)->getValue(position);
    }

    return value;
}

void MultiplyOperator::addFunction(NoiseFunction* function) {
    functions.push_back(NoiseFunctionPtr(function));
}