#pragma once

#include <luabind/luabind.hpp>

#include "Engine/Actor/Component/Logical/LogicalComponent.h"

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

private:
    ComponentAttribute<std::string> scriptName;

    ScriptInterpreter* scriptInterpreter;

    luabind::object scriptObject;
};