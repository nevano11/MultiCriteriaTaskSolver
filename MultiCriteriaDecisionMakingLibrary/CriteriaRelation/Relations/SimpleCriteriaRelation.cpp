#include "SimpleCriteriaRelation.h"
#include <set>

extern "C" {
__declspec(dllexport) SimpleCriteriaRelation *SimpleCriteriaRelation_new(TwoCriteriaRelation** relations, int criteriaCount, int relationCount) {
    return new SimpleCriteriaRelation(relations, criteriaCount, relationCount);
}
__declspec(dllexport) void SimpleCriteriaRelation_delete(SimpleCriteriaRelation* relation) {
    delete relation;
}
__declspec(dllexport) TwoCriteriaRelation** SimpleCriteriaRelation_getTwoCriteriaRelationArray(SimpleCriteriaRelation* relation) {
    return relation->getTwoCriteriaRelationArray();
}
__declspec(dllexport) int SimpleCriteriaRelation_getCriteriaCount(SimpleCriteriaRelation* relation) {
    return relation->getCriteriaCount();
}
__declspec(dllexport) int SimpleCriteriaRelation_getRelationCount(SimpleCriteriaRelation* relation) {
    return relation->getRelationCount();
}
__declspec(dllexport) bool SimpleCriteriaRelation_isValid(SimpleCriteriaRelation* relation) {
    return relation->isValid();
}
__declspec(dllexport) CriteriaRelation *SimpleCriteriaRelation_copy(SimpleCriteriaRelation* relation) {
    return relation->copy();
}
}

SimpleCriteriaRelation::SimpleCriteriaRelation(TwoCriteriaRelation **twoCriteriaRelationArray,
                                               int criteriaCount, int relationCount) {
    this->criteriaCount = criteriaCount;
    this->relationCount = relationCount;
    this->twoCriteriaRelationArray = twoCriteriaRelationArray;
}

bool SimpleCriteriaRelation::isValid() {
    if (criteriaCount < 1 || relationCount < 1 || twoCriteriaRelationArray == nullptr)
        return false;

    std::set<int> idOnRelationSet;

    for (int i = 0; i < relationCount; ++i) {
        if (twoCriteriaRelationArray[i] == nullptr || !twoCriteriaRelationArray[i]->isValid())
            return false;
        else {
            idOnRelationSet.insert(twoCriteriaRelationArray[i]->getFirstCriteriaId());
            idOnRelationSet.insert(twoCriteriaRelationArray[i]->getSecondCriteriaId());
        }
    }

    if (idOnRelationSet.size() != 0)
        return false;

    // Непротиворечивость
    for (int i = 0; i < relationCount - 1; i++)
        for (int j = 0; j < relationCount - i - 1; j++)
            if (!twoCriteriaRelationArray[i]->isRespond(twoCriteriaRelationArray[j]))
                return false;

    return true;
}

TwoCriteriaRelation **SimpleCriteriaRelation::getTwoCriteriaRelationArray() {
    return twoCriteriaRelationArray;
}

int SimpleCriteriaRelation::getRelationCount() {
    return relationCount;
}

SimpleCriteriaRelation::SimpleCriteriaRelation() {

}

// TODO
CriteriaRelation *SimpleCriteriaRelation::copy() {
    return this;
}

int SimpleCriteriaRelation::getCriteriaCount() {
    return criteriaCount;
}