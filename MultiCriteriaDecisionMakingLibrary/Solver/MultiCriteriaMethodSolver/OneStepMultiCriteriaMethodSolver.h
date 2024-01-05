#ifndef DMLTESTER_ONESTEPMULTICRITERIAMETHODSOLVER_H
#define DMLTESTER_ONESTEPMULTICRITERIAMETHODSOLVER_H

#include <list>
#include "MultiCriteriaMethodSolver.h"
#include "../../MathModel/MathModel.h"
#include "../../CriteriaRelation/CriteriaRelation.h"
#include "../../DecisionMakingMethod/AbstractMultiCriteriaMethod/MultiCriteriaMethods/OneStepMethod.h"

class OneStepMultiCriteriaMethodSolver : public MultiCriteriaMethodSolver {
private:
    MathModel* mathModel;
    CriteriaRelation* relation;
    std::list<OneStepMethod*> methods;
public:
    OneStepMultiCriteriaMethodSolver(MathModel* mathModel, CriteriaRelation* relation);
    ~OneStepMultiCriteriaMethodSolver();

    void addMethod(OneStepMethod* method);
    void addMethods(std::list<OneStepMethod*> methods);

    std::map<MathModel*, SolveStatus*> solve();
};


#endif //DMLTESTER_ONESTEPMULTICRITERIAMETHODSOLVER_H
