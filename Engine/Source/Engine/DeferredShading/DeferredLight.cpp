#include <OgreCamera.h>
#include <OgreHardwareBufferManager.h>
#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreTechnique.h>
#include <OgreSceneManager.h>

#include "Engine/Core/GeometryUtils.h"
#include "Engine/DeferredShading/LightMaterialGenerator.h"

#include "DeferredLight.h"

#define ENABLE_BIT(mask, flag) (mask) |= (flag)
#define DISABLE_BIT(mask, flag) (mask) &= ~(flag)

DeferredLight::DeferredLight(MaterialGenerator* generator, Ogre::Light* parentLight):
        parentLight(parentLight),
        ignoreWorld(false),
        radius(0.0),
        generator(generator),
        permutation(0) {
    mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
    mRenderOp.indexData = 0;
    mRenderOp.vertexData = 0;
    mRenderOp.useIndexes = true;

    updateFromParent();
}

DeferredLight::~DeferredLight() {
    delete mRenderOp.indexData;
    delete mRenderOp.vertexData;
}

void DeferredLight::setAttenuation(Ogre::Real c, Ogre::Real b, Ogre::Real a) {
    Ogre::Real outerRadius = parentLight->getAttenuationRange();

    if (c != 1.0 || b != 0.0 || a != 0.0) {
        ENABLE_BIT(permutation, LightMaterialGenerator::MI_ATTENUATED);
        if (parentLight->getType() == Ogre::Light::LT_POINT) {
            int thresholdLevel = 10;
            Ogre::Real threshold = 1.0 / ((Ogre::Real)thresholdLevel / 256.0);

            c -= threshold;
            Ogre::Real d = Ogre::Math::Sqrt(b * b - 4 * a * c);
            outerRadius = (-2 * c) / (b + d);
            outerRadius *= 1.2;
        }
    } else {
        DISABLE_BIT(permutation, LightMaterialGenerator::MI_ATTENUATED);
    }

    rebuildGeometry(outerRadius);
}

void DeferredLight::setSpecularColour(const Ogre::ColourValue& colour) {
    if (colour.r != 0.0 || colour.g != 0.0 || colour.b != 0.0) {
        ENABLE_BIT(permutation,LightMaterialGenerator::MI_SPECULAR);
    } else {
        DISABLE_BIT(permutation,LightMaterialGenerator::MI_SPECULAR);
    }
}

void DeferredLight::rebuildGeometry(Ogre::Real radius) {
    DISABLE_BIT(permutation, LightMaterialGenerator::MI_POINT);
    DISABLE_BIT(permutation, LightMaterialGenerator::MI_SPOTLIGHT);
    DISABLE_BIT(permutation, LightMaterialGenerator::MI_DIRECTIONAL);

    switch (parentLight->getType()) {
        case Ogre::Light::LT_DIRECTIONAL:
            createRectangle2D();
            ENABLE_BIT(permutation,LightMaterialGenerator::MI_DIRECTIONAL);
            break;
        case Ogre::Light::LT_POINT:
            createSphere(radius, 10, 10);
            ENABLE_BIT(permutation,LightMaterialGenerator::MI_POINT);
            break;
        case Ogre::Light::LT_SPOTLIGHT:
            Ogre::Real height = parentLight->getAttenuationRange();
            Ogre::Radian coneRadiusAngle = parentLight->getSpotlightOuterAngle() / 2;
            Ogre::Real rad = Ogre::Math::Tan(coneRadiusAngle) * height;
            createCone(rad, height, 20);
            ENABLE_BIT(permutation,LightMaterialGenerator::MI_SPOTLIGHT);
            break;
    }
}

void DeferredLight::createRectangle2D() {
    delete mRenderOp.vertexData;
    delete mRenderOp.indexData;

    mRenderOp.vertexData = new Ogre::VertexData();
    mRenderOp.indexData = 0;

    GeometryUtils::createQuad(mRenderOp.vertexData);

    mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_STRIP;
    mRenderOp.useIndexes = false;

    setBoundingBox(Ogre::AxisAlignedBox(-10000, -10000, -10000, 10000, 10000, 10000));
    radius = 15000;
    ignoreWorld = true;
}

void DeferredLight::createSphere(Ogre::Real radius, int numRings, int numSegments) {
    delete mRenderOp.vertexData;
    delete mRenderOp.indexData;
    mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
    mRenderOp.indexData = new Ogre::IndexData();
    mRenderOp.vertexData = new Ogre::VertexData();
    mRenderOp.useIndexes = true;

    GeometryUtils::createSphere(mRenderOp.vertexData, mRenderOp.indexData, radius, numRings, numSegments, false, false);

    setBoundingBox(Ogre::AxisAlignedBox(Ogre::Vector3(-radius, -radius, -radius), Ogre::Vector3(radius, radius, radius)));
    this->radius = radius;
    ignoreWorld = false;
}

void DeferredLight::createCone(Ogre::Real radius, Ogre::Real height, int numVerticesInBase) {
    delete mRenderOp.vertexData;
    delete mRenderOp.indexData;
    mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
    mRenderOp.indexData = new Ogre::IndexData();
    mRenderOp.vertexData = new Ogre::VertexData();
    mRenderOp.useIndexes = true;

    GeometryUtils::createCone(mRenderOp.vertexData, mRenderOp.indexData, radius, height, numVerticesInBase);

    setBoundingBox(Ogre::AxisAlignedBox(Ogre::Vector3(-radius, 0, -radius), Ogre::Vector3(radius, height, radius)));
    this->radius = radius;
    ignoreWorld = false;
}

