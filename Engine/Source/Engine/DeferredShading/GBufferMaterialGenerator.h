#pragma once

#include "Engine/DeferredShading/MaterialGenerator.h"

class GBufferMaterialGenerator :
            public MaterialGenerator {
public:
    GBufferMaterialGenerator();

    enum GBufferPermutations {
        // (Regular) Textures
        GBP_NO_TEXTURES = 0x00000000,
        GBP_ONE_TEXTURE = 0x00000001,
        GBP_TWO_TEXTURES = 0x00000002,
        GBP_THREE_TEXTURES = 0x00000003,
        GBP_TEXTURE_MASK = 0x0000000F,

        // Material properties
        GBP_HAS_DIFFUSE_COLOUR = 0x00000010,

        // The number of texture coordinate sets
        GBP_NO_TEXCOORDS = 0x00000000,
        GBP_ONE_TEXCOORD = 0x00000100,
        GBP_TWO_TEXCOORDS = 0x00000200,
        GBP_TEXCOORD_MASK = 0x00000700,

        // Do we have a normal map
        GBP_NORMAL_MAP =  0x00000800,

        // Are we skinned?
        GBP_SKINNED = 0x00010000
    };
};

class GBufferMaterialGeneratorImpl :
            public MaterialGenerator::Impl {
public:
    GBufferMaterialGeneratorImpl(const Ogre::String& baseName) : baseName(baseName) {}

protected:
    Ogre::String baseName;
    virtual Ogre::GpuProgramPtr generateVertexShader(MaterialGenerator::Perm permutation);
    virtual Ogre::GpuProgramPtr generateFragmentShader(MaterialGenerator::Perm permutation);
    virtual Ogre::MaterialPtr generateTemplateMaterial(MaterialGenerator::Perm permutation);
};