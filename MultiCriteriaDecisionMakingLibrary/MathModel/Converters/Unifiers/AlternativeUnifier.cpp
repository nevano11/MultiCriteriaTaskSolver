#include "AlternativeUnifier.h"

MathModel *AlternativeUnifier::getUnifiedMathModel(MathModel *original) {
    auto criteriaCount = original->getCriteriaCount();

    bool needToUnify = false;
    for (int criteriaIndex = 0; criteriaIndex < criteriaCount; ++criteriaIndex) {
        if (original->getCriteriaArray()[criteriaIndex]->getType() == CriteriaType::MINIMIZATION) {
            needToUnify = true;
            break;
        }
    }
    if (!needToUnify) {
        return original;
    }

    int estimateVectorCount = original->getEstimateVectorCount();
    Criteria **criteriaWithMaximization = new Criteria *[criteriaCount];
    for (int criteriaIndex = 0; criteriaIndex < criteriaCount; ++criteriaIndex) {
        criteriaWithMaximization[criteriaIndex] = new Criteria(original->getCriteriaArray()[criteriaIndex]->getId(),
                                                               original->getCriteriaArray()[criteriaIndex]->getName(),
                                                               CriteriaType::MAXIMIZATION);
        if (original->getCriteriaArray()[criteriaIndex]->getType() == CriteriaType::MINIMIZATION) {
            for (int eVIndex = 0; eVIndex < estimateVectorCount; ++eVIndex) {
                original->getEstimateVectorArray()[eVIndex]->getMarks()[criteriaIndex] *= -1;
            }
        }
    }

    EstimateVector **correctedEstimateVectors = new EstimateVector *[estimateVectorCount];
    for (int estimateVectorIndex = 0; estimateVectorIndex < estimateVectorCount; ++estimateVectorIndex) {
        correctedEstimateVectors[estimateVectorIndex] = new EstimateVector(
                *original->getEstimateVectorArray()[estimateVectorIndex]);
    }

    MathModel *unifiedMathModel = new MathModel(criteriaWithMaximization, criteriaCount, correctedEstimateVectors,
                                                estimateVectorCount);
    delete original;
    return unifiedMathModel;
}