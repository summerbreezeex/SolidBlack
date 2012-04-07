#include "AddOperator.h"

Ogre::Real AddOperator::getValue(const Ogre::Vector3& position) const {
    Ogre::Real value = 0.0;

    foreach (function, functions) {
        value += (*function)->getValue(position);
    }

    return value;
}

void AddOperator::addFunction(NoiseFunction* function) {
    functions.push_back(NoiseFunctionPtr(function));
}