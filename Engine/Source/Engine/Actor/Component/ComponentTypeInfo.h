#pragma once

#include "Engine/StlCommon.h"

class Component;
typedef std::function<Component*()> ComponentConstructor;

struct ComponentFamily {
    enum Enum {
        Input,
        Logical,
        Physical,
        Spacial,
        Visual
    };
};

class ComponentTypeInfo {
public:
    ComponentTypeInfo(const std::string& typeName, const ComponentTypeInfo* superTypeInfo);
    ComponentTypeInfo(const std::string& typeName, const ComponentTypeInfo* superTypeInfo, const ComponentConstructor& constructor);
    ComponentTypeInfo(const std::string& typeName, ComponentFamily::Enum family);

    Component* createComponent();

    const std::string& getTypeName() const;
    const std::string getFullTypeName() const;
    ComponentFamily::Enum getFamily() const;
    const std::vector<std::string> getImplementedTypeNames() const;

private:
    std::string typeName;
    const ComponentTypeInfo* superTypeInfo;
    
    ComponentFamily::Enum family;
    ComponentConstructor constructor;
};

template <class T>
const std::string getComponentTypeName() {
    std::string typeName(typeid(T).name());
    typeName = typeName.substr(6, typeName.length() - 1);

    return typeName;
}