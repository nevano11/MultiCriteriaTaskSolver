#include "EstimateVector.h"
#include <string>
#include <cstring>

extern "C" {
__declspec(dllexport) EstimateVector *EstimateVector_new(int id, const char* name, int nameLength, double *markArray, int criteriaCount) {
    std::string realName = std::string(name, nameLength);
    return new EstimateVector(id, realName, markArray, criteriaCount);
}
__declspec(dllexport) EstimateVector *EstimateVector_new_copy(const EstimateVector &other) {
    return new EstimateVector(other);
}
__declspec(dllexport) void EstimateVector_delete(EstimateVector *obj) {
    delete obj;
}
__declspec(dllexport) int EstimateVector_getId(EstimateVector *obj) {
    return obj->getId();
}
__declspec(dllexport) const char* EstimateVector_getName(EstimateVector *obj) {
    try {
        std::string str = obj->getName();
        char* buffer = new char[str.length() + 1];
        std::strcpy(buffer, str.c_str());
        return buffer;
    }
    catch (const std::exception& e) {
        std::cerr << "Error in EstimateVector_getName: " << e.what() << std::endl;
        return nullptr;
    }
}
__declspec(dllexport) double *EstimateVector_getMarks(EstimateVector *obj) {
    return obj->getMarks();
}
__declspec(dllexport) int EstimateVector_getCriteriaCount(EstimateVector *obj) {
    return obj->getCriteriaCount();
}
__declspec(dllexport) const char* EstimateVector_toString(EstimateVector *obj) {
    try {
        std::string str = obj->toString();
        char* buffer = new char[str.length() + 1];
        std::strcpy(buffer, str.c_str());
        return buffer;
    }
    catch (const std::exception& e) {
        std::cerr << "Error in EstimateVector_getName: " << e.what() << std::endl;
        return nullptr;
    }
}
}


EstimateVector::EstimateVector(int id, std::string name, double *markArray, int criteriaCount) {
    this->id = id;
    this->name = name;
    marks = new double[criteriaCount];
    for (int i = 0; i < criteriaCount; i++) {
        marks[i] = markArray[i];
    }
    this->criteriaCount = criteriaCount;
}

EstimateVector::EstimateVector(const EstimateVector &other) {
    this->id = other.id;
    this->name = other.name;
    this->criteriaCount = other.criteriaCount;
    marks = new double[criteriaCount];
    for (int i = 0; i < criteriaCount; i++) {
        marks[i] = other.marks[i];
    }
}

EstimateVector::~EstimateVector()
{
    delete[] marks;
}

int EstimateVector::getId() {
    return id;
}

std::string EstimateVector::getName() {
    return name;
}

double *EstimateVector::getMarks() {
    return marks;
}

int EstimateVector::getCriteriaCount() {
    return this->criteriaCount;
}

std::string EstimateVector::toString() {
    std::string res = "EstimateVector[";
    res += "id=" + std::to_string(this->id);
    res += ", name=" + name;

    res += ", marks=[";
    for (int i = 0; i < criteriaCount; ++i) {
        res += std::to_string(marks[i]);
        if (i != criteriaCount - 1)
            res += ", ";
    }
    res += "]]";
    return res;
}
