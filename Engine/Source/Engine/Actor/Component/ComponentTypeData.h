#pragma once

#include "Engine/StlCommon.h"

struct ComponentClassType {
    enum Enum {
        None,
        Abstract,
        Concrete
    };
};

struct ComponentFamily {
    enum Enum {
        None,
        Input,
        Logical,
        Physical,
        Spacial,
        Visual
    };
};

class ComponentTypeData {
public:
    ComponentTypeData();

    void setClassType(ComponentClassType::Enum classType);
    ComponentClassType::Enum getClassType() const;

    void setFamily(ComponentFamily::Enum family);
    ComponentFamily::Enum getFamily() const;

    void addBaseTypeName(const std::string& typeName);

    void setDerivedTypeName(const std::string& typeName);
    const std::string& getDerivedTypeName() const;

    const std::vector<std::string>& getBaseTypeNames() const;
    const std::vector<std::string> getImplementedTypeNames() const;

    bool implementsType(const std::string& typeName) const;

private:
    ComponentClassType::Enum classType;
    ComponentFamily::Enum family;

    std::vector<std::string> baseTypeNames;
    std::string derivedTypeName;
};