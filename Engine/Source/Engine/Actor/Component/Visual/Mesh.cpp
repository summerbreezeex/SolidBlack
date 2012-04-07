#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"

#include "Mesh.h"

std::string Mesh::typeName = "Mesh";

Mesh::Mesh() :
        meshName("meshName", ""),
        materialName("materialName", ""),
        entity(nullptr),
        mesh(nullptr) {
    addImplementedTypeName(typeName);
    addAttribute(&meshName);
    addAttribute(&materialName);
}

void Mesh::enterScene(Scene* scene) {
    Super::enterScene(scene);

    mesh = Ogre::MeshManager::getSingleton().load(meshName.getValue(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME).get();

    unsigned short src, dest;
    if (!mesh->suggestTangentVectorBuildParams(Ogre::VES_TANGENT, src, dest))
        mesh->buildTangentVectors(Ogre::VES_TANGENT, src, dest);

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

    Super::leaveScene();
}

Ogre::Entity* Mesh::getEntity() {
    return entity;
}