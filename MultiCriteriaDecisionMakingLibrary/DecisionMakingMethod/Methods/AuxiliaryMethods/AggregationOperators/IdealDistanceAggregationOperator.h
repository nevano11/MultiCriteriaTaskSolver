#ifndef DMLTESTER_IDEALDISTANCEAGGREGATIONOPERATOR_H
#define DMLTESTER_IDEALDISTANCEAGGREGATIONOPERATOR_H

#include "../AggregationOperator.h"

// TODO сделать самостоятельный выбор идеального значения
class IdealDistanceAggregationOperator : public AggregationOperator {
protected:
    std::map<int, double> estimateVectorValue;
public:
    std::map<int, double> getEstimateVectorMark(MathModel* mathModel, WeightCriteriaRelation* weightCriteriaRelation);
    double getBestValue();
    int getBestEstimateVectorId();
    bool isNeedNormalizedMathModel();
};


#endif //DMLTESTER_IDEALDISTANCEAGGREGATIONOPERATOR_H
