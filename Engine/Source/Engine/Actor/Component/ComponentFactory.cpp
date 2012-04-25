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
    auto it = constructors.find(typeName);
    if (it == constructors.end()) {
        throw std::runtime_error("No registered component type '" + typeName + "'.");
    }

    auto component = (*it).second();
    component->typeData = getTypeData(typeName);

    return component;
}

ComponentTypeData* ComponentFactory::getTypeData(const std::string& typeName) {
    return typeDataMap[typeName].get();
}