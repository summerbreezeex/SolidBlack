#pragma once

#include "Engine/StlCommon.h"

class RandomSequence {
public:
    RandomSequence(unsigned int seed);

    unsigned int getNextNumber();

private:
    unsigned int current;
};