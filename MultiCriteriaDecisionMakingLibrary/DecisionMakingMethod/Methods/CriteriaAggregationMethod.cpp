#include <algorithm>
#include "CriteriaAggregationMethod.h"
#include "../../MathModel/Converters/Normalizers/MinMaxNormalizer.h"

extern "C" {
__declspec(dllexport) CriteriaAggregationMethod *CriteriaAggregationMethod_new(AggregationOperator* oper) {
    return new CriteriaAggregationMethod(oper);
}
__declspec(dllexport) CriteriaAggregationMethod *CriteriaAggregationMethod_new_2(AggregationOperator* oper, Normalizer* normalizer) {
    return new CriteriaAggregationMethod(oper, normalizer);
}
__declspec(dllexport) CriteriaAggregationMethod *CriteriaAggregationMethod_new_3(MathModel* mm, WeightCriteriaRelation* rel, AggregationOperator* oper) {
    return new CriteriaAggregationMethod(mm, rel, oper);
}
__declspec(dllexport) CriteriaAggregationMethod *CriteriaAggregationMethod_new_4(MathModel* mm, WeightCriteriaRelation* rel, AggregationOperator* oper, Normalizer* normalizer) {
    return new CriteriaAggregationMethod(mm, rel, oper, normalizer);
}
__declspec(dllexport) void CriteriaAggregationMethod_delete(CriteriaAggregationMethod* method) {
    delete method;
}
__declspec(dllexport) MathModel* CriteriaAggregationMethod_getMathModel(CriteriaAggregationMethod* method) {
    return method->getMathModel();
}
__declspec(dllexport) void CriteriaAggregationMethod_setMathModel(
        CriteriaAggregationMethod* method, MathModel* mm) {
    method->setMathModel(mm);
}
__declspec(dllexport) void CriteriaAggregationMethod_setCriteriaRelation(
        CriteriaAggregationMethod* method, CriteriaRelation* mm) {
    method->setCriteriaRelation(mm);
}
__declspec(dllexport) void CriteriaAggregationMethod_setNormalizer(
        CriteriaAggregationMethod* method, Normalizer* mm) {
    method->setNormalizer(mm);
}
__declspec(dllexport) void CriteriaAggregationMethod_setOperator(
        CriteriaAggregationMethod* method, AggregationOperator* mm) {
    method->setAggregationOperator(mm);
}
__declspec(dllexport) int* CriteriaAggregationMethod_GetEstimateVectorWeight_Keys(CriteriaAggregationMethod* method) {
    auto map = method->getEstimateVectorWeight();
    int size = map.size();
    int* keys = new int[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.first; });
    return keys;
}
__declspec(dllexport) double* CriteriaAggregationMethod_GetEstimateVectorWeight_Values(CriteriaAggregationMethod* method) {
    auto map = method->getEstimateVectorWeight();
    int size = map.size();
    double* keys = new double[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.second; });
    return keys;
}
__declspec(dllexport) int CriteriaAggregationMethod_GetEstimateVectorWeight_Size(CriteriaAggregationMethod* method) {
    auto map = method->getEstimateVectorWeight();
    return map.size();
}
__declspec(dllexport) int CriteriaAggregationMethod_GetBestEstimateVectorId(CriteriaAggregationMethod* method) {
    return method->getBestEstimateVectorId();
}
__declspec(dllexport) SolveStatus* CriteriaAggregationMethod_solve(CriteriaAggregationMethod* method) {
    return method->solve();
}
}

CriteriaAggregationMethod::CriteriaAggregationMethod(AggregationOperator* aggregationOperator) {
    this->solveStatus = new SolveStatus(None);
    this->aggregationOperator = aggregationOperator;
    normalizer = new MinMaxNormalizer();
}

CriteriaAggregationMethod::CriteriaAggregationMethod(AggregationOperator* aggregationOperator, Normalizer* normalizer) {
    this->solveStatus = new SolveStatus(None);
    this->aggregationOperator = aggregationOperator;
    this->normalizer = normalizer;
}

