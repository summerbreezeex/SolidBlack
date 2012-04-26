#pragma once

#include "Engine/StlCommon.h"

class Component;

class ComponentDependencyBase {
public:
    virtual void setComponent(Component* component) = 0;
    virtual const std::string getTypeName() const = 0;
};

template <typename T>
class ComponentDependency :
            public ComponentDependencyBase {
public:
    ComponentDependency();

    void setComponent(Component* component);
    T* getComponent();
    const T* getComponent() const;

    Component* getBaseComponent();

    const std::string getTypeName() const;

    operator bool() const;

private:
    T* component;
};

#include "ComponentDependency.inl"