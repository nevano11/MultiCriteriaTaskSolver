#ifndef DMLTESTER_ADDICTIVEAGGREGATIONOPERATOR_H
#define DMLTESTER_ADDICTIVEAGGREGATIONOPERATOR_H

#include "../AggregationOperator.h"

class AddictiveAggregationOperator : public AggregationOperator {
protected:
    std::map<int, double> estimateVectorValue;
public:
    std::map<int, double> getEstimateVectorMark(MathModel* normalizedMathModel, WeightCriteriaRelation* weightCriteriaRelation);
    double getBestValue();
    int getBestEstimateVectorId();
    bool isNeedNormalizedMathModel();
};


#endif //DMLTESTER_ADDICTIVEAGGREGATIONOPERATOR_H
