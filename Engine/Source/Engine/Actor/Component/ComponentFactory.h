#pragma once

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/Component.h"

class ComponentFactory {
public:
    template <class T>
    void registerModule();

    template <class T>
    void registerComponent();

    Component* createComponent(const std::string& typeName) const;

private:
    template <class T>
    static T* newComponent();

    std::map<std::string, ComponentConstructor> constructors;
};

#include "ComponentFactory.inl"