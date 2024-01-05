#ifndef LIBRARYTESTS_MULTISTEPMULTICRITERIAMETHODSOLVER_H
#define LIBRARYTESTS_MULTISTEPMULTICRITERIAMETHODSOLVER_H

#include <list>
#include "MultiCriteriaMethodSolver.h"
#include "../../MathModel/MathModel.h"
#include "../../CriteriaRelation/CriteriaRelation.h"
#include "../../DecisionMakingMethod/AbstractMultiCriteriaMethod/MultiCriteriaMethods/MultiStepMethod.h"

#include "MultiCriteriaMethodSolver.h"

class MultiStepMultiCriteriaMethodSolver : public MultiCriteriaMethodSolver {
private:
    MathModel* mathModel;
    CriteriaRelation* relation;
    MultiStepMethod* method = nullptr;
    SolveStatus* methodSolveStatus;
    IntermediateMethodData* methodData = nullptr;
public:
    MultiStepMultiCriteriaMethodSolver(MathModel* mathModel, CriteriaRelation* relation);
    ~MultiStepMultiCriteriaMethodSolver();

    void setMethod(MultiStepMethod* method);

    SolveStatus* getCurrentSolveStatus();
    MathModel* getMethodMathModel();

    void makeIteration(DecisionMakerInfo* makerInfo);
    IntermediateMethodData* getMethodData();
};


#endif //LIBRARYTESTS_MULTISTEPMULTICRITERIAMETHODSOLVER_H
