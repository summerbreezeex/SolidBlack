#pragma once

#include "Engine/StlCommon.h"
#include "Engine/Actor/Component/Component.h"

class Scene;
typedef unsigned int ActorId;

class Actor {
public:
    Actor(const std::string& name);

    void attachComponents();

    void enterScene(Scene* scene);
    void leaveScene();

    void kill();

    void addComponent(Component* component); // Assumes ownership of component.

    const std::vector<const Component*> getComponents() const;

    Component* findComponentOfType(const std::string& typeName);
    const std::vector<Component*> findComponentsOfType(const std::string& typeName);

    template <class T>
    T* findComponentOfType();

    template <class T>
    const std::vector<T*> findComponentsOfType();

    const std::string& getName() const;
    const std::string getUniqueName() const;

    ActorId getId() const;
    void setId(ActorId id);

    bool isAlive() const;

    Scene* getScene();

private:
    void registerImplementedTypes(Component* component);

    std::string name;
    ActorId id;
    bool alive;

    Scene* scene;

    std::map<std::string, std::vector<Component*>> componentImplementedTypes;
    std::vector<ComponentPtr> components;
};

typedef std::shared_ptr<Actor> ActorPtr;

#include "Actor.inl"