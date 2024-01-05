#ifndef DMLTESTER_CRITERIA_H
#define DMLTESTER_CRITERIA_H

#include <iostream>

enum class CriteriaType {MAXIMIZATION, MINIMIZATION};

class Criteria {
private:
    int id;
    std::string name;
    CriteriaType type;
public:
    Criteria(int id, std::string name, CriteriaType criteriaType);
    Criteria(const Criteria& other);
    ~Criteria();

    int getId();
    std::string getName();
    CriteriaType getType();
};

#endif //DMLTESTER_CRITERIA_H
