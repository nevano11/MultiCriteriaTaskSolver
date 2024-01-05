#include <cmath>
#include "MathModel.h"

extern "C" {
__declspec(dllexport) MathModel *MathModel_new(Criteria **criteriaArray, int criteriaCount, EstimateVector **estimateVectorArray, int estimateVectorCount) {
        return new MathModel(criteriaArray, criteriaCount, estimateVectorArray, estimateVectorCount);
    }
__declspec(dllexport) MathModel *MathModel_new_copy(const MathModel& other) {
        return new MathModel(other);
    }
__declspec(dllexport) Criteria** MathModel_getCriteriaArray(MathModel *obj) {
        return obj->getCriteriaArray();
    }
__declspec(dllexport) EstimateVector** MathModel_getEstimateVectorArray(MathModel *obj) {
        return obj->getEstimateVectorArray();
    }
__declspec(dllexport) int MathModel_getCriteriaCount(MathModel *obj) {
        return obj->getCriteriaCount();
    }
__declspec(dllexport) int MathModel_getEstimateVectorCount(MathModel *obj) {
        return obj->getEstimateVectorCount();
    }
__declspec(dllexport) Criteria* MathModel_getCriteriaById(MathModel *obj, int id) {
        return obj->getCriteriaById(id);
    }
__declspec(dllexport) Criteria* MathModel_getCriteriaByName(MathModel *obj, const char* name) {
        return obj->getCriteriaByName(name);
    }
__declspec(dllexport) int MathModel_findCriteriaNumById(MathModel *obj, int criteriaId) {
        return obj->findCriteriaNumById(criteriaId);
    }
__declspec(dllexport) int MathModel_findCriteriaNumByName(MathModel *obj, const char* name) {
        return obj->findCriteriaNumByName(name);
    }
__declspec(dllexport) double MathModel_sumByCriteria(MathModel *obj, int criteriaId) {
        return obj->sumByCriteria(criteriaId);
    }
__declspec(dllexport) double MathModel_maxByCriteria(MathModel *obj, int criteriaId) {
        return obj->maxByCriteria(criteriaId);
    }
__declspec(dllexport) double MathModel_minByCriteria(MathModel *obj, int criteriaId) {
        return obj->minByCriteria(criteriaId);
    }
__declspec(dllexport) void deleteEstimateVectorByPredicate(MathModel *obj, int criteriaNum, bool (*deletePredicate)(double, std::vector<double>)
                                         , std::vector<double> secondAttributes) {
        obj->deleteEstimateVectorByPredicate(criteriaNum, deletePredicate, secondAttributes);
    }
__declspec(dllexport) double MathModel_isValid(MathModel *obj) {
        return obj->isValid();
    }
__declspec(dllexport) double MathModel_isNormalized(MathModel *obj) {
        return obj->isNormalized();
    }
__declspec(dllexport) const char* MathModel_estimateVectorArrayToString(MathModel *obj) {
        return obj->estimateVectorArrayToString().c_str();
    }
}

MathModel::MathModel(Criteria **criteriaArray, int criteriaCount, EstimateVector **estimateVectorArray,
                     int estimateVectorCount) {
    this->criteriaArray = criteriaArray;
    this->criteriaCount = criteriaCount;
    this->estimateVectorArray = estimateVectorArray;
    this->estimateVectorCount = estimateVectorCount;
}

MathModel::MathModel(const MathModel &other)
{
    criteriaCount = other.criteriaCount;
    criteriaArray = new Criteria*[criteriaCount];
    for (int i = 0; i < criteriaCount; i++) {
        criteriaArray[i] = new Criteria(*other.criteriaArray[i]);
    }

    estimateVectorCount = other.estimateVectorCount;
    estimateVectorArray = new EstimateVector*[estimateVectorCount];
    for (int i = 0; i < estimateVectorCount; i++) {
        estimateVectorArray[i] = new EstimateVector(*other.estimateVectorArray[i]);
    }
}

