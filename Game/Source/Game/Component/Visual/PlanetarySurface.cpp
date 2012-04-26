#include <OgreSceneManager.h>

#include "Engine/Actor/Scene.h"
#include "Engine/Serialization/JsonUtils.h"
#include "Engine/Serialization/NoiseFunctionJsonSerializer.h"

#include "PlanetarySurface.h"

PlanetarySurface::PlanetarySurface(ComponentFactory* factory) :
        VisualComponent(factory),
        diameter("diameter", 0),
        noiseFunctionName("noiseFunctionName", ""),
        sceneCamera(nullptr),
#ifdef _DEBUG
        tessellation(32)
#else
        tessellation(64)
#endif
{
    addAttribute(&diameter);
    addAttribute(&noiseFunctionName);
}

void PlanetarySurface::enterScene(Scene* scene) {
    VisualComponent::enterScene(scene);

    initializeNoise();

    sceneCamera = scene->getCamera();

    Ogre::Real radius = getRadius();

    std::vector<Ogre::Quaternion> orientations(6);
    orientations[0].FromAngleAxis(Ogre::Degree(0.0), Ogre::Vector3::UNIT_Z);
    orientations[1].FromAngleAxis(Ogre::Degree(90.0), Ogre::Vector3::UNIT_Z);
    orientations[2].FromAngleAxis(Ogre::Degree(-90.0), Ogre::Vector3::UNIT_Z);
    orientations[3].FromAngleAxis(Ogre::Degree(180.0), Ogre::Vector3::UNIT_Z);
    orientations[4].FromAngleAxis(Ogre::Degree(90.0), Ogre::Vector3::UNIT_X);
    orientations[5].FromAngleAxis(Ogre::Degree(-90.0), Ogre::Vector3::UNIT_X);

    std::vector<Ogre::Vector3> positions(6);
    positions[0] = Ogre::Vector3(0.0, radius, 0.0);
    positions[1] = Ogre::Vector3(-radius, 0.0, 0.0);
    positions[2] = Ogre::Vector3(radius, 0.0, 0.0);
    positions[3] = Ogre::Vector3(0.0, -radius, 0.0);
    positions[4] = Ogre::Vector3(0.0, 0.0, radius);
    positions[5] = Ogre::Vector3(0.0, 0.0, -radius);

    for (int i = 0; i < 6; ++i) {
        Ogre::SceneNode* treeSceneNode = getSceneNode()->createChildSceneNode(positions[i], orientations[i]);
        terrainPatchTrees.push_back(std::make_shared<TerrainQuadtree>(this, treeSceneNode, getDiameter()));
    }
}

void PlanetarySurface::leaveScene() {
    terrainPatchTrees.clear();
    sceneCamera = nullptr;

    getSceneNode()->removeAndDestroyAllChildren();
    getScene()->getSceneManager()->destroySceneNode(getSceneNode());

    VisualComponent::leaveScene();
}

void PlanetarySurface::logicUpdate(Ogre::Real timeStep) {
    VisualComponent::logicUpdate(timeStep);

    foreach (tree, terrainPatchTrees) {
        (*tree)->update(sceneCamera);
    }
}

int PlanetarySurface::getDiameter() const {
    return diameter.getValue();
}

int PlanetarySurface::getRadius() const {
    return getDiameter() / 2;
}

int PlanetarySurface::getTessellation() const {
    return tessellation;
}

const NoiseFunction* PlanetarySurface::getNoiseFunction() const {
    return noiseFunction.get();
}

void PlanetarySurface::initializeNoise() {
    Json::Value root;
    JsonUtils::readValueFromFile(noiseFunctionName.getValue(), &root);

    NoiseFunction* n = NoiseFunctionJsonSerializer::deserialize(root);
    noiseFunction = NoiseFunctionPtr(n);
}