#pragma once

#include "Engine/Actor/Component/Logical/LogicalComponent.h"
#include "Engine/Scripting/ScriptInterpreter.h"

class Script :
            public LogicalComponent {
public:
    Script(ComponentFactory* factory);

    void initializeScript();
    
    void attachToActor(Actor* actor);
    void detachFromActor();
    void enterScene(Scene* scene);
    void leaveScene();

    void logicUpdate(Ogre::Real timeStep);

    template <typename Ret>
    Ret invokeFunction(const std::string& functionName);

    template <typename Ret>
    Ret invokeMethod(const std::string& methodName);

    template <typename Ret, typename T0>
    Ret invokeMethod(const std::string& methodName, const T0& a0);

private:
    ComponentAttribute<std::string> scriptName;

    ScriptInterpreter* scriptInterpreter;

    LuaObject scriptObject;
};

#include "Script.inl"