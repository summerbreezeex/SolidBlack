#pragma once

#include <OgrePrerequisites.h>

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class Mesh :
            public VisualComponent {
    typedef VisualComponent Super;
public:
    static std::string typeName;

    Mesh();

    void enterScene(Scene* scene);
    void leaveScene();

    Ogre::Entity* getEntity();

private:
    Attribute<std::string> meshName;
    Attribute<std::string> materialName;

    Ogre::Entity* entity;
    Ogre::Mesh* mesh;
};