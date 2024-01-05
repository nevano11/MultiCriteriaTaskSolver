#ifndef DMLTESTER_MATHMODEL_H
#define DMLTESTER_MATHMODEL_H

#include <vector>
#include "Components/Criteria.h"
#include "Components/EstimateVector.h"

class MathModel {
private:
    Criteria** criteriaArray;
    int criteriaCount;
    EstimateVector** estimateVectorArray;
    int estimateVectorCount;
public:
    MathModel(Criteria **criteriaArray, int criteriaCount, EstimateVector **estimateVectorArray, int estimateVectorCount);
    MathModel(const MathModel& other);
    ~MathModel();
    
    Criteria** getCriteriaArray();
    EstimateVector** getEstimateVectorArray();
    int getCriteriaCount();
    int getEstimateVectorCount();

    Criteria* getCriteriaById(int id);
    Criteria* getCriteriaByName(std::string name);

    int findCriteriaNumById(int criteriaId);
    int findCriteriaNumByName(std::string criteriaName);

    double sumByCriteria(int criteriaId);
    double maxByCriteria(int criteriaId);
    double minByCriteria(int criteriaId);

    void deleteEstimateVectorByPredicate(int criteriaNum,
                                         bool (*deletePredicate)(double, std::vector<double>),
                                         std::vector<double> secondAttributes);

    bool isValid();
    bool isNormalized();

    std::string estimateVectorArrayToString();
};

#endif //DMLTESTER_MATHMODEL_H