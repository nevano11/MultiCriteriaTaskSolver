#include "SuccessiveConcessionsIntermediateData.h"
#include <string>

extern "C" {
__declspec(dllexport) SuccessiveConcessionsIntermediateData *SuccessiveConcessionsIntermediateData_new(Criteria* criteria) {
    return new SuccessiveConcessionsIntermediateData(criteria);
}
__declspec(dllexport) Criteria* SuccessiveConcessionsIntermediateData_getCriteria(SuccessiveConcessionsIntermediateData* methodData) {
    return methodData->getCriteriaThatNeedCedeValue();
}
}

SuccessiveConcessionsIntermediateData::SuccessiveConcessionsIntermediateData(Criteria *criteriaThatNeedCedeValue) {
    criteria = criteriaThatNeedCedeValue;
}

Criteria *SuccessiveConcessionsIntermediateData::getCriteriaThatNeedCedeValue() {
    return criteria;
}

std::string SuccessiveConcessionsIntermediateData::toString() {
    return "Criteria with id=" + std::to_string(criteria->getId());
}
