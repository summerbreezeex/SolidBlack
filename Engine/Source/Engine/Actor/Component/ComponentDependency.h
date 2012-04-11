#pragma once

#include "Engine/StlCommon.h"

class Component;

class ComponentDependencyBase {
public:
    ComponentDependencyBase(const std::string& typeName);

    virtual void setComponent(Component* component) = 0;

    const std::string& getTypeName() const;

private:
    std::string typeName;
};

template <typename T>
class ComponentDependency :
        public ComponentDependencyBase {
    friend class Component;
public:
    ComponentDependency();

    void setComponent(Component* component);

    T* operator*();
    const T* operator*() const;

    operator bool() const;

private:
    T* component;
};

#include "ComponentDependency.inl"