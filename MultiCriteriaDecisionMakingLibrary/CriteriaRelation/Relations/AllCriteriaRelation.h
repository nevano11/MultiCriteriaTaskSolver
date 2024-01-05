#ifndef DMLTESTER_AllCRITERIARELATION_H
#define DMLTESTER_AllCRITERIARELATION_H

#include "../../MathModel/Components/Criteria.h"
#include "../CriteriaRelation.h"

class AllCriteriaRelation : public CriteriaRelation{
private:
    int criteriaCount;
    int* idSequence;
public:
    AllCriteriaRelation(int criteriaCount, int* idSequence);
    ~AllCriteriaRelation();

    int getSequenceSize();
    int* getIdSequence();

    bool isValid();
    CriteriaRelation* copy();
};

#endif //DMLTESTER_AllCRITERIARELATION_H