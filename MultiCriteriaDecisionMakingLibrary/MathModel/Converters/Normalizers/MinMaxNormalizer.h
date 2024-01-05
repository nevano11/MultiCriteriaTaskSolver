#ifndef DMLTESTER_MINMAXNORMALIZER_H
#define DMLTESTER_MINMAXNORMALIZER_H

#include "../Normalizer.h"

class MinMaxNormalizer : public Normalizer {
public:
    MathModel* getNormalizedMathModel(MathModel* original);
};


#endif //DMLTESTER_MINMAXNORMALIZER_H
