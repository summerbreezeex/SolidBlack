#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "SkyBox.h"

std::string SkyBox::typeName = "SkyBox";

SkyBox::SkyBox() :
        materialName("materialName", "") {
    addImplementedTypeName(typeName);
    addAttribute(&materialName);
}

void SkyBox::enterScene(Scene* scene) {
    Super::enterScene(scene);

    getScene()->getSceneManager()->setSkyBox(true, materialName.getValue());
}

void SkyBox::leaveScene() {
    getScene()->getSceneManager()->setSkyBoxEnabled(false);

    Super::leaveScene();
}