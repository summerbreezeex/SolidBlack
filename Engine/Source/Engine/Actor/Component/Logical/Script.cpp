#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/ComponentFactory.h"

#include "Script.h"

std::string Script::typeName = "Script";

Script::Script() :
        scriptName("scriptName", ""),
        scriptInterpreter(nullptr) {
    addImplementedTypeName(typeName);
    addAttribute(&scriptName);
}

void Script::initialize() {
    Super::initialize();

    scriptInterpreter = getFactory()->getScriptInterpreter();
    scriptInterpreter->loadScript(*scriptName);

    std::string constructorName = (*scriptName).substr(0, (*scriptName).size() - 4);

    try {
        scriptObject = luabind::call_function<luabind::object>(scriptInterpreter->getLuaState(), constructorName.c_str());
        scriptObject["scriptWrapper"] = this;

        for (luabind::iterator it(scriptObject["dependencies"]), end; it != end; ++it) {
            luabind::object member = *it;
            auto castedMember = luabind::object_cast_nothrow<ComponentDependencyBase*>(member);
            if (castedMember) {
                addDependency(*castedMember);
            }
        }
    } catch (const luabind::error&) {
        throw std::runtime_error("Failed to execute constructor for script '" + *scriptName + "': " + scriptInterpreter->getErrorMessage());
    }
}

void Script::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    invokeMethod<luabind::object>("attachToActor", actor);
}

void Script::detachFromActor() {
    invokeMethod<luabind::object>("detachFromActor");
    scriptObject = luabind::object();

    Super::detachFromActor();
}

void Script::enterScene(Scene* scene) {
    Super::enterScene(scene);

    invokeMethod<luabind::object>("enterScene", scene);
}

void Script::leaveScene() {
    invokeMethod<luabind::object>("leaveScene");

    Super::leaveScene();
}

void Script::logicUpdate(Ogre::Real timeStep) {
    invokeMethod<luabind::object>("logicUpdate", timeStep);
}