#include <algorithm>
#include "SimpleRankingMethod.h"

extern "C" {
__declspec(dllexport) SimpleRankingMethod *SimpleRankingMethod_new(int criteriaCount, int* keys, double* values) {
    std::map<int, double> map;
    for (int i = 0; i < criteriaCount; ++i) {
        map.emplace(keys[i], values[i]);
    }
    return new SimpleRankingMethod(criteriaCount, map);
}
__declspec(dllexport) bool SimpleRankingMethod_isValid(SimpleRankingMethod* relation) {
    return relation->isValid();
}
__declspec(dllexport) CriteriaRelation *SimpleRankingMethod_copy(SimpleRankingMethod* relation) {
    return relation->copy();
}
__declspec(dllexport) int SimpleRankingMethod_getCriteriaCount(SimpleRankingMethod* relation) {
    return relation->getCriteriaCount();
}
__declspec(dllexport) int* SimpleRankingMethod_getCriteriaWeightMapKeys(SimpleRankingMethod* relation) {
    auto map = relation->getCriteriaWeightMap();
    int size = map.size();
    int* keys = new int[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.first; });
    return keys;
}
__declspec(dllexport) double* SimpleRankingMethod_getCriteriaWeightMapValues(SimpleRankingMethod* relation) {
    auto map = relation->getCriteriaWeightMap();
    int size = map.size();
    double* keys = new double[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.second; });
    return keys;
}
}

SimpleRankingMethod::SimpleRankingMethod(int criteriaCount, std::map<int, double> criteriaIdRankMap) {
    this->criteriaCount = criteriaCount;
    this->criteriaIdRankMap = criteriaIdRankMap;
}

bool SimpleRankingMethod::isValid() {
    return true;
}

std::map<int, double> SimpleRankingMethod::getCriteriaWeightMap() {
    if (!weightMap.empty())
        return weightMap;

    int maxRank = criteriaIdRankMap.size() + 1;
    double sum = 0;
    for (auto & iterator : criteriaIdRankMap) {
        sum += iterator.second;
    }

    for (auto & iterator : criteriaIdRankMap) {
        weightMap.emplace(iterator.first, (maxRank - iterator.second) / sum);
    }

    return weightMap;
}

CriteriaRelation *SimpleRankingMethod::copy() {
    return new SimpleRankingMethod(criteriaCount, criteriaIdRankMap);
}

int SimpleRankingMethod::getCriteriaCount() {
    return criteriaCount;
}
