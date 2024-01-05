#include "MultiStepMultiCriteriaMethodSolver.h"

extern "C" {
__declspec(dllexport) MultiStepMultiCriteriaMethodSolver *MultiStepMultiCriteriaMethodSolver_new(MathModel* mathModel, CriteriaRelation* relation) {
    return new MultiStepMultiCriteriaMethodSolver(mathModel, relation);
}
__declspec(dllexport) void MultiStepMultiCriteriaMethodSolver_delete(MultiStepMultiCriteriaMethodSolver* solver) {
    delete solver;
}
__declspec(dllexport) void MultiStepMultiCriteriaMethodSolver_setMethod(MultiStepMultiCriteriaMethodSolver* solver, MultiStepMethod* method) {
    solver->setMethod(method);
}
__declspec(dllexport) SolveStatus* MultiStepMultiCriteriaMethodSolver_getCurrentSolveStatus(MultiStepMultiCriteriaMethodSolver *obj) {
    return obj->getCurrentSolveStatus();
}
__declspec(dllexport) MathModel* MultiStepMultiCriteriaMethodSolver_getMethodMathModel(MultiStepMultiCriteriaMethodSolver *obj) {
    return obj->getMethodMathModel();
}
__declspec(dllexport) void MultiStepMultiCriteriaMethodSolver_makeIteration(MultiStepMultiCriteriaMethodSolver *obj, DecisionMakerInfo* methodData) {
    obj->makeIteration(methodData);
}
__declspec(dllexport) IntermediateMethodData* MultiStepMultiCriteriaMethodSolver_getMethodData(MultiStepMultiCriteriaMethodSolver *obj) {
    return obj->getMethodData();
}
}

MultiStepMultiCriteriaMethodSolver::MultiStepMultiCriteriaMethodSolver(MathModel *mathModel,
                                                                       CriteriaRelation *relation) {
    this->mathModel = mathModel;
    this->relation = relation;
    methodSolveStatus = new SolveStatus(DecisionStatus::None);
}

MultiStepMultiCriteriaMethodSolver::~MultiStepMultiCriteriaMethodSolver() {
    if (method != nullptr)
        delete method;
    if (methodData != nullptr)
        delete methodData;
    if (mathModel != nullptr)
        delete mathModel;
    if (relation != nullptr)
        delete relation;
    if (methodSolveStatus != nullptr)
        delete methodSolveStatus;
}

void MultiStepMultiCriteriaMethodSolver::setMethod(MultiStepMethod *method) {
    if (this->method != nullptr)
        delete this->method;
    this->method = method;
}

void MultiStepMultiCriteriaMethodSolver::makeIteration(DecisionMakerInfo *makerInfo) {
    std::pair<MultiStepMethod *, SolveStatus *> result;
    if (method != nullptr && makerInfo != nullptr)
        methodSolveStatus = method->makeIteration(makerInfo);
    delete makerInfo;
}

IntermediateMethodData *MultiStepMultiCriteriaMethodSolver::getMethodData() {
    if (methodData != nullptr)
        delete methodData;
    return method == nullptr ? nullptr : methodData = method->getIntermediateMethodData();
}

SolveStatus *MultiStepMultiCriteriaMethodSolver::getCurrentSolveStatus() {
    return methodSolveStatus;
}

MathModel *MultiStepMultiCriteriaMethodSolver::getMethodMathModel() {
    return method != nullptr ? method->getMathModel() : nullptr;
}
