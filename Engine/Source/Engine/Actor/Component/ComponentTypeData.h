#pragma once

#include "Engine/StlCommon.h"

struct ComponentFamily {
    enum Enum {
        Input,
        Logical,
        Physical,
        Spacial,
        Visual
    };
};

class ComponentTypeData {
public:
    ComponentTypeData(const std::string& typeName, const ComponentTypeData* superTypeData);
    ComponentTypeData(const std::string& typeName, ComponentFamily::Enum family);

    const std::string& getTypeName() const;
    ComponentFamily::Enum getFamily() const;
    const std::vector<std::string> getImplementedTypeNames() const;

private:
    std::string typeName;
    const ComponentTypeData* superTypeData;
    
    ComponentFamily::Enum family;
};