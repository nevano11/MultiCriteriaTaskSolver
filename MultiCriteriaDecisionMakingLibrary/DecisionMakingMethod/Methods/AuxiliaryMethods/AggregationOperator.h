#ifndef DMLTESTER_AGGREGATIONOPERATOR_H
#define DMLTESTER_AGGREGATIONOPERATOR_H

#include "../../../MathModel/MathModel.h"
#include "../../../CriteriaRelation/Relations/WeightCriteriaRelation.h"

class AggregationOperator {
protected:
    std::map<int, double> estimateVectorValue;
public:
    virtual std::map<int, double> getEstimateVectorMark(MathModel* normalizedMathModel, WeightCriteriaRelation* weightCriteriaRelation) = 0;
    virtual double getBestValue() = 0;
    virtual int getBestEstimateVectorId() = 0;
    virtual bool isNeedNormalizedMathModel() = 0;
};


#endif //DMLTESTER_AGGREGATIONOPERATOR_H
