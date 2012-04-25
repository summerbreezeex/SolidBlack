#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include <json/json.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/CoreComponentModule.h"
#include "Engine/Core/Engine.h"
#include "Engine/Core/Settings.h"
#include "Engine/Serialization/ActorJsonSerializer.h"
#include "Engine/Serialization/JsonUtils.h"

#include "Scene.h"

Scene::Scene(const std::string& name, Engine* engine) :
        Logged("Scene"),
        name(name),
        engine(engine),
        sceneManager(engine->getRoot()->createSceneManager(Ogre::ST_INTERIOR)),
        camera(sceneManager->createCamera("Camera")),
        viewport(engine->getRenderWindow()->addViewport(camera)),
        deferredShadingSystem(viewport, sceneManager, camera),
        scriptInterpreter(),
        componentFactory(this),
        nextActorId(1) {
    sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
    sceneManager->setAmbientLight(Ogre::ColourValue(0.04f, 0.04f, 0.04f));

    camera->setNearClipDistance(0.01);
    camera->setFarClipDistance(5000.0);
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

    deferredShadingSystem.initialize();
    deferredShadingSystem.setSsao(true);

    familyCollections[ComponentFamily::Input] = &inputComponents;
    familyCollections[ComponentFamily::Logical] = &logicalComponents;
    familyCollections[ComponentFamily::Physical] = &physicalComponents;
    familyCollections[ComponentFamily::Spacial] = &spacialComponents;
    familyCollections[ComponentFamily::Visual] = &visualComponents;

    componentFactory.registerModule<CoreComponentModule>();
}

Scene::~Scene() {
    removeAllActors();

    deferredShadingSystem.cleanUp();

    engine->getRenderWindow()->removeAllViewports();
    engine->getRoot()->destroySceneManager(sceneManager);
}

void Scene::saveActorsToFile(const std::string& fileName) {
    logInfo("Saving actors to '" + fileName + "'");

    Json::Value jsonValue;

    foreach (actorPair, actors) {
        Json::Value actorRoot;
        ActorJsonSerializer::serialize((*actorPair).second.get(), &actorRoot);

        jsonValue["actors"].append(actorRoot);
    }

    JsonUtils::writeValueToFile(jsonValue, fileName);
}

void Scene::loadActorsFromFile(const std::string& fileName) {
    logInfo("Loading actors from '" + fileName + "'");
    removeAllActors();

    Json::Value jsonValue;
    JsonUtils::readValueFromFile(fileName, &jsonValue);

    Json::Value actors = jsonValue["actors"];
    for (int i = 0; i < (int)actors.size(); ++i) {
        auto actor = ActorJsonSerializer::deserialize(getComponentFactory(), actors[i]);
        addActor(actor);
    };
}

void Scene::addActor(Actor* actor) {
    assert(!actor->getScene());

    ActorId id = nextActorId++;

    actor->setId(id);
    actors[id] = ActorPtr(actor);

    actor->enterScene(this);
}

void Scene::removeActor(Actor* actor) {
    assert(actor->getScene() == this);
    auto it = actors.find(actor->getId());

    actor->leaveScene();

    actors.erase(it);
}

void Scene::removeAllActors() {
    std::vector<Actor*> actorsToRemove = getActorsWhere([](const Actor*) { return true; });

    if (actorsToRemove.size() > 0) {
        logInfo("Removing all actors");
    }

    foreach (actor, actorsToRemove) {
        removeActor(*actor);
    }

    assert(actors.size() == 0);
}

void Scene::addComponent(Component* component) {
    auto typeData = component->getTypeData();
    auto it = familyCollections.find(typeData->getFamily());
    assert(it != familyCollections.end());

    (*it).second->addComponent(component);
}

void Scene::removeComponent(Component* component) {
    auto typeData = component->getTypeData();
    auto it = familyCollections.find(typeData->getFamily());
    assert(it != familyCollections.end());

    (*it).second->removeComponent(component);
}

void Scene::logicUpdate(Ogre::Real timeStep) {
    physicsTask.waitUntilDone();

    spacialComponents.logicUpdate(timeStep);
    physicalComponents.logicUpdate(timeStep);
    logicalComponents.logicUpdate(timeStep);
    visualComponents.logicUpdate(timeStep);

    auto deadActors = getActorsWhere([](const Actor* actor) {
        return !actor->isAlive();
    });

    foreach (actor, deadActors) {
        removeActor(*actor);
    }

    Task<void*>::Function physicsFunc = [this, timeStep]() -> void* {
        physics.logicUpdate(timeStep);
        return 0;
    };

    physicsTask = getEngine()->getTaskPool()->schedule([this, timeStep] {
        physics.logicUpdate(timeStep);
    });
}

void Scene::frameUpdate(Ogre::Real frameDelta) {
    spacialComponents.frameUpdate(frameDelta);
    visualComponents.frameUpdate(frameDelta);
}

Actor* Scene::getActor(ActorId id) {
    auto it = actors.find(id);

    if (it == actors.end()) {
        return nullptr;
    } else {
        return (*it).second.get();
    }
}

const std::vector<Actor*> Scene::getActorsWhere(ActorPredicate predicate) {
    std::vector<Actor*> resultingActors;

    foreach (actorPair, actors) {
        Actor* actor = (*actorPair).second.get();

        if (predicate(actor)) {
            resultingActors.push_back(actor);
        }
    }

    return resultingActors;
}

const std::string& Scene::getName() const {
    return name;
}

Engine* Scene::getEngine() {
    return engine;
}

Ogre::SceneManager* Scene::getSceneManager() {
    return sceneManager;
}

Ogre::Camera* Scene::getCamera() {
    return camera;
}

Physics* Scene::getPhysics() {
    return &physics;
}

ScriptInterpreter* Scene::getScriptInterpreter() {
    return &scriptInterpreter;
}

ComponentFactory* Scene::getComponentFactory() {
    return &componentFactory;
}