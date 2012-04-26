#pragma once

#include "Engine/StlCommon.h"

class Component;

class ComponentDependencyBase {
public:
    virtual void resolve(Component* component) = 0;
    virtual void unresolve() = 0;

    virtual const std::string getTypeName() const = 0;
};

template <typename ComponentType>
class ComponentDependency :
            public ComponentDependencyBase {
public:
    ComponentDependency();

    void resolve(Component* component);
    void unresolve();

    const std::string getTypeName() const;

    ComponentType* getComponent();
    const ComponentType* getComponent() const;
    Component* getBaseComponent();

    operator bool() const;

private:
    ComponentType* component;
};

#include "ComponentDependency.inl"