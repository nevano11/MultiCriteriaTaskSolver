#ifndef DMLTESTER_NORMALIZER_H
#define DMLTESTER_NORMALIZER_H

#include "../MathModel.h"

class Normalizer {
public:
    virtual MathModel* getNormalizedMathModel(MathModel* original) = 0;
};


#endif //DMLTESTER_NORMALIZER_H
