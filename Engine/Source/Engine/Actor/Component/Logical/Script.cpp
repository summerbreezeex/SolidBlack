#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/ComponentFactory.h"
#include "Engine/Scripting/ScriptInterpreter.h"

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

    scriptObject = luabind::call_function<luabind::object>(scriptInterpreter->getLuaState(), (*scriptName).c_str());
    scriptObject["scriptWrapper"] = this;

    for (luabind::iterator it(scriptObject["dependencies"]), end; it != end; ++it) {
        luabind::object member = *it;
        auto castedMember = luabind::object_cast_nothrow<ComponentDependencyBase*>(member);
        if (castedMember) {
            addDependency(*castedMember);
        }
    }
}

void Script::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    luabind::call_member<luabind::object>(scriptObject, "attachToActor", actor);
}

void Script::detachFromActor() {
    luabind::call_member<luabind::object>(scriptObject, "detachFromActor");
    scriptObject = luabind::object();

    Super::detachFromActor();
}

void Script::enterScene(Scene* scene) {
    Super::enterScene(scene);

    luabind::call_member<luabind::object>(scriptObject, "enterScene", scene);
}

void Script::leaveScene() {
    luabind::call_member<luabind::object>(scriptObject, "leaveScene");

    Super::leaveScene();
}

void Script::logicUpdate(Ogre::Real timeStep) {
    luabind::call_member<luabind::object>(scriptObject, "logicUpdate", timeStep);
}