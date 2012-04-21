#include "ComponentFactory.h"

ComponentFactory::ComponentFactory(ScriptInterpreter* scriptInterpreter) :
        scriptInterpreter(scriptInterpreter) {
}

ScriptInterpreter* ComponentFactory::getScriptInterpreter() {
    return scriptInterpreter;
}

Component* ComponentFactory::createComponent(const std::string& typeName) {
    auto it = constructors.find(typeName);
    if (it == constructors.end()) {
        throw std::runtime_error(std::string("No registered component type '") + typeName + "'.");
    }

    Component* component = (*it).second();
    component->setFactory(this);
    return component;
}