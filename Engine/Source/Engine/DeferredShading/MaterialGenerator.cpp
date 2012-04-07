#include "MaterialGenerator.h"

#include "OgreStringConverter.h"
#include "OgreException.h"

#include "OgrePass.h"
#include "OgreTechnique.h"

#include "OgreHighLevelGpuProgram.h"
#include "OgreHighLevelGpuProgramManager.h"

MaterialGenerator::MaterialGenerator() :
        vertexShaderMask(0),
        fragmentShaderMask(0),
        materialMask(0),
        impl(0) {
}

MaterialGenerator::~MaterialGenerator() {
    delete impl;
}

const Ogre::MaterialPtr& MaterialGenerator::getMaterial(Perm permutation) {
    auto it = materials.find(permutation);

    if (it != materials.end()) {
        return it->second;
    } else {
        Ogre::MaterialPtr templateMaterial = getTemplateMaterial(permutation & materialMask);

        Ogre::GpuProgramPtr vertexShader = getVertexShader(permutation & vertexShaderMask);
        Ogre::GpuProgramPtr fragmentShader = getFragmentShader(permutation & fragmentShaderMask);

        std::string name = materialBaseName + Ogre::StringConverter::toString(permutation);

        Ogre::MaterialPtr material = templateMaterial->clone(name);
        Ogre::Technique* technique = material->getTechnique(0);

        Ogre::Pass* pass = technique->getPass(0);
        pass->setFragmentProgram(fragmentShader->getName());
        pass->setVertexProgram(vertexShader->getName());

        materials[permutation] = material;
        return materials[permutation];
    }
}

const Ogre::GpuProgramPtr& MaterialGenerator::getVertexShader(Perm permutation) {
    auto it = vertexShaders.find(permutation);

    if (it != vertexShaders.end()) {
        return it->second;
    } else {
        vertexShaders[permutation] = impl->generateVertexShader(permutation);
        return vertexShaders[permutation];
    }
}

const Ogre::GpuProgramPtr& MaterialGenerator::getFragmentShader(Perm permutation) {
    auto it = fragmentShaders.find(permutation);

    if (it != fragmentShaders.end()) {
        return it->second;
    } else {
        fragmentShaders[permutation] = impl->generateFragmentShader(permutation);
        return fragmentShaders[permutation];
    }
}

const Ogre::MaterialPtr& MaterialGenerator::getTemplateMaterial(Perm permutation) {
    auto it = templateMaterials.find(permutation);

    if (it != templateMaterials.end()) {
        return it->second;
    } else {
        templateMaterials[permutation] = impl->generateTemplateMaterial(permutation);
        return templateMaterials[permutation];
    }
}