#include <OgreCamera.h>
#include <OgreCompositorChain.h>
#include <OgrePass.h>
#include <OgreTechnique.h>
#include <OgreViewport.h>

#include "SsaoListener.h"

SsaoListener::SsaoListener(Ogre::CompositorInstance* instance) :
        instance(instance) {
}

void SsaoListener::notifyMaterialRender(Ogre::uint32 passId, Ogre::MaterialPtr& material) {
    if (passId != 42) {
        return;
    }

    Ogre::Camera* camera = instance->getChain()->getViewport()->getCamera();
    Ogre::Vector3 farCorner = camera->getViewMatrix(true) * camera->getWorldSpaceCorners()[4];
    Ogre::Pass* pass = material->getBestTechnique()->getPass(0);

    Ogre::GpuProgramParametersSharedPtr params = pass->getVertexProgramParameters();
    if (params->_findNamedConstantDefinition("farCorner")) {
        params->setNamedConstant("farCorner", farCorner);
    }

    params = pass->getFragmentProgramParameters();

    static const Ogre::Matrix4 CLIP_SPACE_TO_IMAGE_SPACE(
        0.5,    0,    0,  0.5,
        0,   -0.5,    0,  0.5,
        0,      0,    1,    0,
        0,      0,    0,    1);

    if (params->_findNamedConstantDefinition("ptMat")) {
        params->setNamedConstant("ptMat", CLIP_SPACE_TO_IMAGE_SPACE * camera->getProjectionMatrixWithRSDepth());
    }

    if (params->_findNamedConstantDefinition("far")) {
        params->setNamedConstant("far", camera->getFarClipDistance());
    }
}