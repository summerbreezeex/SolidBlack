#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/ComponentTypeInfo.h"
#include "Engine/Actor/Component/ComponentAttribute.h"
#include "Engine/Actor/Component/ComponentDependency.h"
#include "Engine/Core/Logged.h"

class Actor;
class ComponentFactory;
class Scene;
class ScriptInterpreter;

class Component :
            public Logged {
    friend class ComponentTypeInfo;
public:
    Component(ComponentFactory* factory);
    virtual ~Component();

    virtual void attachToActor(Actor* actor);
    virtual void detachFromActor();
    virtual void enterScene(Scene* scene);
    virtual void leaveScene();

    virtual void logicUpdate(Ogre::Real timeStep) { }
    virtual void frameUpdate(Ogre::Real frameDelta) { }

    Actor* getActor() const;
    Scene* getScene() const;

    ComponentTypeInfo* getTypeInfo();
    const ComponentTypeInfo* getTypeInfo() const;

    bool isValid() const;
    
    template <typename AttributeType>
    const AttributeType* getAttributeValue(const std::string& name) const;

    template <typename AttributeType>
    void setAttributeValue(const std::string& name, const AttributeType& value);

    ComponentAttributeBase* getAttribute(const std::string& name);
    const ComponentAttributeBase* getAttribute(const std::string& name) const;

    const std::vector<ComponentAttributeBase*> getAttributes();
    const std::vector<const ComponentAttributeBase*> getAttributes() const;

protected:
    void addAttribute(ComponentAttributeBase* attribute);
    void addDependency(ComponentDependencyBase* dependency);

    ComponentFactory* getFactory();

private:
    void resolveDependencies();
    void unresolveDependencies();

    Actor* actor;
    Scene* scene;

    ComponentTypeInfo* typeInfo;
    ComponentFactory* factory;

    std::map<std::string, ComponentAttributeBase*> attributes;
    std::vector<ComponentDependencyBase*> dependencies;

    bool validFlag;
};

#include "Component.inl"