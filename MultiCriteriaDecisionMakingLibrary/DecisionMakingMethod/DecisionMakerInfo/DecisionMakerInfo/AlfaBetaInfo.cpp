#include "AlfaBetaInfo.h"

AlfaBetaInfo::AlfaBetaInfo(double alfa, double beta) {
    this->alfa = alfa;
    this->beta = beta;
}

double AlfaBetaInfo::getAlfa() {
    return this->alfa;
}

double AlfaBetaInfo::getBeta() {
    return this->beta;
}

bool AlfaBetaInfo::isValid() {
    if (this->alfa >= this->beta) {
        return false;
    }
    if (this->alfa < 0 || this->alfa > 0,5 || this->beta < 0,5 || this->beta > 1) {
        return false;
    }
    return true;
}