CriteriaAggregationMethod::CriteriaAggregationMethod(MathModel *mathModel, WeightCriteriaRelation *relation, AggregationOperator* aggregationOperator) {
    this->solveStatus = new SolveStatus(None);
    setMathModel(mathModel);
    this->relation = relation->copy();
    this->aggregationOperator = aggregationOperator;
    normalizer = new MinMaxNormalizer();
}

CriteriaAggregationMethod::CriteriaAggregationMethod(MathModel *mathModel, WeightCriteriaRelation *relation, AggregationOperator* aggregationOperator, Normalizer* normalizer) {
    this->solveStatus = new SolveStatus(None);
    setMathModel(mathModel);
    this->relation = relation->copy();
    this->aggregationOperator = aggregationOperator;
    this->normalizer = normalizer;
}

CriteriaAggregationMethod::~CriteriaAggregationMethod() {
    if (mathModel != nullptr)
        delete mathModel;
    if (relation != nullptr)
        delete relation;
    if (normalizer != nullptr)
        delete normalizer;
    if (aggregationOperator != nullptr)
        delete aggregationOperator;
    if (solveStatus != nullptr)
        delete solveStatus;
}

void CriteriaAggregationMethod::setMathModel(MathModel *mathModel) {
    this->mathModel = new MathModel(*mathModel);
}

void CriteriaAggregationMethod::setCriteriaRelation(CriteriaRelation *relation) {
    this->relation = relation->copy();
}

void CriteriaAggregationMethod::setAggregationOperator(AggregationOperator *aggregationOperator) {
    this->aggregationOperator = aggregationOperator;
}

void CriteriaAggregationMethod::setNormalizer(Normalizer *normalizer) {
    delete this->normalizer;
    this->normalizer = normalizer;
}

SolveStatus *CriteriaAggregationMethod::solve() {
    if (solveStatus->getStatus() == DecisionStatus::Optimal)
        return solveStatus;

    delete solveStatus;
    solveStatus = new SolveStatus(None);

    // method check validity and convert relation to WeightCriteriaRelation
    calculateValiditySolveStatus();

    if (solveStatus->getStatus() != DecisionStatus::None)
        return solveStatus;

    if (aggregationOperator->isNeedNormalizedMathModel()) {
        auto normalizedMathModel = normalizer->getNormalizedMathModel(mathModel);

        if (!normalizedMathModel->isNormalized())
            return new SolveStatus(DecisionStatus::InvalidModel, "failed to normalize math model");

        delete mathModel;
        mathModel = normalizedMathModel;
    }

    estimateVectorWeight = aggregationOperator->getEstimateVectorMark(mathModel, (WeightCriteriaRelation* )relation);
    return this->solveStatus = new SolveStatus(Optimal);
}

void CriteriaAggregationMethod::calculateValiditySolveStatus() {
    if (mathModel == nullptr) {
        solveStatus = new SolveStatus(InvalidModel, "math model was null");
        return;
    }

    if (relation == nullptr) {
        solveStatus = new SolveStatus(InvalidData, "relation was null");
        return;
    }

    if (aggregationOperator == nullptr) {
        solveStatus = new SolveStatus(InvalidData, "aggregationOperator was null");
        return;
    }

    if ((relation = CriteriaRelationConverter::convertToWeightCriteriaRelation(relation)) == nullptr) {
        solveStatus = new SolveStatus(InvalidData, "relation cannot be reduces to AllCriteriaRelation");
        return;
    }

    if (!mathModel->isValid()) {
        solveStatus = new SolveStatus(InvalidModel, "invalid math model");
        return;
    }

    if (!relation->isValid()) {
        solveStatus = new SolveStatus(InvalidData, "criteria relationships are set incorrectly");
    }
}

std::map<int, double> CriteriaAggregationMethod::getEstimateVectorWeight() {
    return this->estimateVectorWeight;
}

int CriteriaAggregationMethod::getBestEstimateVectorId() {
    return aggregationOperator->getBestEstimateVectorId();
}

MathModel *CriteriaAggregationMethod::getMathModel() {
    return mathModel;
}
