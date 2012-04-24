#pragma once

#include "Engine/StlCommon.h"

class ComponentTypeData {
public:
    void addBaseTypeName(const std::string& typeName);

    void setDerivedTypeName(const std::string& typeName);
    const std::string& getDerivedTypeName() const;

    const std::vector<std::string> getImplementedTypeNames() const;

    bool implementsType(const std::string& typeName) const;

    std::vector<std::string> baseTypeNames;
    std::string derivedTypeName;
};