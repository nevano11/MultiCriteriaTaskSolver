#include "CedeValueInfo.h"

extern "C" {
__declspec(dllexport) CedeValueInfo *CedeValueInfo_new(double cedeValue) {
    return new CedeValueInfo(cedeValue);
}
__declspec(dllexport) double CedeValueInfo_getCedeValue(CedeValueInfo* makerInfo) {
    return makerInfo->getCedeValue();
}
}

CedeValueInfo::CedeValueInfo(double cedeValue) {
    this->cedeValue = cedeValue;
}

double CedeValueInfo::getCedeValue() {
    return cedeValue < 0 ? 0 : cedeValue;
}
