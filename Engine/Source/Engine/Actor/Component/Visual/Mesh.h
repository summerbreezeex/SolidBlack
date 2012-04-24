#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class Mesh :
            public VisualComponent {
    typedef VisualComponent Super;
public:
    ComponentClass

    Mesh();

    void enterScene(Scene* scene);
    void leaveScene();

    Ogre::Entity* getEntity();

private:
    ComponentAttribute<std::string> meshName;
    ComponentAttribute<std::string> materialName;

    Ogre::Entity* entity;
    Ogre::Mesh* mesh;
};