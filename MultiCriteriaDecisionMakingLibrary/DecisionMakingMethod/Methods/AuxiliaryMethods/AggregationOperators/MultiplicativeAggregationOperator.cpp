#include "MultiplicativeAggregationOperator.h"

#include <climits>
#include <cmath>
#include <algorithm>

extern "C" {
__declspec(dllexport) MultiplicativeAggregationOperator *MultiplicativeAggregationOperator_new() {
    return new MultiplicativeAggregationOperator();
}
__declspec(dllexport) int *MultiplicativeAggregationOperator_getEstimateVectorMark_Keys(
        MultiplicativeAggregationOperator* oper,  MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    int size = map.size();
    int* keys = new int[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.first; });
    return keys;
}
__declspec(dllexport) double* MultiplicativeAggregationOperator_getEstimateVectorMark_Values(
        MultiplicativeAggregationOperator* oper, MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    int size = map.size();
    double* values = new double[size];
    std::transform(map.begin(), map.end(), values,
                   [](const std::pair<int, double>& p) { return p.second; });
    return values;
}
__declspec(dllexport) int MultiplicativeAggregationOperator_getEstimateVectorMark_Size(
        MultiplicativeAggregationOperator* oper, MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    return map.size();
}
__declspec(dllexport) double MultiplicativeAggregationOperator_GetBestValue(MultiplicativeAggregationOperator* oper) {
    return oper->getBestValue();
}
__declspec(dllexport) int MultiplicativeAggregationOperator_GetBestEstimateVectorId(MultiplicativeAggregationOperator* oper) {
    return oper->getBestEstimateVectorId();
}
__declspec(dllexport) bool MultiplicativeAggregationOperator_IsNeedNormalizedMathModel(MultiplicativeAggregationOperator* oper) {
    return oper->isNeedNormalizedMathModel();
}
}

std::map<int, double> MultiplicativeAggregationOperator::getEstimateVectorMark(MathModel *normalizedMathModel,
                                                                          WeightCriteriaRelation *weightCriteriaRelation) {
    auto criteriaWeightMap = weightCriteriaRelation->getCriteriaWeightMap();
    int estimateVectorCount = normalizedMathModel->getEstimateVectorCount();
    auto estimateVectorArray = normalizedMathModel->getEstimateVectorArray();

    int criteriaCount = normalizedMathModel->getCriteriaCount();

    for (int i = 0; i < estimateVectorCount; ++i) {
        auto estimateVector = estimateVectorArray[i];
        auto marks = estimateVector->getMarks();
        double res = 1;
        for (int j = 0; j < criteriaCount; ++j) {
            int criteriaId = normalizedMathModel->getCriteriaArray()[j]->getId();
            res *= pow(marks[j], weightCriteriaRelation->getCriteriaWeightMap()[criteriaId]);
        }
        estimateVectorValue.emplace(estimateVector->getId(), res);
    }

    return estimateVectorValue;
}

double MultiplicativeAggregationOperator::getBestValue() {
    if (estimateVectorValue.empty())
        return -1;

    double max = INT_MIN;
    for (const auto &item: estimateVectorValue) {
        max = item.second > max ? item.second : max;
    }
    return max;
}

int MultiplicativeAggregationOperator::getBestEstimateVectorId() {
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

bool MultiplicativeAggregationOperator::isNeedNormalizedMathModel() {
    return true;
}
