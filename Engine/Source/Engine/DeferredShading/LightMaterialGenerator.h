#pragma once

#include "Engine/DeferredShading/MaterialGenerator.h"

class LightMaterialGenerator :
            public MaterialGenerator {
public:
    enum MaterialId {
        MI_POINT = 0x01,
        MI_SPOTLIGHT = 0x02,
        MI_DIRECTIONAL = 0x04,
        MI_ATTENUATED = 0x08,
        MI_SPECULAR = 0x10,
        MI_SHADOW_CASTER = 0x20
    };

    LightMaterialGenerator();
    virtual ~LightMaterialGenerator() { }
};

class LightMaterialGeneratorCG :
            public MaterialGenerator::Impl {
public:
    typedef MaterialGenerator::Perm Perm;

    LightMaterialGeneratorCG(const Ogre::String &baseName);

    virtual Ogre::GpuProgramPtr generateVertexShader(Perm permutation);
    virtual Ogre::GpuProgramPtr generateFragmentShader(Perm permutation);
    virtual Ogre::MaterialPtr generateTemplateMaterial(Perm permutation);

private:
    Ogre::String getPPDefines(Perm permutation);
    void setUpBaseParameters(const Ogre::GpuProgramParametersSharedPtr& params);

    Ogre::String baseName;
    Ogre::String masterSource;
};