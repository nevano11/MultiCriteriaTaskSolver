#ifndef DMLTESTER_WEIGHTCRITERIARELATION_H
#define DMLTESTER_WEIGHTCRITERIARELATION_H

#include "../CriteriaRelation.h"
#include <map>

class WeightCriteriaRelation : public CriteriaRelation{
protected:
    std::map<int, double> criteriaIdWeightMap;
    int criteriaCount;
public:
    virtual std::map<int, double> getCriteriaWeightMap() = 0;
    virtual int getCriteriaCount() = 0;
    virtual bool isValid() = 0;
    virtual CriteriaRelation* copy() = 0;
};


#endif //DMLTESTER_WEIGHTCRITERIARELATION_H
