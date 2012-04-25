#include "PhysicalComponent.h"

ComponentClassDef(PhysicalComponent)

PhysicalComponent::PhysicalComponent(ComponentFactory* factory) :
        Component(factory, ComponentFamily::Physical) {
}