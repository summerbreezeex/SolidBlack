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
    auto it = typeInfoMap.find(typeName);
    if (it == typeInfoMap.end()) {
        throw std::runtime_error("No registered component type '" + typeName + "'");
    }

    return (*it).second->createComponent();
}

ComponentTypeInfo* ComponentFactory::getTypeInfo(const std::string& typeName) {
    return typeInfoMap[typeName].get();
}

void ComponentFactory::throwIfRegistered(const std::string& typeName) {
    if (typeInfoMap.find(typeName) != typeInfoMap.end()) {
        throw std::runtime_error("Component type '" + typeName + "' is already registered");
    }
}

void ComponentFactory::throwIfNotRegistered(const std::string& typeName) {
    if (typeInfoMap.find(typeName) == typeInfoMap.end()) {
        throw std::runtime_error("Component type '" + typeName + "' is not registered");
    }
}