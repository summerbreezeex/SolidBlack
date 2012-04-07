#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class Camera :
            public VisualComponent {
    typedef VisualComponent Super;
public:
    static std::string typeName;

    Camera();
    virtual ~Camera() { }

    void enterScene(Scene* scene);
    void leaveScene();

    Ogre::Real getFov() const;
    void setFov(Ogre::Real fov);

private:
    void initialiseCamera();

    Attribute<Ogre::Real> fov;

    Ogre::Camera* camera;
};