Ogre::Real DeferredLight::getBoundingRadius() const {
    return radius;
}

Ogre::Real DeferredLight::getSquaredViewDepth(const Ogre::Camera* camera) const {
    if (ignoreWorld) {
        return 0.0;
    } else {
        Ogre::Vector3 dist = camera->getDerivedPosition() - getParentSceneNode()->_getDerivedPosition();
        return dist.squaredLength();
    }
}

const Ogre::MaterialPtr& DeferredLight::getMaterial() const {
    return generator->getMaterial(permutation);
}

void DeferredLight::getWorldTransforms(Ogre::Matrix4* transform) const {
    if (parentLight->getType() == Ogre::Light::LT_SPOTLIGHT) {
        Ogre::Quaternion quat = Ogre::Vector3::UNIT_Y.getRotationTo(parentLight->getDerivedDirection());
        transform->makeTransform(parentLight->getDerivedPosition(), Ogre::Vector3::UNIT_SCALE, quat);
    } else {
        transform->makeTransform(parentLight->getDerivedPosition(), Ogre::Vector3::UNIT_SCALE, Ogre::Quaternion::IDENTITY);
    }
}

void DeferredLight::updateFromParent() {
    setAttenuation(parentLight->getAttenuationConstant(), parentLight->getAttenuationLinear(), parentLight->getAttenuationQuadric());
    setSpecularColour(parentLight->getSpecularColour());

    if (getCastChadows()) {
        ENABLE_BIT(permutation,LightMaterialGenerator::MI_SHADOW_CASTER);
    } else {
        DISABLE_BIT(permutation, LightMaterialGenerator::MI_SHADOW_CASTER);
    }
}

bool DeferredLight::isCameraInsideLight(Ogre::Camera* camera) {
    switch (parentLight->getType()) {
        case Ogre::Light::LT_DIRECTIONAL:
            return false;
        case Ogre::Light::LT_POINT: {
            Ogre::Real distanceFromLight =
                camera->getDerivedPosition().distance(parentLight->getDerivedPosition());

            // Small epsilon fix to account for the fact that we aren't a true sphere.
            return distanceFromLight <= radius + camera->getNearClipDistance() + 0.1;
        }
        case Ogre::Light::LT_SPOTLIGHT: {
            Ogre::Vector3 lightPos = parentLight->getDerivedPosition();
            Ogre::Vector3 lightDir = parentLight->getDerivedDirection();
            Ogre::Radian attAngle = parentLight->getSpotlightOuterAngle();

            // Extend the analytic cone's radius by the near clip range by moving its tip accordingly.
            Ogre::Vector3 clipRangeFix = -lightDir * (camera->getNearClipDistance() / Ogre::Math::Tan(attAngle/2));
            lightPos = lightPos + clipRangeFix;

            Ogre::Vector3 lightToCamDir = camera->getDerivedPosition() - lightPos;
            Ogre::Real distanceFromLight = lightToCamDir.normalise();

            Ogre::Real cosAngle = lightToCamDir.dotProduct(lightDir);
            Ogre::Radian angle = Ogre::Math::ACos(cosAngle);

            // Check whether we will see the cone from our current POV.
            return (distanceFromLight <= (parentLight->getAttenuationRange() + clipRangeFix.length()))
                   && (angle <= attAngle);
        }
        default:
            return false;
    }
}

bool DeferredLight::getCastChadows() const {
    return
        parentLight->_getManager()->isShadowTechniqueInUse() &&
        parentLight->getCastShadows() &&
        (parentLight->getType() == Ogre::Light::LT_DIRECTIONAL || parentLight->getType() == Ogre::Light::LT_SPOTLIGHT);
}

void DeferredLight::updateFromCamera(Ogre::Camera* camera) {
    const Ogre::MaterialPtr& material = getMaterial();
    if (!material->isLoaded()) {
        material->load();
    }
    Ogre::Technique* tech = material->getBestTechnique();
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

        if (parentLight->getType() == Ogre::Light::LT_DIRECTIONAL) {
            pass->setCullingMode(Ogre::CULL_CLOCKWISE);
            pass->setDepthCheckEnabled(false);
        } else {
            pass->setDepthCheckEnabled(true);

            // If inside light geometry then render back faces.
            if (isCameraInsideLight(camera)) {
                pass->setCullingMode(Ogre::CULL_ANTICLOCKWISE);
                pass->setDepthFunction(Ogre::CMPF_GREATER_EQUAL);
            } else {
                pass->setCullingMode(Ogre::CULL_CLOCKWISE);
                pass->setDepthFunction(Ogre::CMPF_LESS_EQUAL);
            }
        }

        Ogre::Camera shadowCamera("ShadowCameraSetupCam", 0);
        shadowCamera._notifyViewport(camera->getViewport());
        Ogre::SceneManager* sceneManager = parentLight->_getManager();
        sceneManager->getShadowCameraSetup()->getShadowCamera(sceneManager, camera, camera->getViewport(), parentLight, &shadowCamera, 0);

        if (params->_findNamedConstantDefinition("shadowCamPos")) {
            params->setNamedConstant("shadowCamPos", shadowCamera.getPosition());
        }

        if (params->_findNamedConstantDefinition("shadowFarClip")) {
            params->setNamedConstant("shadowFarClip", shadowCamera.getFarClipDistance());
        }
    }
}
