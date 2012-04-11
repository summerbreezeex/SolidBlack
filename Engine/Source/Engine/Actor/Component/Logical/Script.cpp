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

void Script::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    scriptInterpreter = getFactory()->getScriptInterpreter();
    scriptInterpreter->loadScript(*scriptName);

    scriptObject = luabind::call_function<luabind::object>(scriptInterpreter->getLuaState(), (*scriptName).c_str());
    //scriptObject["internalComponent"] = this;
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

}