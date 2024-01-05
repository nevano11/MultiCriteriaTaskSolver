#ifndef DMLTESTER_MULTICRITERIAMETHOD_H
#define DMLTESTER_MULTICRITERIAMETHOD_H

#include "../DecisionMakingMethod.h"
#include "../../MathModel/MathModel.h"
#include "../../CriteriaRelation/CriteriaRelation.h"
#include "../../CriteriaRelation/CriteriaRelationConverter.h"

class MultiCriteriaMethod : public DecisionMakingMethod {
protected:
    MathModel* mathModel;
    CriteriaRelation* relation;
public:
    virtual MathModel* getMathModel() = 0;
    virtual void setMathModel(MathModel* mathModel) = 0;
    virtual void setCriteriaRelation(CriteriaRelation* relation) = 0;
    virtual int getBestEstimateVectorId() = 0;
};

#endif //DMLTESTER_MULTICRITERIAMETHOD_H
