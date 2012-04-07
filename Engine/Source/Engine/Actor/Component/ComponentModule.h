#pragma once

class ComponentFactory;

class ComponentModule {
public:
    virtual void registerComponents(ComponentFactory* factory) = 0;
};