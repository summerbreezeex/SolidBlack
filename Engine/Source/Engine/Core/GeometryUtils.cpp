#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
#include <OgreHardwareBufferManager.h>

#include "GeometryUtils.h"

void GeometryUtils::createSphere(Ogre::VertexData*& vertexData, Ogre::IndexData*& indexData, Ogre::Real radius, int numRings, int numSegments, bool normals, bool texCoords) {
    assert(vertexData && indexData);

    // define the vertex format
    Ogre::VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
    size_t currOffset = 0;

    vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    if (normals) {
        vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
        currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    }

    if (texCoords) {
        vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES, 0);
        currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
    }

    vertexData->vertexCount = (numRings + 1) * (numSegments + 1);
    Ogre::HardwareVertexBufferSharedPtr vBuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(vertexDecl->getVertexSize(0), vertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::VertexBufferBinding* binding = vertexData->vertexBufferBinding;
    binding->setBinding(0, vBuf);
    float* pVertex = static_cast<float*>(vBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    // allocate index buffer
    indexData->indexCount = 6 * numRings * (numSegments + 1);
    indexData->indexBuffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, indexData->indexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::HardwareIndexBufferSharedPtr iBuf = indexData->indexBuffer;
    unsigned short* pIndices = static_cast<unsigned short*>(iBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    Ogre::Real fDeltaRingAngle = (Ogre::Math::PI / numRings);
    Ogre::Real fDeltaSegAngle = (2 * Ogre::Math::PI / numSegments);
    unsigned short wVerticeIndex = 0 ;

    // Generate the group of rings for the sphere
    for ( int ring = 0; ring <= numRings; ring++ ) {
        Ogre::Real r0 = radius * sin(ring * fDeltaRingAngle);
        Ogre::Real y0 = radius * cos(ring * fDeltaRingAngle);

        // Generate the group of segments for the current ring
        for (int seg = 0; seg <= numSegments; seg++) {
            Ogre::Real x0 = r0 * sin(seg * fDeltaSegAngle);
            Ogre::Real z0 = r0 * cos(seg * fDeltaSegAngle);

            // Add one vertex to the strip which makes up the sphere
            *pVertex++ = (float)x0;
            *pVertex++ = (float)y0;
            *pVertex++ = (float)z0;

            if (normals) {
                Ogre::Vector3 vNormal = Ogre::Vector3(x0, y0, z0).normalisedCopy();
                *pVertex++ = (float)vNormal.x;
                *pVertex++ = (float)vNormal.y;
                *pVertex++ = (float)vNormal.z;
            }
            if (texCoords) {
                *pVertex++ = (float)seg / (float)numSegments;
                *pVertex++ = (float)ring / (float)numRings;
            }

            if (ring != numRings) {
                *pIndices++ = wVerticeIndex + numSegments + 1;
                *pIndices++ = wVerticeIndex;
                *pIndices++ = wVerticeIndex + numSegments;
                *pIndices++ = wVerticeIndex + numSegments + 1;
                *pIndices++ = wVerticeIndex + 1;
                *pIndices++ = wVerticeIndex;
                wVerticeIndex ++;
            }
        }
    }

    vBuf->unlock();
    iBuf->unlock();
}

void GeometryUtils::createCone(Ogre::VertexData*& vertexData, Ogre::IndexData*& indexData, Ogre::Real radius, Ogre::Real height, int numVerticesInBase) {
    assert(vertexData && indexData);

    // define the vertex format
    Ogre::VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
    // positions
    vertexDecl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);

    // allocate the vertex buffer
    vertexData->vertexCount = numVerticesInBase + 1;
    Ogre::HardwareVertexBufferSharedPtr vBuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(vertexDecl->getVertexSize(0), vertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::VertexBufferBinding* binding = vertexData->vertexBufferBinding;
    binding->setBinding(0, vBuf);
    float* pVertex = static_cast<float*>(vBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    // allocate index buffer - cone and base
    indexData->indexCount = (3 * numVerticesInBase) + (3 * (numVerticesInBase - 2));
    indexData->indexBuffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, indexData->indexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::HardwareIndexBufferSharedPtr iBuf = indexData->indexBuffer;
    unsigned short* pIndices = static_cast<unsigned short*>(iBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    //Positions : cone head and base
    for (int i=0; i<3; i++)
        *pVertex++ = 0.0;

    //Base :
    Ogre::Real fDeltaBaseAngle = (2 * Ogre::Math::PI) / numVerticesInBase;
    for (int i=0; i<numVerticesInBase; i++) {
        Ogre::Real angle = i * fDeltaBaseAngle;
        *pVertex++ = (float)radius * cosf((float)angle);
        *pVertex++ = (float)height;
        *pVertex++ = (float)radius * sinf((float)angle);
    }

    //Indices :
    //Cone head to vertices
    for (int i=0; i<numVerticesInBase; i++) {
        *pIndices++ = 0;
        *pIndices++ = (i%numVerticesInBase) + 1;
        *pIndices++ = ((i+1)%numVerticesInBase) + 1;
    }
    //Cone base
    for (int i=0; i<numVerticesInBase-2; i++) {
        *pIndices++ = 1;
        *pIndices++ = i + 3;
        *pIndices++ = i + 2;
    }

    // Unlock
    vBuf->unlock();
    iBuf->unlock();
}

void GeometryUtils::createQuad(Ogre::VertexData*& vertexData) {
    assert(vertexData);

    vertexData->vertexCount = 4;
    vertexData->vertexStart = 0;

    Ogre::VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
    Ogre::VertexBufferBinding* bind = vertexData->vertexBufferBinding;

    vertexDecl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);

    Ogre::HardwareVertexBufferSharedPtr vbuf =
        Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
            vertexDecl->getVertexSize(0),
            vertexData->vertexCount,
            Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    // Bind buffer
    bind->setBinding(0, vbuf);
    // Upload data
    float data[] = {
        -1,1,-1,  // corner 1
        -1,-1,-1, // corner 2
        1,1,-1,   // corner 3
        1,-1,-1
    }; // corner 4
    vbuf->writeData(0, sizeof(data), data, true);
}