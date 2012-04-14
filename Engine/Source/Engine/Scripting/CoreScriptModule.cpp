#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Component.h"

#include "Engine/Scripting/ScriptInterpreter.h"

#include "CoreScriptModule.h"

void CoreScriptModule::registerCode(ScriptInterpreter* interpreter) {
    using namespace luabind;
    using namespace Ogre;

    module(interpreter->getLuaState()) [
        class_<Logged>("Logged")
            .def("logInfo", &Logged::logInfo)
            .def("logWarning", &Logged::logWarning),

        class_<Vector3>("Vector3")
            .def(constructor<Real, Real, Real>())
            .def_readwrite("x", &Vector3::x)
            .def_readwrite("y", &Vector3::y)
            .def_readwrite("z", &Vector3::z)
            .def("normalise", &Vector3::normalise)
            .def("normalisedCopy", &Vector3::normalisedCopy)
            .def(self + other<Vector3>())
            .def(self - other<Vector3>())
            .def(self * other<Vector3>())
            .def(self * other<Real>()),

        class_<Radian>("Radian")
            .def(constructor<Real>()),

        class_<Degree>("Degree")
            .def(constructor<Real>()),

        class_<Actor>("Actor"),

        class_<Scene, Logged>("Scene"),

        class_<Component, Logged>("Component"),

        class_<ComponentDependencyBase>("ComponentDependencyBase"),

        class_<ComponentAttributeBase>("ComponentAttributeBase"),

        class_<ComponentAttribute<bool>, ComponentAttributeBase>("BoolAttribute")
            .def(constructor<std::string, bool>())
            .property("value", &ComponentAttribute<bool>::getValue, &ComponentAttribute<bool>::setValue),

        class_<ComponentAttribute<Real>, ComponentAttributeBase>("NumberAttribute")
            .def(constructor<std::string, Real>())
            .property("value", &ComponentAttribute<Real>::getValue, &ComponentAttribute<Real>::setValue),

        class_<ComponentAttribute<std::string>, ComponentAttributeBase>("StringAttribute")
            .def(constructor<std::string, std::string>())   
            .property("value", &ComponentAttribute<std::string>::getValue, &ComponentAttribute<std::string>::setValue),

        class_<ComponentAttribute<Vector3>, ComponentAttributeBase>("Vector3Attribute")
            .def(constructor<std::string, Vector3>())
            .property("value", &ComponentAttribute<Vector3>::getValue, &ComponentAttribute<Vector3>::setValue)
    ];

    const char* listClass =
        "class 'List'\n"
        "function List:__init()\n"
        "    self.items = {}\n"
        "end\n"
        "function List:add(item)\n"
        "    table.insert(self.items, item)\n"
        "end\n"
        "function List:elements()\n"
        "    return ipairs(self.items)\n"
        "end\n";

    interpreter->execute(listClass);

    const char* scriptClass =
        "class 'Script'\n"
        "function Script:__init()\n"
        "    self.actor = nil\n"
        "    self.scriptWrapper = nil\n"
        "    self.attributes = { }\n"
        "    self.dependencies = { }\n"
        "end\n"

        "function Script:attachToActor(actor)\n"
        "    self.actor = actor\n"
        "end\n"

        "function Script:detatchFromActor()\n"
        "    self.actor = nil\n"
        "end\n"

        "function Script:enterScene(scene)\n"
        "    self.scene = scene\n"
        "end\n"

        "function Script:leaveScene()\n"
        "    self.scene = nil\n"
        "end\n"

        "function Script:logicUpdate(timeStep)\n"
        "end\n"

        "function Script:addAttribute(attribute)\n"
        "    table.insert(self.attributes, attribute)\n"
        "end\n"

        "function Script:addDependency(dependency)\n"
        "    table.insert(self.dependencies, dependency)\n"
        "end\n"

        "function Script:logInfo(message)\n"
        "    self.scriptWrapper:logInfo(message)\n"
        "end\n"

        "function Script:logWarning(message)\n"
        "    self.scriptWrapper:logWarning(message)\n"
        "end\n";

    interpreter->execute(scriptClass);
}