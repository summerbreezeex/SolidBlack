#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/ComponentAttribute.h"
#include "Engine/Actor/Component/ComponentDependency.h"
#include "Engine/Core/Logged.h"

class Actor;
class ComponentFactory;
class Scene;
class ScriptInterpreter;

class Component :
            public Logged {
    friend class ComponentFactory;
public:
    Component(const std::string& family);
    virtual ~Component();

    virtual void attachToActor(Actor* actor);
    virtual void detachFromActor();
    virtual void enterScene(Scene* scene);
    virtual void leaveScene();

    virtual void logicUpdate(Ogre::Real timeStep) { }
    virtual void frameUpdate(Ogre::Real frameDelta) { }

    Actor* getActor() const;
    Scene* getScene() const;

    const std::string& getFamily() const;

    const std::vector<std::string>& getImplementedTypeNames() const;
    const std::vector<std::string> getAttributeNames() const;

    template <typename T>
    bool attributeIsType(const std::string& name) const;

    template <typename T>
    void setAttributeValue(const std::string& name, const T& value);

    template <typename T>
    const T* getAttributeValue(const std::string& name) const;

    ComponentAttributeBase* getAttribute(const std::string& name);
    const ComponentAttributeBase* getAttribute(const std::string& name) const;

    const std::vector<ComponentAttributeBase*> getAttributes() const;

    bool isValid() const;
    
protected:
    void addAttribute(ComponentAttributeBase* attribute);
    void addDependency(ComponentDependencyBase* dependency);
    void addImplementedTypeName(const std::string& implementedTypeName);

    ComponentFactory* getFactory();
    void setFactory(ComponentFactory* factory);

private:
    void resolveDependencies();
    void unresolveDependencies();

    ComponentFactory* factory;

    Actor* actor;
    Scene* scene;

    std::string family;

    std::map<std::string, ComponentAttributeBase*> attributes;
    std::vector<ComponentDependencyBase*> dependencies;
    std::vector<std::string> implementedTypeNames;

    bool validFlag;
};

typedef Component*(*ComponentConstructor)();
typedef std::shared_ptr<Component> ComponentPtr;

#include "Component.inl"