#ifndef DMLTESTER_SIMPLECRITERIARELATION_H
#define DMLTESTER_SIMPLECRITERIARELATION_H

#include "../CriteriaRelation.h"
#include "TwoCriteriaRelation.h"

class SimpleCriteriaRelation : public CriteriaRelation{
private:
    TwoCriteriaRelation** twoCriteriaRelationArray;
    int criteriaCount;
    int relationCount;
public:
    SimpleCriteriaRelation(TwoCriteriaRelation** twoCriteriaRelationArray, int criteriaCount, int relationCount);
    SimpleCriteriaRelation();

    int getRelationCount();
    int getCriteriaCount();
    TwoCriteriaRelation** getTwoCriteriaRelationArray();

    bool isValid();
    CriteriaRelation* copy();
};


#endif //DMLTESTER_SIMPLECRITERIARELATION_H
