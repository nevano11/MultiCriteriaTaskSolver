#ifndef MULTICRITERIADECISIONMAKINGLIBRARY_UNIFIER_H
#define MULTICRITERIADECISIONMAKINGLIBRARY_UNIFIER_H


#include "../MathModel.h"

class Unifier {
    public:
        virtual MathModel* getUnifiedMathModel(MathModel* original) = 0;
};


#endif //MULTICRITERIADECISIONMAKINGLIBRARY_UNIFIER_H
