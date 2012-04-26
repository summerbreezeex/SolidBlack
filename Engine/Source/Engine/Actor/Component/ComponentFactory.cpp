#include "Engine/Actor/Scene.h"

#include "ComponentFactory.h"

ComponentFactory::ComponentFactory(Scene* scene) :
        Logged("ComponentFactory"),
        scene(scene),
        scriptInterpreter(scene->getScriptInterpreter()) {
}

Scene* ComponentFactory::getScene() {
    return scene;
}

Component* ComponentFactory::createComponent(const std::string& typeName) {
    auto typeInfo = getTypeInfo(typeName);
    if (typeInfo->isAbstract()) {
        throw std::runtime_error("Cannot create instance of abstract component type '" + typeName + "'");
    }

    return typeInfo->createComponent();
}

ComponentTypeInfo* ComponentFactory::getTypeInfo(const std::string& typeName) {
    throwIfNotRegistered(typeName);
    return registeredTypeInfo[typeName].get();
}

void ComponentFactory::throwIfRegistered(const std::string& typeName) {
    if (registeredTypeInfo.find(typeName) != registeredTypeInfo.end()) {
        throw std::runtime_error("Component type '" + typeName + "' is already registered");
    }
}

void ComponentFactory::throwIfNotRegistered(const std::string& typeName) {
    if (registeredTypeInfo.find(typeName) == registeredTypeInfo.end()) {
        throw std::runtime_error("Component type '" + typeName + "' is not registered");
    }
}