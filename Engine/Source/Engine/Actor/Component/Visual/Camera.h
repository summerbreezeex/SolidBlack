#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class Camera :
            public VisualComponent {
public:
    Camera(ComponentFactory* factory);
    virtual ~Camera() { }

    void enterScene(Scene* scene);
    void leaveScene();

    Ogre::Real getFov() const;
    void setFov(Ogre::Real fov);

    Ogre::Vector3 getDirection() const;

private:
    void initializeCamera();

    ComponentAttribute<Ogre::Real> fov;

    Ogre::Camera* camera;
};