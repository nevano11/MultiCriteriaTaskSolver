
#ifndef MULTICRITERIADECISIONMAKINGLIBRARY_ELECTREMETHOD_H
#define MULTICRITERIADECISIONMAKINGLIBRARY_ELECTREMETHOD_H


#include "../../MathModel/MathModel.h"
#include "../SolveStatus.h"
#include "../../CriteriaRelation/CriteriaRelation.h"
#include "../IntermediateMethodData/IntermediateMethodData.h"
#include "../DecisionMakerInfo/DecisionMakerInfo.h"
#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/MultiStepMethod.h"
#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/ProgressingAllAlternativesMethod.h"

class ElectreMethod : public MultiStepMethod, ProgressingAllAlternativesMethod {
private:
    MathModel* mathModel;
    SolveStatus* solveStatus;
    CriteriaRelation* relation;

    double** agreementMatrix;
    double** disagreementMatrix;
public:
    ElectreMethod();
    ElectreMethod(MathModel* mathModel, CriteriaRelation* relation);
    ~ElectreMethod();

    SolveStatus* makeIteration(DecisionMakerInfo* decisionMakingInfo);
    IntermediateMethodData* getIntermediateMethodData();

    SolveStatus* solve();

    void setMathModel(MathModel* mathModel);
    void setCriteriaRelation(CriteriaRelation* relation);

    MathModel* getMathModel();
    int getBestEstimateVectorId();
};


#endif //MULTICRITERIADECISIONMAKINGLIBRARY_ELECTREMETHOD_H
