#ifndef DMLTESTER_PROPORTIONALMETHOD_H
#define DMLTESTER_PROPORTIONALMETHOD_H

#include "../WeightCriteriaRelation.h"
#include <map>

// TODO isValid Method
class ProportionalMethod : public WeightCriteriaRelation{
private:
    std::map<int, double> weightMap;
protected:
    std::map<int, double> criteriaIdWeightMap;
    int criteriaCount;
public:
    ProportionalMethod(int criteriaCount, std::map<int, double> criteriaIdWeightMap);

    int getCriteriaCount();
    std::map<int, double> getCriteriaWeightMap();
    bool isValid();
    CriteriaRelation* copy();
};


#endif //DMLTESTER_PROPORTIONALMETHOD_H
