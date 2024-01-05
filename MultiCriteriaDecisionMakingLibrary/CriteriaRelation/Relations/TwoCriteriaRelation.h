#ifndef DMLTESTER_TWOCRITERIARELATION_H
#define DMLTESTER_TWOCRITERIARELATION_H

#include "../../MathModel/Components/Criteria.h"

enum class CriteriaConstraint { More, MoreOrEquivalent, Equivalent, LessOrEquivalent, Less };

class TwoCriteriaRelation {
private:
    int firstId;
    int secondId;
    CriteriaConstraint constraint;

public:
    TwoCriteriaRelation(int firstCriteriaId, CriteriaConstraint constraint, int secondCriteriaId);
    TwoCriteriaRelation(const TwoCriteriaRelation& other);
    int getFirstCriteriaId();
    int getSecondCriteriaId();
    CriteriaConstraint getConstraint();

    bool isValid();
    bool isEqual(TwoCriteriaRelation* relation);
    bool isRespond(TwoCriteriaRelation* secondRelation);

    TwoCriteriaRelation* invert();
    CriteriaConstraint getInvertConstraint(CriteriaConstraint constraint);
};


#endif //DMLTESTER_TWOCRITERIARELATION_H
