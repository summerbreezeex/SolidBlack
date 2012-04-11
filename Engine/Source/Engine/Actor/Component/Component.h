#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/ComponentAttribute.h"
#include "Engine/Actor/Component/ComponentDependency.h"

class Actor;
class Scene;

class Component {
public:
    Component();
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

protected:
    void addAttribute(ComponentAttributeBase* attribute);
    void addDependency(ComponentDependencyBase* dependency);
    void addImplementedTypeName(const std::string& implementedTypeName);

    void setFamily(const std::string& family);

private:
    void resolveDependencies();
    void unresolveDependencies();

    Actor* actor;
    Scene* scene;

    std::string family;

    std::map<std::string, ComponentAttributeBase*> attributes;
    std::vector<ComponentDependencyBase*> dependencies;
    std::vector<std::string> implementedTypeNames;
};

typedef Component*(*ComponentConstructor)();
typedef std::shared_ptr<Component> ComponentPtr;

#include "Component.inl"