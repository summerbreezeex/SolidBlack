#pragma once

#include <OgreMaterial.h>
#include <OgreStringVector.h>

#include "Engine/StlCommon.h"

class MaterialGenerator {
public:
    typedef Ogre::uint32 Perm;

    virtual ~MaterialGenerator();

    const Ogre::MaterialPtr& getMaterial(Perm permutation);

    class Impl {
    public:
        virtual ~Impl() { }

        virtual Ogre::GpuProgramPtr generateVertexShader(Perm permutation) = 0;
        virtual Ogre::GpuProgramPtr generateFragmentShader(Perm permutation) = 0;
        virtual Ogre::MaterialPtr generateTemplateMaterial(Perm permutation) = 0;
    };

protected:
    MaterialGenerator();

    const Ogre::GpuProgramPtr& getVertexShader(Perm permutation);
    const Ogre::GpuProgramPtr& getFragmentShader(Perm permutation);
    const Ogre::MaterialPtr& getTemplateMaterial(Perm permutation);

    Ogre::String materialBaseName;

    Perm vertexShaderMask;
    Perm fragmentShaderMask;
    Perm materialMask;

    Impl* impl;

    typedef Ogre::map<Perm, Ogre::GpuProgramPtr>::type ProgramMap;
    ProgramMap vertexShaders;
    ProgramMap fragmentShaders;

    typedef Ogre::map<Perm, Ogre::MaterialPtr>::type MaterialMap;
    MaterialMap templateMaterials;
    MaterialMap materials;
};