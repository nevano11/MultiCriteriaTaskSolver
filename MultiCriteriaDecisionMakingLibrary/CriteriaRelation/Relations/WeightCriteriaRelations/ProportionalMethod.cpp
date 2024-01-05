#include <algorithm>
#include "ProportionalMethod.h"

extern "C" {
__declspec(dllexport) ProportionalMethod *ProportionalMethod_new(int criteriaCount, int* keys, double* values) {
    std::map<int, double> map;
    for (int i = 0; i < criteriaCount; ++i) {
        map.emplace(keys[i], values[i]);
    }
    return new ProportionalMethod(criteriaCount, map);
}
__declspec(dllexport) bool ProportionalMethod_isValid(ProportionalMethod* relation) {
    return relation->isValid();
}
__declspec(dllexport) CriteriaRelation *ProportionalMethod_copy(ProportionalMethod* relation) {
    return relation->copy();
}
__declspec(dllexport) int ProportionalMethod_getCriteriaCount(ProportionalMethod* relation) {
    return relation->getCriteriaCount();
}
__declspec(dllexport) int* ProportionalMethod_getCriteriaWeightMapKeys(ProportionalMethod* relation) {
    auto map = relation->getCriteriaWeightMap();
    int size = map.size();
    int* keys = new int[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.first; });
    return keys;
}
__declspec(dllexport) double* ProportionalMethod_getCriteriaWeightMapValues(ProportionalMethod* relation) {
    auto map = relation->getCriteriaWeightMap();
    int size = map.size();
    double* keys = new double[size];
    std::transform(map.begin(), map.end(), keys,
                   [](const std::pair<int, double>& p) { return p.second; });
    return keys;
}
}

ProportionalMethod::ProportionalMethod(int criteriaCount, std::map<int, double> criteriaIdWeightMap) {
    this->criteriaCount = criteriaCount;
    this->criteriaIdWeightMap = criteriaIdWeightMap;
}

bool ProportionalMethod::isValid() {
    return true;
}

std::map<int, double> ProportionalMethod::getCriteriaWeightMap() {
    if (!weightMap.empty())
        return weightMap;

    double sum = 0;
    for (auto & iterator : criteriaIdWeightMap) {
        sum += iterator.second;
    }

    for (auto & iterator : criteriaIdWeightMap) {
        weightMap.emplace(iterator.first, iterator.second / sum);
    }

    return weightMap;
}

CriteriaRelation *ProportionalMethod::copy() {
    return new ProportionalMethod(criteriaCount, criteriaIdWeightMap);
}

int ProportionalMethod::getCriteriaCount() {
    return criteriaCount;
}
