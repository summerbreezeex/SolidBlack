#pragma once

#include <luabind/luabind.hpp>

#include "Engine/Actor/Component/Logical/LogicalComponent.h"
#include "Engine/Scripting/ScriptInterpreter.h"

class Script :
            public LogicalComponent {
    typedef LogicalComponent Super;
public:
    static std::string typeName;

    Script();

    void initialize();
    
    void attachToActor(Actor* actor);
    void detachFromActor();
    void enterScene(Scene* scene);
    void leaveScene();

    void logicUpdate(Ogre::Real timeStep);

    template <typename Ret>
    Ret invokeMethod(const std::string& methodName);

    template <typename Ret, typename T0>
    Ret invokeMethod(const std::string& methodName, const T0& a0);

private:
    ComponentAttribute<std::string> scriptName;

    ScriptInterpreter* scriptInterpreter;

    luabind::object scriptObject;
};

#include "Script.inl"