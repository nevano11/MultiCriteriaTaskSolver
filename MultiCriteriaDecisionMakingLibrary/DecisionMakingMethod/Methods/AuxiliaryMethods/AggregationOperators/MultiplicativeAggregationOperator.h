#ifndef DMLTESTER_MULTIPLICATIVEAGGREGATIONOPERATOR_H
#define DMLTESTER_MULTIPLICATIVEAGGREGATIONOPERATOR_H

#include "../AggregationOperator.h"

class MultiplicativeAggregationOperator : public AggregationOperator {
protected:
    std::map<int, double> estimateVectorValue;
public:
    std::map<int, double> getEstimateVectorMark(MathModel* normalizedMathModel, WeightCriteriaRelation* weightCriteriaRelation);
    double getBestValue();
    int getBestEstimateVectorId();
    bool isNeedNormalizedMathModel();
};


#endif //DMLTESTER_MULTIPLICATIVEAGGREGATIONOPERATOR_H
