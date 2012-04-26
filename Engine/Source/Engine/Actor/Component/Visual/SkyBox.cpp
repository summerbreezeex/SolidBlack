#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "SkyBox.h"

SkyBox::SkyBox(ComponentFactory* factory) :
        VisualComponent(factory),
        materialName("materialName", "") {
    addAttribute(&materialName);
}

void SkyBox::enterScene(Scene* scene) {
    VisualComponent::enterScene(scene);

    getScene()->getSceneManager()->setSkyBox(true, materialName.getValue());
}

void SkyBox::leaveScene() {
    getScene()->getSceneManager()->setSkyBoxEnabled(false);

    VisualComponent::leaveScene();
}