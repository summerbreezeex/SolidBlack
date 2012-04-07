#include "RandomSequence.h"

RandomSequence::RandomSequence(unsigned int seed) :
        current(seed) {
}

unsigned int RandomSequence::getNextNumber() {
    unsigned int output = 0, temp = 0;

    for (int i = 0; i < 16; ++i) {
        current = 3039177861 * current + 1;
        temp = current >> 30;

        output = output << 2;
        output = output + temp;
    }

    return output;
}