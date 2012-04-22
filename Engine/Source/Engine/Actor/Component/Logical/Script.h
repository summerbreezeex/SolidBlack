#pragma once

#include "Engine/Actor/Component/Logical/LogicalComponent.h"
#include "Engine/Scripting/ScriptInterpreter.h"

class Script :
            public LogicalComponent {
    typedef LogicalComponent Super;
public:
    static std::string typeName;

    Script();

    void initializeScript();
    
    void attachToActor(Actor* actor);
    void detachFromActor();
    void enterScene(Scene* scene);
    void leaveScene();

    void logicUpdate(Ogre::Real timeStep);

    template <typename Ret>
    Ret invokeFunction(const std::string& functionName);

private:
    void throwMethodError(const std::string& methodName);

    ComponentAttribute<std::string> scriptName;

    ScriptInterpreter* scriptInterpreter;

    LuaObject scriptObject;

    LuaObject attachToActorMethod;
    LuaObject detachFromActorMethod;
    LuaObject enterSceneMethod;
    LuaObject leaveSceneMethod;
    LuaObject logicUpdateMethod;
};

#include "Script.inl"