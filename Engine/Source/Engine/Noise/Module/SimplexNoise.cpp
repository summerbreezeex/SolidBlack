#include "Engine/Noise/RandomSequence.h"

#include "SimplexNoise.h"

int grad[12][3] = {
    {1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
    {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
    {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}
};

SimplexNoise::SimplexNoise() {
}

SimplexNoise::SimplexNoise(int seed, Ogre::Real scale) :
        NoiseModule(seed, scale) {
}

Ogre::Real SimplexNoise::getValue(const Ogre::Vector3& position) const {
    assert(isInitialised());

    Ogre::Vector3 scaledPosition(position * getScale());

    Ogre::Real n0, n1, n2, n3;

    const Ogre::Real F3 = 1.0/3.0;

    Ogre::Real s = (scaledPosition.x + scaledPosition.y + scaledPosition.z) * F3;
    int i = fastFloor(scaledPosition.x + s);
    int j = fastFloor(scaledPosition.y + s);
    int k = fastFloor(scaledPosition.z + s);

    const Ogre::Real G3 = 1.0/6.0;
    Ogre::Real t = (i+j+k)*G3;
    Ogre::Real X0 = i-t;
    Ogre::Real Y0 = j-t;
    Ogre::Real Z0 = k-t;
    Ogre::Real x0 = scaledPosition.x - X0;
    Ogre::Real y0 = scaledPosition.y - Y0;
    Ogre::Real z0 = scaledPosition.z - Z0;

    int i1, j1, k1;
    int i2, j2, k2;
    if (x0>=y0) {
        if (y0>=z0) {
            i1=1;
            j1=0;
            k1=0;
            i2=1;
            j2=1;
            k2=0;
        } else if (x0>=z0) {
            i1=1;
            j1=0;
            k1=0;
            i2=1;
            j2=0;
            k2=1;
        } else {
            i1=0;
            j1=0;
            k1=1;
            i2=1;
            j2=0;
            k2=1;
        }
    } else {
        if (y0<z0) {
            i1=0;
            j1=0;
            k1=1;
            i2=0;
            j2=1;
            k2=1;
        } else if (x0<z0) {
            i1=0;
            j1=1;
            k1=0;
            i2=0;
            j2=1;
            k2=1;
        } else {
            i1=0;
            j1=1;
            k1=0;
            i2=1;
            j2=1;
            k2=0;
        }
    }

    Ogre::Real x1 = x0 - i1 + G3;
    Ogre::Real y1 = y0 - j1 + G3;
    Ogre::Real z1 = z0 - k1 + G3;
    Ogre::Real x2 = x0 - i2 + 2.0*G3;
    Ogre::Real y2 = y0 - j2 + 2.0*G3;
    Ogre::Real z2 = z0 - k2 + 2.0*G3;
    Ogre::Real x3 = x0 - 1.0 + 3.0*G3;
    Ogre::Real y3 = y0 - 1.0 + 3.0*G3;
    Ogre::Real z3 = z0 - 1.0 + 3.0*G3;

    int ii = i & 255;
    int jj = j & 255;
    int kk = k & 255;
    int gi0 = permTable[ii+permTable[jj+permTable[kk]]] % 12;
    int gi1 = permTable[ii+i1+permTable[jj+j1+permTable[kk+k1]]] % 12;
    int gi2 = permTable[ii+i2+permTable[jj+j2+permTable[kk+k2]]] % 12;
    int gi3 = permTable[ii+1+permTable[jj+1+permTable[kk+1]]] % 12;

    Ogre::Real t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
    if (t0<0) {
        n0 = 0.0;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad[gi0], x0, y0, z0);
    }

    Ogre::Real t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
    if (t1<0) {
        n1 = 0.0;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad[gi1], x1, y1, z1);
    }

    Ogre::Real t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
    if (t2<0) {
        n2 = 0.0;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad[gi2], x2, y2, z2);
    }

    Ogre::Real t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
    if (t3<0) {
        n3 = 0.0;
    } else {
        t3 *= t3;
        n3 = t3 * t3 * dot(grad[gi3], x3, y3, z3);
    }

    return 32.0 * (n0 + n1 + n2 + n3);
}

void SimplexNoise::initialise() {
    NoiseModule::initialise();

    int integers[256]; // Sequence of integers from 0 to 255.
    Ogre::Real reals[256]; // Sequence of real numbers from -1.0 to 1.0

    // Construct the sequences.
    for (int i = 0; i < 256; ++i) {
        integers[i] = i;
        reals[i] = -1.0 + 2.0 * ((Ogre::Real)i / 255.0);
    }

    RandomSequence randomSequence(getSeed());

    // Shuffle the integer sequence.
    for (int i = 0; i < 256; ++i) {
        int r = randomSequence.getNextNumber() % (i + 1);

        integers[i] = integers[r];
        integers[r] = i;
    }

    // Construct permutation table.
    for (int i = 0; i < 256; ++i) {
        permTable[256 + i] = permTable[i] = integers[i];
    }
}

Ogre::Real SimplexNoise::dot(int g[], Ogre::Real x, Ogre::Real y, Ogre::Real z) {
    return g[0]*x + g[1]*y + g[2]*z;
}

__forceinline int __stdcall SimplexNoise::fastFloor(Ogre::Real x) {
    float y = (float)x;
    y -= 0.5;

    int t;

    __asm fld y
    __asm fistp t

    return t;
}