MathModel::~MathModel()
{
    for (int i = 0; i < criteriaCount; i++) {
        if (criteriaArray != nullptr && criteriaArray[i] != nullptr)
            delete criteriaArray[i];
    }

    if (criteriaArray != nullptr)
        delete[] criteriaArray;

    for (int i = 0; i < estimateVectorCount; i++) {
        if (estimateVectorArray != nullptr && estimateVectorArray[i] != nullptr)
            delete estimateVectorArray[i];
    }
    if (estimateVectorArray != nullptr)
        delete[] estimateVectorArray;
}

Criteria **MathModel::getCriteriaArray() {
    return criteriaArray;
}

EstimateVector **MathModel::getEstimateVectorArray() {
    return estimateVectorArray;
}

int MathModel::getCriteriaCount() {
    return criteriaCount;
}

int MathModel::getEstimateVectorCount() {
    return estimateVectorCount;
}

Criteria *MathModel::getCriteriaById(int id)
{
    return criteriaArray[findCriteriaNumById(id)];
}

Criteria *MathModel::getCriteriaByName(std::string name)
{
    return criteriaArray[findCriteriaNumByName(name)];
}

double MathModel::sumByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double sum = 0;
    for (int i = 0; i < estimateVectorCount; ++i) {
        sum += estimateVectorArray[i]->getMarks()[criteriaNum];
    }
    return sum;
}

double MathModel::minByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double min = estimateVectorArray[0]->getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        int mark = estimateVectorArray[i]->getMarks()[criteriaNum];
        if (min > mark)
            min = mark;
    }
    return min;
}

double MathModel::maxByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double max = estimateVectorArray[0]->getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        int mark = estimateVectorArray[i]->getMarks()[criteriaNum];
        if (max < mark)
            max = mark;
    }
    return max;
}

int MathModel::findCriteriaNumById(int criteriaId) {
    for (int i = 0; i < criteriaCount; ++i)
        if (criteriaArray[i]->getId() == criteriaId)
            return i;
    return -1;
}

int MathModel::findCriteriaNumByName(std::string criteriaName) {
    for (int i = 0; i < criteriaCount; ++i)
        if (criteriaArray[i]->getName() == criteriaName)
            return i;
    return -1;
}

void MathModel::deleteEstimateVectorByPredicate(int criteriaNum, bool(*deletePredicate)(double, std::vector<double>), std::vector<double> secondAttributes)
{
    int deleteCount = 0;
    for (int i = 0; i < estimateVectorCount; i++)
        if (deletePredicate(estimateVectorArray[i]->getMarks()[criteriaNum], secondAttributes))
            deleteCount++;

    estimateVectorCount = estimateVectorCount - deleteCount;
    EstimateVector** tmpArray = new EstimateVector*[estimateVectorCount];

    int j = 0;
    for (size_t i = 0; i < estimateVectorCount + deleteCount; i++) {
        if (!deletePredicate(estimateVectorArray[i]->getMarks()[criteriaNum], secondAttributes))
            tmpArray[j++] = new EstimateVector(*estimateVectorArray[i]);
        delete estimateVectorArray[i];
    }
    delete[] estimateVectorArray;
    estimateVectorArray = tmpArray;
}

bool MathModel::isValid()
{
    if (criteriaCount < 1 || estimateVectorCount < 1 || criteriaArray == nullptr || estimateVectorArray == nullptr)
        return false;

    for (size_t i = 0; i < criteriaCount; i++)
        if (criteriaArray[i] == nullptr)
            return false;
    
    for (size_t i = 0; i < estimateVectorCount; i++)
        if (estimateVectorArray[i] == nullptr || estimateVectorArray[i]->getCriteriaCount() != criteriaCount)
            return false;

    return true;
}

std::string MathModel::estimateVectorArrayToString() {
    std::string res = "";
    for (int i = 0; i < estimateVectorCount; ++i) {
        res += estimateVectorArray[i]->toString();
        res += "\n";
    }
    return res;
}

bool MathModel::isNormalized() {
    for (int i = 0; i < estimateVectorCount; ++i)
        for (int j = 0; j < criteriaCount; ++j)
            if (estimateVectorArray[i]->getMarks()[j] > 1 || estimateVectorArray[i]->getMarks()[j] < 0)
                return false;
    return true;
}
