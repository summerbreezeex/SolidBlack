#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/ComponentFactory.h"

#include "Script.h"

ComponentClassDef(Script)

Script::Script(ComponentFactory* factory) :
        LogicalComponent(factory),
        scriptName("scriptName", ""),
        scriptInterpreter(nullptr) {
    addAttribute(&scriptName);
}

void Script::initializeScript() {
    auto scriptNameValue = scriptName.getValue();

    scriptInterpreter = getFactory()->getScene()->getScriptInterpreter();
    scriptInterpreter->loadScript(scriptNameValue);

    std::string constructorName = scriptNameValue.substr(0, scriptNameValue.size() - 4);

    // Construct the script object.
    scriptObject = invokeFunction<LuaObject>(constructorName);
    scriptObject["scriptWrapper"] = this;

    // Add dependencies defined in the script.
    for (luabind::iterator it(scriptObject["dependencies"]), end; it != end; ++it) {
        LuaObject dependency = *it;
        auto casted = luabind::object_cast_nothrow<ComponentDependencyBase*>(dependency);
        if (casted) {
            addDependency(*casted);
        }
    }

    // Add attributes defined in the script.
    for (luabind::iterator it(scriptObject["attributes"]), end; it != end; ++it) {
        LuaObject attribute = *it;
        auto casted = luabind::object_cast_nothrow<ComponentAttributeBase*>(attribute);
        if (casted) {
            addAttribute(*casted);
        }
    }
}

void Script::attachToActor(Actor* actor) {
    LogicalComponent::attachToActor(actor);

    invokeMethod<LuaObject>("attachToActor", actor);
}

void Script::detachFromActor() {
    invokeMethod<LuaObject>("detachFromActor");
    scriptObject = LuaObject();

    LogicalComponent::detachFromActor();
}

void Script::enterScene(Scene* scene) {
    LogicalComponent::enterScene(scene);

    invokeMethod<LuaObject>("enterScene", scene);
}

void Script::leaveScene() {
    invokeMethod<LuaObject>("leaveScene");

    LogicalComponent::leaveScene();
}

void Script::logicUpdate(Ogre::Real timeStep) {
    invokeMethod<LuaObject>("logicUpdate", timeStep);
}