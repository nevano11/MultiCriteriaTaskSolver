#ifndef DMLTESTER_CRITERIARELATION_H
#define DMLTESTER_CRITERIARELATION_H

#include "../MathModel/Components/Criteria.h"

class CriteriaRelation {
public:
    virtual bool isValid() = 0;
    virtual CriteriaRelation* copy() = 0;
};

#endif //DMLTESTER_CRITERIARELATION_H
