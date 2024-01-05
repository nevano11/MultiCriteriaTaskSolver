#include <vector>
#include <algorithm>
#include <list>
#include "CriteriaRelationConverter.h"
#include "Relations/WeightCriteriaRelations/SimpleRankingMethod.h"
#include "Relations/SimpleCriteriaRelationUtils/SimpleCriteriaRelationUtil.h"

extern "C" {
__declspec(dllexport) AllCriteriaRelation *CriteriaRelationConverter_toAll(CriteriaRelation *relation) {
    return CriteriaRelationConverter::convertToAllCriteriaRelation(relation);
}
__declspec(dllexport) SimpleCriteriaRelation *CriteriaRelationConverter_toSimple(CriteriaRelation *relation) {
    return CriteriaRelationConverter::convertToSimpleCriteriaRelation(relation);
}
__declspec(dllexport) WeightCriteriaRelation *CriteriaRelationConverter_toWeight(CriteriaRelation *relation) {
    return CriteriaRelationConverter::convertToWeightCriteriaRelation(relation);
}
}

AllCriteriaRelation *CriteriaRelationConverter::convertToAllCriteriaRelation(CriteriaRelation *relation) {
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        return convertWeightCriteriaRelationToAllCriteriaRelation(dynamic_cast<WeightCriteriaRelation*>(relation));
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        return convertSimpleCriteriaRelationToAllCriteriaRelation(dynamic_cast<SimpleCriteriaRelation*>(relation));
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        return (AllCriteriaRelation*) relation;
    }
    return nullptr;
}

SimpleCriteriaRelation *CriteriaRelationConverter::convertToSimpleCriteriaRelation(CriteriaRelation *relation) {
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        return convertWeightCriteriaRelationToSimpleCriteriaRelation((WeightCriteriaRelation*) relation);
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        return (SimpleCriteriaRelation*) relation;
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        return convertAllCriteriaRelationToSimpleCriteriaRelation((AllCriteriaRelation*) relation);
    }
    return nullptr;
}

WeightCriteriaRelation *CriteriaRelationConverter::convertToWeightCriteriaRelation(CriteriaRelation *relation) {
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        return (WeightCriteriaRelation*) relation;
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        return convertSimpleCriteriaRelationToWeightCriteriaRelation((SimpleCriteriaRelation*) relation);
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        return convertAllCriteriaRelationToWeightCriteriaRelation((AllCriteriaRelation*) relation);
    }
    return nullptr;
}

CriteriaRelationConverter::CriteriaRelationConverter() {

}

AllCriteriaRelation* CriteriaRelationConverter::convertWeightCriteriaRelationToAllCriteriaRelation(WeightCriteriaRelation *relation) {
    if (relation == nullptr)
        return nullptr;

    auto criteriaWeightMap = relation->getCriteriaWeightMap();
    std::vector<std::pair<int, double>> v(begin(criteriaWeightMap), end(criteriaWeightMap));
    bool hasEqualItems = false;

    std::sort(begin(v), end(v), [&hasEqualItems](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        if (a.second == b.second)
            hasEqualItems = true;
        return a.second > b.second;
    });

    if (hasEqualItems)
        return nullptr;

    int* idSequence = new int[v.size()];
    int i = 0;
    for (const auto &item: v) {
        idSequence[i++] = item.first;
    }
    delete relation;
    return new AllCriteriaRelation(v.size(), idSequence);
}

WeightCriteriaRelation* CriteriaRelationConverter::convertAllCriteriaRelationToWeightCriteriaRelation(AllCriteriaRelation *relation) {
    if (relation == nullptr)
        return nullptr;

    std::map<int, double> criteriaIdRankMap;

    int criteriaCount = relation->getSequenceSize();
    int* idSequence = relation->getIdSequence();
    for (int i = 0; i < criteriaCount; ++i) {
        criteriaIdRankMap.emplace(idSequence[i], i + 1);
    }
    delete relation;
    return new SimpleRankingMethod(relation->getSequenceSize(), criteriaIdRankMap);
}

SimpleCriteriaRelation *
CriteriaRelationConverter::convertAllCriteriaRelationToSimpleCriteriaRelation(AllCriteriaRelation *relation) {
    int* idSequence = relation->getIdSequence();
    int count = relation->getSequenceSize();

    TwoCriteriaRelation** twoCriteriaRelationArray = new TwoCriteriaRelation* [count - 1];

    for (int i = 0; i < count - 1; ++i)
        twoCriteriaRelationArray[i] = new TwoCriteriaRelation(idSequence[i], CriteriaConstraint::More, idSequence[i+1]);

    delete relation;
    return new SimpleCriteriaRelation(twoCriteriaRelationArray, count, count - 1);
}

SimpleCriteriaRelation *
CriteriaRelationConverter::convertWeightCriteriaRelationToSimpleCriteriaRelation(WeightCriteriaRelation *relation) {
    auto map = relation->getCriteriaWeightMap();
    int criteriaCount = map.size();
    int* idSequence = new int[criteriaCount];

    int i = 0;
    for (const auto &item: map) {
        idSequence[i++] = item.first;
    }

    std::list<TwoCriteriaRelation*> relations;

    for (int j = 0; j < criteriaCount - 1; ++j) {
        for (int k = j + 1; k < criteriaCount; ++k) {
            double firstWeight = map[idSequence[j]];
            double secondWeight = map[idSequence[k]];
            if (firstWeight > secondWeight)
                relations.emplace_back(new TwoCriteriaRelation(idSequence[j], CriteriaConstraint::More, idSequence[k]));
            else if (firstWeight < secondWeight)
                relations.emplace_back(new TwoCriteriaRelation(idSequence[j], CriteriaConstraint::Less, idSequence[k]));
            else
                relations.emplace_back(new TwoCriteriaRelation(idSequence[j], CriteriaConstraint::Equivalent, idSequence[k]));
        }
    }

    TwoCriteriaRelation** relationArray = new TwoCriteriaRelation* [relations.size()];
    std::copy(relations.begin(), relations.end(), relationArray);
    delete relation;
    return new SimpleCriteriaRelation(relationArray, criteriaCount, relations.size());
}

AllCriteriaRelation *
CriteriaRelationConverter::convertSimpleCriteriaRelationToAllCriteriaRelation(SimpleCriteriaRelation *relation) {
    SimpleCriteriaRelationUtil* util = new SimpleCriteriaRelationUtil(relation);
    auto aCR = util->toAllCriteriaRelation();
    delete relation;
    delete util;
    return aCR;
}

WeightCriteriaRelation *
CriteriaRelationConverter::convertSimpleCriteriaRelationToWeightCriteriaRelation(SimpleCriteriaRelation *relation) {
    SimpleCriteriaRelationUtil* util = new SimpleCriteriaRelationUtil(relation);
    auto wCR = util->toWeightCriteriaRelation();
    delete relation;
    delete util;
    return wCR;
}
