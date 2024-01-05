#include "IdealDistanceAggregationOperator.h"

#include <climits>
#include <cmath>
#include <algorithm>

extern "C" {
__declspec(dllexport) IdealDistanceAggregationOperator *IdealDistanceAggregationOperator_new() {
    return new IdealDistanceAggregationOperator();
}
__declspec(dllexport) int *IdealDistanceAggregationOperator_getEstimateVectorMark_Keys(
        IdealDistanceAggregationOperator* oper,  MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    int size = map.size();
    int* keys = new int[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.first; });
    return keys;
}
__declspec(dllexport) double* IdealDistanceAggregationOperator_getEstimateVectorMark_Values(
        IdealDistanceAggregationOperator* oper, MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    int size = map.size();
    double* values = new double[size];
    std::transform(map.begin(), map.end(), values,
                   [](const std::pair<int, double>& p) { return p.second; });
    return values;
}
__declspec(dllexport) int IdealDistanceAggregationOperator_getEstimateVectorMark_Size(
        IdealDistanceAggregationOperator* oper, MathModel* mm, WeightCriteriaRelation* relation) {
    auto map = oper->getEstimateVectorMark(mm, relation);
    return map.size();
}
__declspec(dllexport) double IdealDistanceAggregationOperator_GetBestValue(IdealDistanceAggregationOperator* oper) {
    return oper->getBestValue();
}
__declspec(dllexport) int IdealDistanceAggregationOperator_GetBestEstimateVectorId(IdealDistanceAggregationOperator* oper) {
    return oper->getBestEstimateVectorId();
}
__declspec(dllexport) bool IdealDistanceAggregationOperator_IsNeedNormalizedMathModel(IdealDistanceAggregationOperator* oper) {
    return oper->isNeedNormalizedMathModel();
}
}

std::map<int, double> IdealDistanceAggregationOperator::getEstimateVectorMark(MathModel *mathModel,
                                                                              WeightCriteriaRelation *weightCriteriaRelation) {
    auto criteriaWeightMap = weightCriteriaRelation->getCriteriaWeightMap();
    int estimateVectorCount = mathModel->getEstimateVectorCount();
    auto estimateVectorArray = mathModel->getEstimateVectorArray();

    int criteriaCount = mathModel->getCriteriaCount();

    std::map<int, double> criteriaMaxDistance;

    for (int i = 0; i < criteriaCount; ++i) {
        int criteriaId = mathModel->getCriteriaArray()[i]->getId();
        double max = INT_MIN;
        for (int j = 0; j < estimateVectorCount; ++j) {
            double temp = estimateVectorArray[j]->getMarks()[i] - mathModel->maxByCriteria(criteriaId);
            temp = temp < 0 ? temp * -1 : temp;
            if (max < temp)
                max = temp;
        }
        criteriaMaxDistance.emplace(criteriaId, max);
    }

    for (int i = 0; i < estimateVectorCount; ++i) {
        auto estimateVector = estimateVectorArray[i];
        auto marks = estimateVector->getMarks();
        double res = 0;
        for (int j = 0; j < criteriaCount; ++j) {
            int criteriaId = mathModel->getCriteriaArray()[j]->getId();
            double temp = marks[j] - mathModel->maxByCriteria(criteriaId);
            temp = temp < 0 ? temp * -1 : temp;
            temp = temp / criteriaMaxDistance[criteriaId];
            res += weightCriteriaRelation->getCriteriaWeightMap()[criteriaId] * temp * temp;
        }
        estimateVectorValue.emplace(estimateVector->getId(), pow(res, 0.5));
    }

    return estimateVectorValue;
}

double IdealDistanceAggregationOperator::getBestValue() {
    if (estimateVectorValue.empty())
        return -1;

    double min = INT_MAX;
    for (const auto &item: estimateVectorValue) {
        min = item.second < min ? item.second : min;
    }
    return min;
}

int IdealDistanceAggregationOperator::getBestEstimateVectorId() {
    if (estimateVectorValue.empty())
        return -1;

    double min = INT_MAX;
    int id = INT_MIN;
    for (const auto &item: estimateVectorValue) {
        if (item.second < min) {
            min = item.second;
            id = item.first;
        }
    }
    return id;
}

bool IdealDistanceAggregationOperator::isNeedNormalizedMathModel() {
    return false;
}
