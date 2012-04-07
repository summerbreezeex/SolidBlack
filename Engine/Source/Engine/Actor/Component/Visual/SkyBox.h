#pragma once

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class SkyBox :
            public VisualComponent {
    typedef VisualComponent Super;
public:
    static std::string typeName;

    SkyBox();

    void enterScene(Scene* scene);
    void leaveScene();

private:
    Attribute<std::string> materialName;
};