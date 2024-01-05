#ifndef DMLTESTER_MULTISTEPMETHOD_H
#define DMLTESTER_MULTISTEPMETHOD_H

#include "../MultiCriteriaMethod.h"
#include "../../DecisionMakerInfo/DecisionMakerInfo.h"
#include "../../IntermediateMethodData/IntermediateMethodData.h"

class MultiStepMethod : public MultiCriteriaMethod {
public:
    virtual SolveStatus* makeIteration(DecisionMakerInfo* decisionMakingInfo) = 0;
    virtual IntermediateMethodData* getIntermediateMethodData() = 0;
};


#endif //DMLTESTER_MULTISTEPMETHOD_H
