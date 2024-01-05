#include <algorithm>
#include "OneStepMultiCriteriaMethodSolver.h"

extern "C" {
__declspec(dllexport) OneStepMultiCriteriaMethodSolver *OneStepMultiCriteriaMethodSolver_new(MathModel* mathModel, CriteriaRelation* relation) {
    return new OneStepMultiCriteriaMethodSolver(mathModel, relation);
}
__declspec(dllexport) void OneStepMultiCriteriaMethodSolver_delete(OneStepMultiCriteriaMethodSolver* solver) {
    delete solver;
}
__declspec(dllexport) void OneStepMultiCriteriaMethodSolver_addMethod(OneStepMultiCriteriaMethodSolver* solver, OneStepMethod* method) {
    solver->addMethod(method);
}
__declspec(dllexport) void OneStepMultiCriteriaMethodSolver_addMethods(OneStepMultiCriteriaMethodSolver* solver, OneStepMethod** methods, int methodCount) {
    std::list<OneStepMethod*> methodList;
    for (int i = 0; i < methodCount; ++i) {
        methodList.push_back(methods[i]);
    }
    solver->addMethods(methodList);
}
__declspec(dllexport) MathModel** OneStepMultiCriteriaMethodSolver_solve_Keys(OneStepMultiCriteriaMethodSolver* solver) {
    auto map = solver->solve();
    int size = map.size();
    MathModel** keys = new MathModel* [size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<MathModel*, SolveStatus*>& p) { return p.first; });
    return keys;
}
__declspec(dllexport) SolveStatus** OneStepMultiCriteriaMethodSolver_solve_Values(OneStepMultiCriteriaMethodSolver* solver) {
    auto map = solver->solve();
    int size = map.size();
    SolveStatus** values = new SolveStatus* [size];
    std::transform(map.begin(), map.end(), values,
                   [](const std::pair<MathModel*, SolveStatus*>& p) { return p.second; });
    return values;
}
__declspec(dllexport) int OneStepMultiCriteriaMethodSolver_solve_Size(OneStepMultiCriteriaMethodSolver* solver) {
    auto map = solver->solve();
    return map.size();
}
}

OneStepMultiCriteriaMethodSolver::OneStepMultiCriteriaMethodSolver(MathModel *mathModel, CriteriaRelation *relation) {
    this->mathModel = mathModel;
    this->relation = relation;
}

OneStepMultiCriteriaMethodSolver::~OneStepMultiCriteriaMethodSolver() {
    for (const auto &item: methods) {
        if (item != nullptr)
            delete item;
    }
    if (mathModel != nullptr)
        delete mathModel;
    if (relation != nullptr)
        delete relation;
}

void OneStepMultiCriteriaMethodSolver::addMethod(OneStepMethod* method) {
    methods.push_back(method);
}

void OneStepMultiCriteriaMethodSolver::addMethods(std::list<OneStepMethod*> methods) {
    for (const auto &method: methods) {
        addMethod(method);
    }
}

std::map<MathModel*, SolveStatus*> OneStepMultiCriteriaMethodSolver::solve() {
    std::map<MathModel*, SolveStatus*> result;

    for (const auto &method: methods) {
        method->setMathModel(mathModel);
        method->setCriteriaRelation(relation);

        result.emplace(method->getMathModel(), method->solve());
    }
    return result;
}