#include "ComponentFactory.h"

Component* ComponentFactory::createComponent(const std::string& typeName) const {
    auto it = constructors.find(typeName);
    if (it == constructors.end()) {
        throw std::runtime_error(std::string("No registered component type '") + typeName + "'.");
    }

    return (*it).second();
}