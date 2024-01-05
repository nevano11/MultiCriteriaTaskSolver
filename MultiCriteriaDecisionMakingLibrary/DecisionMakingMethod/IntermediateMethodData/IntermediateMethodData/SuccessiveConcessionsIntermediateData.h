#ifndef DMLTESTER_SUCCESSIVECONCESSIONSINTERMEDIATEDATA_H
#define DMLTESTER_SUCCESSIVECONCESSIONSINTERMEDIATEDATA_H


#include "../../../MathModel/Components/Criteria.h"
#include "../IntermediateMethodData.h"

class SuccessiveConcessionsIntermediateData : public IntermediateMethodData {
private:
    Criteria* criteria;
public:
    SuccessiveConcessionsIntermediateData(Criteria* criteriaThatNeedCedeValue);
    Criteria* getCriteriaThatNeedCedeValue();
    std::string toString();
};


#endif //DMLTESTER_SUCCESSIVECONCESSIONSINTERMEDIATEDATA_H
