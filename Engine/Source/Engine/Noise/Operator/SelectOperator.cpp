#include "SelectOperator.h"

SelectOperator::SelectOperator() :
        falloff(0.0),
        controlPoint(0.0) {
}

Ogre::Real SelectOperator::getValue(const Ogre::Vector3& position) const {
    Ogre::Real delta = controlFunction->getValue(position) - controlPoint;

    Ogre::Real value = 0.0;

    if (delta > falloff) {
        value = topFunction->getValue(position);
    } else if (delta < -falloff) {
        value = bottomFunction->getValue(position);
    } else {
        Ogre::Real d = (delta + falloff) /  (2.0 * falloff);

        Ogre::Real top = topFunction->getValue(position);
        Ogre::Real bottom = bottomFunction->getValue(position);

        value = bottom + (top - bottom) * d;
    }

    return value;
}

Ogre::Real SelectOperator::getFalloff() const {
    return falloff;
}

void SelectOperator::setFalloff(Ogre::Real falloff) {
    this->falloff = falloff;
}

Ogre::Real SelectOperator::getControlPoint() const {
    return controlPoint;
}

void SelectOperator::setControlPoint(Ogre::Real controlPoint) {
    this->controlPoint = controlPoint;
}

void SelectOperator::setControlFunction(NoiseFunction* function) {
    controlFunction = NoiseFunctionPtr(function);
}

void SelectOperator::setTopFunction(NoiseFunction* function) {
    topFunction = NoiseFunctionPtr(function);
}

void SelectOperator::setBottomFunction(NoiseFunction* function) {
    bottomFunction = NoiseFunctionPtr(function);
}