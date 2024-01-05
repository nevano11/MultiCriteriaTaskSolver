#ifndef DMLTESTER_CRITERIAAGGREGATIONMETHOD_H
#define DMLTESTER_CRITERIAAGGREGATIONMETHOD_H

#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/OneStepMethod.h"
#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/ProgressingAllAlternativesMethod.h"
#include "../../CriteriaRelation/Relations/WeightCriteriaRelation.h"
#include "AuxiliaryMethods/AggregationOperator.h"
#include "../../MathModel/Converters/Normalizer.h"

class CriteriaAggregationMethod : public OneStepMethod, ProgressingAllAlternativesMethod{
private:
    MathModel* mathModel;
    SolveStatus* solveStatus;
    CriteriaRelation* relation;
    AggregationOperator* aggregationOperator;
    Normalizer* normalizer;

    std::map<int, double> estimateVectorWeight;

    void calculateValiditySolveStatus();
public:
    CriteriaAggregationMethod(AggregationOperator* aggregationOperator);
    CriteriaAggregationMethod(AggregationOperator* aggregationOperator, Normalizer* normalizer);
    CriteriaAggregationMethod(MathModel *mathModel, WeightCriteriaRelation *relation, AggregationOperator* aggregationOperator);
    CriteriaAggregationMethod(MathModel *mathModel, WeightCriteriaRelation *relation, AggregationOperator* aggregationOperator, Normalizer* normalizer);

    ~CriteriaAggregationMethod();

    MathModel* getMathModel();

    void setMathModel(MathModel* mathModel);
    void setCriteriaRelation(CriteriaRelation* relation);
    void setAggregationOperator(AggregationOperator* aggregationOperator);
    void setNormalizer(Normalizer* normalizer);

    SolveStatus* solve();

    std::map<int, double> getEstimateVectorWeight();
    int getBestEstimateVectorId();
};


#endif //DMLTESTER_CRITERIAAGGREGATIONMETHOD_H
