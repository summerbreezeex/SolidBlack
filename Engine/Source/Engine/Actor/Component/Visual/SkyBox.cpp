#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "SkyBox.h"

ComponentClassDef(SkyBox)

SkyBox::SkyBox() :
        materialName("materialName", "") {
    getTypeData()->setDerivedTypeName(typeName);
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