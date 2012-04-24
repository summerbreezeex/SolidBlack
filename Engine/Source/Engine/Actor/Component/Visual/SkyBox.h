#pragma once

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class SkyBox :
            public VisualComponent {
    typedef VisualComponent Super;
public:
    ComponentClass

    SkyBox();

    void enterScene(Scene* scene);
    void leaveScene();

private:
    ComponentAttribute<std::string> materialName;
};