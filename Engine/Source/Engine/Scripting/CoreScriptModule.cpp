#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>

#include "Engine/Actor/Actor.h"
#include "Engine/Actor/Scene.h"
#include "Engine/Actor/Component/Component.h"
#include "Engine/Noise/RandomSequence.h"

#include "Engine/Scripting/ScriptInterpreter.h"

#include "CoreScriptModule.h"

void CoreScriptModule::registerCode(ScriptInterpreter* interpreter) {
    using namespace luabind;
    using namespace Ogre;

    module(interpreter->getLuaState()) [
        // Logged
        class_<Logged>("Logged")
            .def("logInfo", &Logged::logInfo)
            .def("logWarning", &Logged::logWarning)
            .def("logError", &Logged::logError),

        // RandomSequence
        class_<RandomSequence>("RandomSequence")
            .def(constructor<int>())
            .def("getNextNumber", &RandomSequence::getNextNumber),

        // Vector2
        class_<Vector2>("Vector2")
            .def(constructor<Real, Real>())
            .def_readwrite("x", &Vector2::x)
            .def_readwrite("y", &Vector2::y)
            .def("normalise", &Vector2::normalise)
            .def("normalisedCopy", &Vector2::normalisedCopy)
            .def("dotProduct", &Vector2::dotProduct)
            .def(self + other<Vector2>())
            .def(self - other<Vector2>())
            .def(self * other<Vector2>())
            .def(self * other<Real>()),

        // Vector3
        class_<Vector3>("Vector3")
            .def(constructor<Real, Real, Real>())
            .def_readwrite("x", &Vector3::x)
            .def_readwrite("y", &Vector3::y)
            .def_readwrite("z", &Vector3::z)
            .def("normalise", &Vector3::normalise)
            .def("normalisedCopy", &Vector3::normalisedCopy)
            .def("crossProduct", &Vector3::crossProduct)
            .def("dotProduct", &Vector3::dotProduct)
            .def(self + other<Vector3>())
            .def(self - other<Vector3>())
            .def(self * other<Vector3>())
            .def(self * other<Real>()),

        // Vector4
        class_<Vector4>("Vector4")
            .def(constructor<Real, Real, Real, Real>())
            .def_readwrite("x", &Vector4::x)
            .def_readwrite("y", &Vector4::y)
            .def_readwrite("z", &Vector4::z)
            .def_readwrite("w", &Vector4::w)
            .def("dotProduct", &Vector4::dotProduct)
            .def(self + other<Vector4>())
            .def(self - other<Vector4>())
            .def(self * other<Vector4>())
            .def(self * other<Real>()),

        // Quaternion
        class_<Quaternion>("Quaternion")
            .def(constructor<Real, Real, Real, Real>())
            .def_readwrite("x", &Quaternion::x)
            .def_readwrite("y", &Quaternion::y)
            .def_readwrite("z", &Quaternion::z)
            .def_readwrite("w", &Quaternion::w)
            .def("normalise", &Quaternion::normalise),

        // Radian
        class_<Radian>("Radian")
            .def(constructor<Real>()),

        // Degree
        class_<Degree>("Degree")
            .def(constructor<Real>()),

        // ColourValue
        class_<ColourValue>("ColourValue")
            .def(constructor<float, float, float>())
            .def(constructor<float, float, float, float>())
            .def_readwrite("r", &ColourValue::r)
            .def_readwrite("g", &ColourValue::g)
            .def_readwrite("b", &ColourValue::b)
            .def_readwrite("a", &ColourValue::a)
            .def("saturate", &ColourValue::saturate)
            .def("saturateCopy", &ColourValue::saturateCopy)
            .def(self + other<ColourValue>())
            .def(self - other<ColourValue>())
            .def(self * other<ColourValue>())
            .def(self * other<float>()),

        // Actor
        class_<Actor>("Actor"),

        // Scene
        class_<Scene, Logged>("Scene"),

        // Component
        class_<Component, Logged>("Component"),

        // ComponentDependencyBase
        class_<ComponentDependencyBase>("ComponentDependencyBase")
            .property("component", &ComponentDependencyBase::getBaseComponent),

        // ComponentAttributeBase
        class_<ComponentAttributeBase>("ComponentAttributeBase"),

        // BoolAttribute
        class_<ComponentAttribute<bool>, ComponentAttributeBase>("BoolAttribute")
            .def(constructor<std::string, bool>())
            .property("value", (const bool&(ComponentAttribute<bool>::*)()const)&ComponentAttribute<bool>::getValue, &ComponentAttribute<bool>::setValue),

        // NumberAttribute
        class_<ComponentAttribute<Real>, ComponentAttributeBase>("NumberAttribute")
            .def(constructor<std::string, Real>())
            .property("value", (const Real&(ComponentAttribute<Real>::*)()const)&ComponentAttribute<Real>::getValue, &ComponentAttribute<Real>::setValue),

        // StringAttribute
        class_<ComponentAttribute<std::string>, ComponentAttributeBase>("StringAttribute")
            .def(constructor<std::string, std::string>())   
            .property("value", (const std::string&(ComponentAttribute<std::string>::*)()const)&ComponentAttribute<std::string>::getValue, &ComponentAttribute<std::string>::setValue),

        // Vector3Attribute
        class_<ComponentAttribute<Vector3>, ComponentAttributeBase>("Vector3Attribute")
            .def(constructor<std::string, Vector3>())
            .property("value", (const Vector3&(ComponentAttribute<Vector3>::*)()const)&ComponentAttribute<Vector3>::getValue, &ComponentAttribute<Vector3>::setValue),

        // ColourValueAttribute
        class_<ComponentAttribute<ColourValue>, ComponentAttributeBase>("ColourValueAttribute")
            .def(constructor<std::string, ColourValue>())
            .property("value", (const ColourValue&(ComponentAttribute<ColourValue>::*)()const)&ComponentAttribute<ColourValue>::getValue, &ComponentAttribute<ColourValue>::setValue)
    ];
    
    interpreter->execute(
        // List
        "class 'List'\n"
        "function List:__init()\n"
        "    self.items = {}\n"
        "end\n"

        "function List:add(item)\n"
        "    table.insert(self.items, item)\n"
        "end\n"

        "function List:elements()\n"
        "    return ipairs(self.items)\n"
        "end\n"

        // Script
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
        "end\n"

        "function Script:logError(message)\n"
        "    self.scriptWrapper:logError(message)\n"
        "end\n"
    );
}