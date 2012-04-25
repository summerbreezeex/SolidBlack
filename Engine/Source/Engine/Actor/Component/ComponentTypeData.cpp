#include "ComponentTypeData.h"

ComponentTypeData::ComponentTypeData(const std::string& typeName, const ComponentTypeData* superTypeData) :
        typeName(typeName),
        superTypeData(superTypeData),
        family(superTypeData->getFamily()) {
}

ComponentTypeData::ComponentTypeData(const std::string& typeName, ComponentFamily::Enum family) :
        typeName(typeName),
        superTypeData(nullptr),
        family(family) {
}

const std::string& ComponentTypeData::getTypeName() const {
    return typeName;
}

const std::string ComponentTypeData::getFullTypeName() const {
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

ComponentFamily::Enum ComponentTypeData::getFamily() const {
    return family;
}

const std::vector<std::string> ComponentTypeData::getImplementedTypeNames() const {
    std::vector<std::string> implementedTypeNames;

    if (superTypeData) {
        implementedTypeNames = superTypeData->getImplementedTypeNames();
    }

    implementedTypeNames.push_back(typeName);
    return implementedTypeNames;
}