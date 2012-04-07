#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include <json/json.h>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Component/DefaultComponentModule.h"
#include "Engine/Core/Engine.h"
#include "Engine/Core/Settings.h"
#include "Engine/Serialization/ActorJsonSerializer.h"
#include "Engine/Serialization/JsonUtils.h"

#include "Scene.h"

Scene::Scene(const std::string& name, Engine* engine) :
        name(name),
        engine(engine),
        log(Ogre::LogManager::getSingleton().createLog(std::string(Settings::sceneLogFilePrefix) + name + ".log")),
        sceneManager(engine->getRoot()->createSceneManager(Ogre::ST_INTERIOR)),
        camera(sceneManager->createCamera("Camera")),
        viewport(engine->getRenderWindow()->addViewport(camera)),
        deferredShadingSystem(viewport, sceneManager, camera),
        nextActorId(1) {
    sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
    sceneManager->setAmbientLight(Ogre::ColourValue(0.04f, 0.04f, 0.04f));

    camera->setNearClipDistance(0.01);
    camera->setFarClipDistance(5000.0);
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

    deferredShadingSystem.initialize();
    deferredShadingSystem.setSsao(true);

    familyCollections["Input"] = &inputComponents;
    familyCollections["Logical"] = &logicalComponents;
    familyCollections["Physical"] = &physicalComponents;
    familyCollections["Spacial"] = &spacialComponents;
    familyCollections["Visual"] = &visualComponents;

    componentFactory.registerModule<DefaultComponentModule>();
}

Scene::~Scene() {
    removeAllActors();

    deferredShadingSystem.cleanUp();

    engine->getRenderWindow()->removeAllViewports();
    engine->getRoot()->destroySceneManager(sceneManager);

    Ogre::LogManager::getSingleton().destroyLog(log);
}

void Scene::saveActorsToFile(const std::string& fileName) {
    Json::Value jsonValue;

    foreach (actorPair, actors) {
        Json::Value actorRoot;
        ActorJsonSerializer::serialize((*actorPair).second.get(), &actorRoot);

        jsonValue["actors"].append(actorRoot);
    }

    JsonUtils::writeValueToFile(jsonValue, fileName);
}

void Scene::loadActorsFromFile(const std::string& fileName) {
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
    std::vector<Actor*> actorsToRemove;

    foreach (actorPair, actors) {
        actorsToRemove.push_back((*actorPair).second.get());
    }

    foreach (actor, actorsToRemove) {
        removeActor(*actor);
    }

    assert(actors.size() == 0);
}

void Scene::addComponent(Component* component) {
    auto it = familyCollections.find(component->getFamily());
    assert(it != familyCollections.end());

    (*it).second->addComponent(component);
}

void Scene::removeComponent(Component* component) {
    auto it = familyCollections.find(component->getFamily());
    assert(it != familyCollections.end());

    (*it).second->removeComponent(component);
}

void Scene::logicUpdate(Ogre::Real timeStep) {
    physicsTask.waitUntilDone();

    spacialComponents.logicUpdate(timeStep);
    physicalComponents.logicUpdate(timeStep);
    logicalComponents.logicUpdate(timeStep);
    visualComponents.logicUpdate(timeStep);

    ActorPredicate isDeadPredicate = [](const Actor* actor) {
        return !actor->isAlive();
    };

    auto deadActors = getActorsWhere(isDeadPredicate);
    foreach (actor, deadActors) {
        removeActor(*actor);
    }

    auto physicsAction = [this, timeStep]() -> bool {
        physics.logicUpdate(timeStep);
        return true;
    };

    physicsTask = getEngine()->getTaskPool()->schedule<bool>(physicsAction);
}

void Scene::frameUpdate(Ogre::Real frameDelta) {
    spacialComponents.frameUpdate(frameDelta);
    visualComponents.frameUpdate(frameDelta);
}

void Scene::logInfo(const std::string& message) {
    log->logMessage(message);
}

void Scene::logWarning(const std::string& message) {
    log->logMessage(std::string("WARNING: ") + message);
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

ComponentFactory* Scene::getComponentFactory() {
    return &componentFactory;
}