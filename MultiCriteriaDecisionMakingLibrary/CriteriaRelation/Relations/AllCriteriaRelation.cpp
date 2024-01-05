#include "AllCriteriaRelation.h"

extern "C" {
__declspec(dllexport) AllCriteriaRelation *AllCriteriaRelation_new(int criteriaCount, int* idSequence) {
    return new AllCriteriaRelation(criteriaCount, idSequence);
}
__declspec(dllexport) void AllCriteriaRelation_delete(AllCriteriaRelation* relation) {
    delete relation;
}
__declspec(dllexport) int *AllCriteriaRelation_getIdSequence(AllCriteriaRelation* relation) {
    return relation->getIdSequence();
}
__declspec(dllexport) int AllCriteriaRelation_getSequenceSize(AllCriteriaRelation* relation) {
    return relation->getSequenceSize();
}
__declspec(dllexport) bool AllCriteriaRelation_isValid(AllCriteriaRelation* relation) {
    return relation->isValid();
}
__declspec(dllexport) CriteriaRelation *AllCriteriaRelation_copy(AllCriteriaRelation* relation) {
    return relation->copy();
}
}

AllCriteriaRelation::AllCriteriaRelation(int criteriaCount, int* idSequence)
{
    this->criteriaCount = criteriaCount;
    this->idSequence = new int[criteriaCount];
    
    for (size_t i = 0; i < criteriaCount; i++)
    {
        this->idSequence[i] = idSequence[i];
    }
}

int AllCriteriaRelation::getSequenceSize()
{
    return criteriaCount;
}

int *AllCriteriaRelation::getIdSequence()
{
    return idSequence;
}

bool AllCriteriaRelation::isValid()
{
    if (criteriaCount < 1 || idSequence == nullptr)
        return false;

    // Check is criteria id unique
    for(int i = 0; i < criteriaCount - 1; i++)
        for(int j = i + 1; j < criteriaCount; j++) 
            if(idSequence[i] == idSequence[j])
                return false;

    return true;
}

CriteriaRelation *AllCriteriaRelation::copy() {
    return new AllCriteriaRelation(criteriaCount, getIdSequence());;
}

AllCriteriaRelation::~AllCriteriaRelation() {
    delete idSequence;
}
