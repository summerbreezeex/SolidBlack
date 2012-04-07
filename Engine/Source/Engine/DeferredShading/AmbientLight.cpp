#include <OgreMaterialManager.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>

#include "Engine/Core/GeometryUtils.h"
#include "Engine/Core/Settings.h"

#include "AmbientLight.h"

AmbientLight::AmbientLight() {
    setRenderQueueGroup(Ogre::RENDER_QUEUE_2);

    mRenderOp.vertexData = new Ogre::VertexData();
    mRenderOp.indexData = 0;

    GeometryUtils::createQuad(mRenderOp.vertexData);

    mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_STRIP;
    mRenderOp.useIndexes = false;

    setBoundingBox(Ogre::AxisAlignedBox(-10000, -10000, -10000, 10000, 10000, 10000));
    radius = 15000;

    material = Ogre::MaterialManager::getSingleton().getByName(Settings::ambientLightMaterial);
    assert(!material.isNull());
    material->load();
}

AmbientLight::~AmbientLight() {
    delete mRenderOp.indexData;
    delete mRenderOp.vertexData;
}

Ogre::Real AmbientLight::getBoundingRadius() const {
    return radius;
}

Ogre::Real AmbientLight::getSquaredViewDepth(const Ogre::Camera* camera) const {
    return 0.0;
}

const Ogre::MaterialPtr& AmbientLight::getMaterial(void) const {
    return material;
}

void AmbientLight::getWorldTransforms(Ogre::Matrix4* transform) const {
    *transform = Ogre::Matrix4::IDENTITY;
}

void AmbientLight::updateFromCamera(Ogre::Camera* camera) {
    Ogre::Technique* tech = getMaterial()->getBestTechnique();
    Ogre::Vector3 farCorner = camera->getViewMatrix(true) * camera->getWorldSpaceCorners()[4];

    for (unsigned short i = 0; i < tech->getNumPasses(); i++) {
        Ogre::Pass* pass = tech->getPass(i);
        Ogre::GpuProgramParametersSharedPtr params = pass->getVertexProgramParameters();

        if (params->_findNamedConstantDefinition("farCorner")) {
            params->setNamedConstant("farCorner", farCorner);
        }

        params = pass->getFragmentProgramParameters();

        if (params->_findNamedConstantDefinition("farCorner")) {
            params->setNamedConstant("farCorner", farCorner);
        }
    }
}