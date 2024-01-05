#ifndef DMLTESTER_SUCCESSIVECONCESSIONSMETHOD_H
#define DMLTESTER_SUCCESSIVECONCESSIONSMETHOD_H

#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/MultiStepMethod.h"
#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/SequentialNarrowingAlternativesMethod.h"

class SuccessiveConcessionsMethod : public MultiStepMethod, SequentialNarrowingAlternativesMethod {
private:
    MathModel* mathModel;
    SolveStatus* solveStatus;
    CriteriaRelation* relation;

    int criteriaNum = 0;

    void calculateValiditySolveStatus();
public:
    SuccessiveConcessionsMethod();
    SuccessiveConcessionsMethod(MathModel* mathModel, CriteriaRelation* relation);
    ~SuccessiveConcessionsMethod();

    IntermediateMethodData* getIntermediateMethodData();
    SolveStatus* solve();
    SolveStatus* makeIteration(DecisionMakerInfo* decisionMakingInfo);

    void setMathModel(MathModel* mathModel);
    void setCriteriaRelation(CriteriaRelation* relation);

    MathModel* getMathModel();
    int getBestEstimateVectorId();
};


#endif //DMLTESTER_SUCCESSIVECONCESSIONSMETHOD_H
