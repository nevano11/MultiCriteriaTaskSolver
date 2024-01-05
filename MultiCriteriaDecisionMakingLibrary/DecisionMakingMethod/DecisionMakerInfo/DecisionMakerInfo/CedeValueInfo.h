#ifndef DMLTESTER_CEDEVALUEINFO_H
#define DMLTESTER_CEDEVALUEINFO_H


#include "../DecisionMakerInfo.h"

class CedeValueInfo : public DecisionMakerInfo{
private:
    double cedeValue;
public:
    CedeValueInfo(double cedeValue);
    double getCedeValue();
};


#endif //DMLTESTER_CEDEVALUEINFO_H
