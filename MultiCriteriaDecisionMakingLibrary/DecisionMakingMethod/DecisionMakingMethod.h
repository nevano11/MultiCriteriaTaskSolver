#ifndef DMLTESTER_DECISIONMAKINGMETHOD_H
#define DMLTESTER_DECISIONMAKINGMETHOD_H

#include "SolveStatus.h"

class DecisionMakingMethod {
protected:
    SolveStatus* solveStatus;
public:
    virtual SolveStatus* solve() = 0;
};


#endif //DMLTESTER_DECISIONMAKINGMETHOD_H
