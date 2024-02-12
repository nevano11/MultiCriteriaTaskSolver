#ifndef MULTICRITERIADECISIONMAKINGLIBRARY_ALFABETAINFO_H
#define MULTICRITERIADECISIONMAKINGLIBRARY_ALFABETAINFO_H

#include "../DecisionMakerInfo.h"

class AlfaBetaInfo : public DecisionMakerInfo{
private:
    double alfa;
    double beta;
public:
    AlfaBetaInfo(double alfa, double beta);
    double getAlfa();
    double getBeta();
    bool isValid();
};


#endif //MULTICRITERIADECISIONMAKINGLIBRARY_ALFABETAINFO_H
