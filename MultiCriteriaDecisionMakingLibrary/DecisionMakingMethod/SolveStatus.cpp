#include "SolveStatus.h"
#include <cstring>

extern "C" {
__declspec(dllexport) SolveStatus *SolveStatus_new_0() {
    return new SolveStatus();
}
__declspec(dllexport) SolveStatus *SolveStatus_new_1(int decisionStatus) {
    return new SolveStatus(static_cast<DecisionStatus>(decisionStatus));
}
__declspec(dllexport) SolveStatus *SolveStatus_new_2(int decisionStatus, char* message, int messageLength) {
    return new SolveStatus(static_cast<DecisionStatus>(decisionStatus), std::string(message, messageLength));
}
__declspec(dllexport) int SolveStatus_getDecisionStatus(SolveStatus* solveStatus) {
    return static_cast<int>(solveStatus->getStatus());
}
__declspec(dllexport) char* SolveStatus_getMessage(SolveStatus* solveStatus) {
    std::string str = solveStatus->getMessage();
    char* buffer = new char[str.length() + 1];
    std::strcpy(buffer, str.c_str());
    return buffer;
}
}

SolveStatus::SolveStatus()
{
}

SolveStatus::SolveStatus(DecisionStatus decisionStatus)
{
    this->decisionStatus = decisionStatus;
}

SolveStatus::SolveStatus(DecisionStatus decisionStatus, std::string message)
{
    this->decisionStatus = decisionStatus;
    this->message = message;
}

DecisionStatus SolveStatus::getStatus()
{
    return decisionStatus;
}

std::string SolveStatus::getMessage()
{
    return message;
}

std::string SolveStatus::toString() {
    std::string status;
    switch (decisionStatus) {
        case None:
            status = "None";
            break;
        case Process:
            status = "Process";
            break;
        case Optimal:
            status = "Optimal";
            break;
        case Feasible:
            status = "Feasible";
            break;
        case Infeasible:
            status = "Infeasible";
            break;
        case InvalidModel:
            status = "InvalidModel";
            break;
        case InvalidData:
            status = "InvalidData";
            break;
    }
    return "Status=" + status + " message=" + getMessage();
}
