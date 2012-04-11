#pragma once

#include <OgrePrerequisites.h>
#include <OgreColourValue.h>
#include <OgreVector4.h>

#include "Engine/Actor/Component/Visual/VisualComponent.h"

class Light :
            public VisualComponent {
    typedef VisualComponent Super;
public:
    static std::string typeName;

    Light();
    virtual ~Light() { }

    void enterScene(Scene* scene);
    void leaveScene();

    bool isEnabled() const;
    void setEnabled(bool enabled);

    const Ogre::ColourValue& getDiffuseColour() const;
    void setDiffuseColour(const Ogre::ColourValue& colour);

    const Ogre::ColourValue& getSpecularColour() const;
    void setSpecularColour(const Ogre::ColourValue& colour);

    const Ogre::Vector4& getAttenuation() const;
    void setAttenuation(const Ogre::Vector4& attenuation);

protected:
    virtual Ogre::Light* createLight() = 0;

private:
    ComponentAttribute<bool> enabled;
    ComponentAttribute<Ogre::ColourValue> diffuseColour;
    ComponentAttribute<Ogre::ColourValue> specularColour;
    ComponentAttribute<Ogre::Vector4> attenuation;

    Ogre::Light* light;
};