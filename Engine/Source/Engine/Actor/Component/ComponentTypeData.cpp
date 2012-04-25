#include "ComponentTypeData.h"

ComponentTypeData::ComponentTypeData() :
        classType(ComponentClassType::None),
        family(ComponentFamily::None) {
}

void ComponentTypeData::setClassType(ComponentClassType::Enum classType) {
    this->classType = classType;
}

ComponentClassType::Enum ComponentTypeData::getClassType() const {
    return classType;
}

void ComponentTypeData::setFamily(ComponentFamily::Enum family) {
    this->family = family;
}

ComponentFamily::Enum ComponentTypeData::getFamily() const {
    return family;
}

void ComponentTypeData::addBaseTypeName(const std::string& typeName) {
    baseTypeNames.push_back(typeName);
}

void ComponentTypeData::setDerivedTypeName(const std::string& typeName) {
    if (derivedTypeName != "") {
        addBaseTypeName(derivedTypeName);
    }

    derivedTypeName = typeName;
}

const std::string& ComponentTypeData::getDerivedTypeName() const {
    return derivedTypeName;
}

const std::vector<std::string>& ComponentTypeData::getBaseTypeNames() const {
    return baseTypeNames;
}

const std::vector<std::string> ComponentTypeData::getImplementedTypeNames() const {
    std::vector<std::string> resultingTypeNames;
    foreach (typeName, baseTypeNames) {
        resultingTypeNames.push_back(*typeName);
    }
    resultingTypeNames.push_back(derivedTypeName);

    return resultingTypeNames;
}

bool ComponentTypeData::implementsType(const std::string& typeName) const {
    return std::find(baseTypeNames.begin(), baseTypeNames.end(), typeName) != baseTypeNames.end();
}