#include "ElectreMethod.h"
#include "../../MathModel/Converters/Unifiers/AlternativeUnifier.h"

ElectreMethod::ElectreMethod() {
    this->solveStatus = new SolveStatus(None);
    this->mathModel = nullptr;
    this->relation = nullptr;
}

ElectreMethod::ElectreMethod(MathModel *mathModel, CriteriaRelation *relation) {
    auto unifier = new AlternativeUnifier();
    this->mathModel = unifier->getUnifiedMathModel(mathModel);

    std::cout << this->mathModel->estimateVectorArrayToString() << std::endl;

    delete unifier;

    this->relation = relation->copy();
    this->solveStatus = new SolveStatus(None);

    int estimateVectorCount = this->mathModel->getEstimateVectorCount();
    int criteriaCount = this->mathModel->getCriteriaCount();

    // for agreement matrix need WeightRelation
    auto weightCriteriaRelation = CriteriaRelationConverter::convertToWeightCriteriaRelation(this->relation);
    for (const auto &item: weightCriteriaRelation->getCriteriaWeightMap()) {
        std::cout << item.first << " " << item.second << std::endl;
    }

    // build matrix of agreement
    this->agreementMatrix = new double *[estimateVectorCount];
    for (int i = 0; i < estimateVectorCount; ++i) {
        this->agreementMatrix[i] = new double[estimateVectorCount];
    }
    // filling matrix of agreement
    for (int mainAlternativeIndex = 0; mainAlternativeIndex < estimateVectorCount; ++mainAlternativeIndex) {
        auto mainMarkArray = this->mathModel->getEstimateVectorArray()[mainAlternativeIndex]->getMarks();

        for (int alternativeIndex = 0; alternativeIndex < estimateVectorCount; ++alternativeIndex) {
            if (mainAlternativeIndex == alternativeIndex) {
                this->agreementMatrix[mainAlternativeIndex][alternativeIndex] = 0;
                continue;
            }
            double agreement = 0;
            auto secondMarkArray = this->mathModel->getEstimateVectorArray()[alternativeIndex]->getMarks();
            for (int criteriaIndex = 0; criteriaIndex < criteriaCount; ++criteriaIndex) {
                auto mMark = mainMarkArray[criteriaIndex];
                auto sMark = secondMarkArray[criteriaIndex];
                if (mMark >= sMark) {
                    agreement += weightCriteriaRelation->getCriteriaWeightMap()[this->mathModel->getCriteriaArray()[criteriaIndex]->getId()];
                }
            }
            this->agreementMatrix[mainAlternativeIndex][alternativeIndex] = agreement;
        }
    }
    // printing
    for (int mainAlternativeIndex = 0; mainAlternativeIndex < estimateVectorCount; ++mainAlternativeIndex) {
        for (int sAlternativeIndex = 0; sAlternativeIndex < estimateVectorCount; ++sAlternativeIndex) {
            std::cout << this->agreementMatrix[mainAlternativeIndex][sAlternativeIndex] << " ";
        }
        std::cout << std::endl;
    }

    // build matrix of disagreement
    this->disagreementMatrix = new double *[estimateVectorCount];
    for (int i = 0; i < estimateVectorCount; ++i) {
        this->disagreementMatrix[i] = new double[estimateVectorCount];
    }
    // find max - min by criteria
    auto maxminDelta = new double[criteriaCount];
    for (int criteriaIndex = 0; criteriaIndex < criteriaCount; ++criteriaIndex) {
        double max = INT_MIN;
        double min = INT_MAX;
        for (int alternativeIndex = 0; alternativeIndex < estimateVectorCount; ++alternativeIndex) {
            auto mark = this->mathModel->getEstimateVectorArray()[alternativeIndex]->getMarks()[criteriaIndex];
            if (mark > max)
                max = mark;
            if (mark < min)
                min = mark;
        }
        maxminDelta[criteriaIndex] = max - min;
    }
    // filling matrix of agreement
    for (int mainAlternativeIndex = 0; mainAlternativeIndex < estimateVectorCount; ++mainAlternativeIndex) {
        auto mainMarkArray = this->mathModel->getEstimateVectorArray()[mainAlternativeIndex]->getMarks();

        for (int alternativeIndex = 0; alternativeIndex < estimateVectorCount; ++alternativeIndex) {
            if (mainAlternativeIndex == alternativeIndex) {
                this->disagreementMatrix[mainAlternativeIndex][alternativeIndex] = 0;
                continue;
            }
            double max = -1;
            auto secondMarkArray = this->mathModel->getEstimateVectorArray()[alternativeIndex]->getMarks();
            for (int criteriaIndex = 0; criteriaIndex < criteriaCount; ++criteriaIndex) {
                auto mMark = mainMarkArray[criteriaIndex];
                auto sMark = secondMarkArray[criteriaIndex];
                auto calc = (sMark-mMark) / maxminDelta[criteriaIndex];

                // always more than 0
                if (calc > max)
                    max = calc;
            }
            this->disagreementMatrix[mainAlternativeIndex][alternativeIndex] = max;
        }
    }
    // printing
    for (int mainAlternativeIndex = 0; mainAlternativeIndex < estimateVectorCount; ++mainAlternativeIndex) {
        for (int sAlternativeIndex = 0; sAlternativeIndex < estimateVectorCount; ++sAlternativeIndex) {
            std::cout << this->disagreementMatrix[mainAlternativeIndex][sAlternativeIndex] << " ";
        }
        std::cout << std::endl;
    }
}

ElectreMethod::~ElectreMethod() {
    int criteriaCount = 0;
    if (mathModel != nullptr) {
        criteriaCount = mathModel->getCriteriaCount();
        delete mathModel;
    }
    if (solveStatus != nullptr)
        delete solveStatus;
    if (relation != nullptr)
        delete relation;

    if (agreementMatrix != nullptr) {
        if (agreementMatrix[0] != nullptr) {
            for (int i = 0; i < criteriaCount; ++i) {
                delete[] agreementMatrix[i];
            }
            delete[] agreementMatrix;
        }
    }

    if (disagreementMatrix != nullptr) {
        if (disagreementMatrix[0] != nullptr) {
            for (int i = 0; i < criteriaCount; ++i) {
                delete[] disagreementMatrix[i];
            }
            delete[] disagreementMatrix;
        }
    }
}

SolveStatus *ElectreMethod::makeIteration(DecisionMakerInfo *decisionMakingInfo) {
    return nullptr;
}

IntermediateMethodData *ElectreMethod::getIntermediateMethodData() {
    return nullptr;
}

SolveStatus *ElectreMethod::solve() {
    return solveStatus;
}

void ElectreMethod::setMathModel(MathModel *mathModel) {
    if (this->mathModel != nullptr)
        delete this->mathModel;
    this->mathModel = new MathModel(*mathModel);
}

void ElectreMethod::setCriteriaRelation(CriteriaRelation *relation) {
    this->relation = relation->copy();
}

MathModel *ElectreMethod::getMathModel() {
    return this->mathModel;
}

int ElectreMethod::getBestEstimateVectorId() {
    return mathModel->getEstimateVectorCount() == 1 ? mathModel->getEstimateVectorArray()[0]->getId() : INT_MIN;
}
