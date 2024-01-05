#include "AddictiveAggregationOperator.h"
#include <climits>
#include <algorithm>

extern "C" {
__declspec(dllexport) AddictiveAggregationOperator *AddictiveAggregationOperator_new() {
    return new AddictiveAggregationOperator();
}
__declspec(dllexport) int *AddictiveAggregationOperator_getEstimateVectorMark_Keys(
        AddictiveAggregationOperator* oper,  MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    int size = map.size();
    int* keys = new int[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.first; });
    return keys;
}
__declspec(dllexport) double* AddictiveAggregationOperator_getEstimateVectorMark_Values(
        AddictiveAggregationOperator* oper, MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    int size = map.size();
    double* values = new double[size];
    std::transform(map.begin(), map.end(), values,
                   [](const std::pair<int, double>& p) { return p.second; });
    return values;
}
__declspec(dllexport) int AddictiveAggregationOperator_getEstimateVectorMark_Size(
        AddictiveAggregationOperator* oper, MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    return map.size();
}
__declspec(dllexport) double AddictiveAggregationOperator_GetBestValue(AddictiveAggregationOperator* oper) {
    return oper->getBestValue();
}
__declspec(dllexport) int AddictiveAggregationOperator_GetBestEstimateVectorId(AddictiveAggregationOperator* oper) {
    return oper->getBestEstimateVectorId();
}
__declspec(dllexport) bool AddictiveAggregationOperator_IsNeedNormalizedMathModel(AddictiveAggregationOperator* oper) {
    return oper->isNeedNormalizedMathModel();
}
}

std::map<int, double> AddictiveAggregationOperator::getEstimateVectorMark(MathModel *normalizedMathModel,
                                                           WeightCriteriaRelation *weightCriteriaRelation) {
    auto criteriaWeightMap = weightCriteriaRelation->getCriteriaWeightMap();
    int estimateVectorCount = normalizedMathModel->getEstimateVectorCount();
    auto estimateVectorArray = normalizedMathModel->getEstimateVectorArray();

    int criteriaCount = normalizedMathModel->getCriteriaCount();

    for (int i = 0; i < estimateVectorCount; ++i) {
        auto estimateVector = estimateVectorArray[i];
        auto marks = estimateVector->getMarks();
        double res = 0;
        for (int j = 0; j < criteriaCount; ++j) {
            int criteriaId = normalizedMathModel->getCriteriaArray()[j]->getId();
            res += weightCriteriaRelation->getCriteriaWeightMap()[criteriaId] * marks[j];
        }
        estimateVectorValue.emplace(estimateVector->getId(), res);
    }

    return estimateVectorValue;
}

double AddictiveAggregationOperator::getBestValue() {
    if (estimateVectorValue.empty())
        return -1;

    double max = INT_MIN;
    for (const auto &item: estimateVectorValue) {
        max = item.second > max ? item.second : max;
    }
    return max;
}

int AddictiveAggregationOperator::getBestEstimateVectorId() {
    if (estimateVectorValue.empty())
        return -1;

    double max = INT_MIN;
    int id = INT_MIN;
    for (const auto &item: estimateVectorValue) {
        if (item.second > max) {
            max = item.second;
            id = item.first;
        }
    }
    return id;
}

bool AddictiveAggregationOperator::isNeedNormalizedMathModel() {
    return true;
}
