#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"
#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/ComponentCollection.h"
#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Core/Logged.h"
#include "Engine/Core/Physics.h"
#include "Engine/DeferredShading/DeferredShadingSystem.h"
#include "Engine/Threading/Task.h"

class Engine;

typedef std::function<bool(const Actor*)> ActorPredicate;

class Scene :
        public Logged {
public:
    Scene(const std::string& name, Engine* engine);
    ~Scene();

    void saveActorsToFile(const std::string& fileName);
    void loadActorsFromFile(const std::string& fileName);

    void addActor(Actor* actor);
    void removeActor(Actor* actor);
    void removeAllActors();

    void addComponent(Component* component);
    void removeComponent(Component* component);

    void logicUpdate(Ogre::Real timeStep);
    void frameUpdate(Ogre::Real frameDelta);

    Actor* getActor(ActorId id);
    const std::vector<Actor*> getActorsWhere(ActorPredicate predicate);

    const std::string& getName() const;

    Engine* getEngine();

    Ogre::SceneManager* getSceneManager();
    Ogre::Camera* getCamera();

    Physics* getPhysics();

    ComponentFactory* getComponentFactory();

private:
    std::string name;

    Engine* engine;

    Ogre::SceneManager* sceneManager;
    Ogre::Camera* camera;
    Ogre::Viewport* viewport;

    DeferredShadingSystem deferredShadingSystem;

    Physics physics;
    Task<> physicsTask;

    ActorId nextActorId;

    ComponentFactory componentFactory;

    ComponentCollection inputComponents;
    ComponentCollection logicalComponents;
    ComponentCollection physicalComponents;
    ComponentCollection spacialComponents;
    ComponentCollection visualComponents;

    std::map<std::string, ComponentCollection*> familyCollections;

    std::map<ActorId, ActorPtr> actors;
};