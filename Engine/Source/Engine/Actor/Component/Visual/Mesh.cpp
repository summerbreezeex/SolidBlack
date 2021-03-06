#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "Mesh.h"

Mesh::Mesh(ComponentFactory* factory) :
        VisualComponent(factory),
        meshName("meshName", ""),
        materialName("materialName", ""),
        entity(nullptr),
        mesh(nullptr) {
    addAttribute(&meshName);
    addAttribute(&materialName);
}

void Mesh::enterScene(Scene* scene) {
    VisualComponent::enterScene(scene);

    mesh = Ogre::MeshManager::getSingleton().load(meshName.getValue(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME).get();

    unsigned short source, destination;
    if (!mesh->suggestTangentVectorBuildParams(Ogre::VES_TANGENT, source, destination)) {
        mesh->buildTangentVectors(Ogre::VES_TANGENT, source, destination);
    }

    entity = scene->getSceneManager()->createEntity(meshName.getValue());
    entity->setCastShadows(true);

    if (materialName.getValue() != "") {
        entity->setMaterialName(materialName.getValue());
    }

    getSceneNode()->attachObject(entity);
}

void Mesh::leaveScene() {
    getSceneNode()->detachObject(entity);
    getScene()->getSceneManager()->destroyEntity(entity);

    mesh = nullptr;

    VisualComponent::leaveScene();
}

Ogre::Entity* Mesh::getEntity() {
    return entity;
}