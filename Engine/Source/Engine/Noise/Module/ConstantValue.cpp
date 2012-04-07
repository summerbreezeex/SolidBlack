#include "ConstantValue.h"

ConstantValue::ConstantValue() :
        value(1.0) {
}

ConstantValue::ConstantValue(Ogre::Real value) :
        NoiseModule(0, 1.0),
        value(value) {
}

Ogre::Real ConstantValue::getValue(const Ogre::Vector3& position) const {
    return value;
}

void ConstantValue::setValue(Ogre::Real value) {
    this->value = value;
}