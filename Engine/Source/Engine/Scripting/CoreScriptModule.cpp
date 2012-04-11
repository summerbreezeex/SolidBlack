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
            .def(self / other<Vector3>()),
        class_<Actor>("Actor"),
        class_<Scene>("Scene")
            .def("logInfo", &Scene::logInfo),
        class_<Component>("Component")
            .def("logInfo", &Component::logInfo)
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
        "    self.internalComponent = nil\n"
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
        "function Script:logInfo(message)\n"
        "    self.internalComponent:logInfo(message)\n"
        "end\n";

    interpreter->execute(scriptClass);
}