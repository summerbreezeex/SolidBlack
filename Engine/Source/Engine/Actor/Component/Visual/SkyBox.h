#pragma once

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class SkyBox :
            public VisualComponent {
public:
    ComponentClass

    SkyBox(ComponentFactory* factory);

    void enterScene(Scene* scene);
    void leaveScene();

private:
    ComponentAttribute<std::string> materialName;
};