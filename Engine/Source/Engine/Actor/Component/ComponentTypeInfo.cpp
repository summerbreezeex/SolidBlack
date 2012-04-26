#include "Engine/Actor/Component/Component.h"

#include "ComponentTypeInfo.h"

ComponentTypeInfo::ComponentTypeInfo(const std::string& typeName, const ComponentTypeInfo* superTypeInfo) :
        typeName(typeName),
        superTypeInfo(superTypeInfo),
        family(superTypeInfo->getFamily()) {
}

ComponentTypeInfo::ComponentTypeInfo(const std::string& typeName, const ComponentTypeInfo* superTypeInfo, const ComponentConstructor& constructor) :
        typeName(typeName),
        superTypeInfo(superTypeInfo),
        family(superTypeInfo->getFamily()),
        constructor(constructor) {
}

ComponentTypeInfo::ComponentTypeInfo(const std::string& typeName, ComponentFamily::Enum family) :
        typeName(typeName),
        superTypeInfo(nullptr),
        family(family) {
}

Component* ComponentTypeInfo::createComponent() {
    Component* component = constructor();
    component->typeInfo = this;
    return component;
}

const std::string& ComponentTypeInfo::getTypeName() const {
    return typeName;
}

const std::string ComponentTypeInfo::getFullTypeName() const {
    auto implementedTypeNames = getImplementedTypeNames();
    int typeNameCount = implementedTypeNames.size();

    std::stringstream ss;
    for (int i = 0; i < typeNameCount; ++i) {
        ss << implementedTypeNames[i];

        if (i != typeNameCount - 1) {
            ss << " -> ";
        }
    }

    return ss.str();
}

ComponentFamily::Enum ComponentTypeInfo::getFamily() const {
    return family;
}

const std::vector<std::string> ComponentTypeInfo::getImplementedTypeNames() const {
    std::vector<std::string> implementedTypeNames;

    if (superTypeInfo) {
        implementedTypeNames = superTypeInfo->getImplementedTypeNames();
    }

    implementedTypeNames.push_back(typeName);
    return implementedTypeNames;
}