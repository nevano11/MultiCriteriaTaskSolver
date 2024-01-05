#include "TwoCriteriaRelation.h"

extern "C" {
__declspec(dllexport) TwoCriteriaRelation *TwoCriteriaRelation_new(int firstId, int constraint, int secondId) {
    return new TwoCriteriaRelation(firstId, static_cast<CriteriaConstraint>(constraint), secondId);
}
__declspec(dllexport) TwoCriteriaRelation * TwoCriteriaRelation_new_copy(TwoCriteriaRelation* relation) {
    return new TwoCriteriaRelation(*relation);
}
__declspec(dllexport) int TwoCriteriaRelation_getFirstCriteriaId(TwoCriteriaRelation* relation) {
    return relation->getFirstCriteriaId();
}
__declspec(dllexport) int TwoCriteriaRelation_getSecondCriteriaId(TwoCriteriaRelation* relation) {
    return relation->getSecondCriteriaId();
}
__declspec(dllexport) int TwoCriteriaRelation_getConstraint(TwoCriteriaRelation* relation) {
    return static_cast<int>(relation->getConstraint());
}
__declspec(dllexport) bool TwoCriteriaRelation_isValid(TwoCriteriaRelation* relation) {
    return relation->isValid();
}
__declspec(dllexport) bool TwoCriteriaRelation_isEqual(TwoCriteriaRelation* relation, TwoCriteriaRelation* otherRelationPtr) {
    return relation->isEqual(otherRelationPtr);
}
__declspec(dllexport) TwoCriteriaRelation* TwoCriteriaRelation_invert(TwoCriteriaRelation* relation) {
    return relation->invert();
}
__declspec(dllexport) int TwoCriteriaRelation_getInvertConstraint(TwoCriteriaRelation* relation, int constraint) {
    return static_cast<int>(relation->getInvertConstraint(static_cast<CriteriaConstraint>(constraint)));
}
}

TwoCriteriaRelation::TwoCriteriaRelation(int firstCriteriaId, CriteriaConstraint constraint, int secondCriteriaId) :
        firstId(firstCriteriaId), secondId(secondCriteriaId), constraint(constraint) {
}

TwoCriteriaRelation::TwoCriteriaRelation(const TwoCriteriaRelation& other) {
    firstId = other.firstId;
    secondId = other.secondId;
    constraint = other.constraint;
}

int TwoCriteriaRelation::getFirstCriteriaId() {
    return firstId;
}

int TwoCriteriaRelation::getSecondCriteriaId() {
    return secondId;
}

CriteriaConstraint TwoCriteriaRelation::getConstraint() {
    return constraint;
}

bool TwoCriteriaRelation::isValid() {
    if (constraint == CriteriaConstraint::More || constraint == CriteriaConstraint::Less)
        return firstId != secondId;
    return true;
}

TwoCriteriaRelation *TwoCriteriaRelation::invert() {
    return new TwoCriteriaRelation(secondId, getInvertConstraint(constraint), firstId);
}

bool TwoCriteriaRelation::isRespond(TwoCriteriaRelation *secondRelation) {
    if (firstId == secondRelation->getFirstCriteriaId() && secondId == secondRelation->getSecondCriteriaId())
        return constraint == secondRelation->constraint;
    if (secondId == secondRelation->getFirstCriteriaId() && firstId == secondRelation->getSecondCriteriaId())
        return constraint == getInvertConstraint(secondRelation->constraint);
    return true;
}

CriteriaConstraint TwoCriteriaRelation::getInvertConstraint(CriteriaConstraint constraint) {
    switch (constraint) {
        case CriteriaConstraint::More:
            return CriteriaConstraint::Less;
        case CriteriaConstraint::Less:
            return CriteriaConstraint::More;
        case CriteriaConstraint::MoreOrEquivalent:
            return CriteriaConstraint::LessOrEquivalent;
        case CriteriaConstraint::LessOrEquivalent:
            return CriteriaConstraint::MoreOrEquivalent;
        default:
            return CriteriaConstraint::Equivalent;
    }
}

bool TwoCriteriaRelation::isEqual(TwoCriteriaRelation* relation) {
    if (this->constraint == relation->constraint)
        if (this->constraint == CriteriaConstraint::Equivalent)
            return (this->firstId == relation->firstId && this->secondId == relation->secondId) ||
                    (this->firstId == relation->secondId && this->secondId == relation->firstId);
        return this->firstId == relation->firstId && this->secondId == relation->secondId;
}
