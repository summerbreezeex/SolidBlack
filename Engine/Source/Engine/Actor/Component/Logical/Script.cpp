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

void Script::initializeScript() {
    scriptInterpreter = getFactory()->getScriptInterpreter();
    scriptInterpreter->loadScript(*scriptName);

    std::string constructorName = (*scriptName).substr(0, (*scriptName).size() - 4);

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

    // Get the script methods.
    attachToActorMethod = scriptObject["attachToActor"];
    detachFromActorMethod = scriptObject["detachFromActor"];
    enterSceneMethod = scriptObject["enterScene"];
    leaveSceneMethod = scriptObject["leaveScene"];
    logicUpdateMethod = scriptObject["logicUpdate"];
}

void Script::attachToActor(Actor* actor) {
    Super::attachToActor(actor);

    try {
        attachToActorMethod(scriptObject, actor);
    } catch (const luabind::error&) {
        throwMethodError("attachToActor");
    }
}

void Script::detachFromActor() {
    try {
        detachFromActorMethod(scriptObject);
    } catch (const luabind::error&) {
        throwMethodError("detachFromActor");
    }

    scriptObject = LuaObject();

    Super::detachFromActor();
}

void Script::enterScene(Scene* scene) {
    Super::enterScene(scene);

    try {
        enterSceneMethod(scriptObject, scene);
    } catch (const luabind::error&) {
        throwMethodError("enterScene");
    }
}

void Script::leaveScene() {
    try {
        leaveSceneMethod(scriptObject);
    } catch (const luabind::error&) {
        throwMethodError("leaveScene");
    }

    Super::leaveScene();
}

void Script::logicUpdate(Ogre::Real timeStep) {
    try {
        logicUpdateMethod(scriptObject, timeStep);
    } catch (const luabind::error&) {
        throwMethodError("logicUpdate");
    }
}

void Script::throwMethodError(const std::string& methodName) {
    throw new std::runtime_error("Error occurred in method '" + methodName + "' in '" + *scriptName + "': " + scriptInterpreter->getErrorMessage());
}