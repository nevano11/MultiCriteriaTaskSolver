#ifndef DMLTESTER_SIMPLECRITERIARELATIONUTIL_H
#define DMLTESTER_SIMPLECRITERIARELATIONUTIL_H

#include "Node.h"
#include "../SimpleCriteriaRelation.h"
#include "../AllCriteriaRelation.h"
#include "../WeightCriteriaRelations/SimpleRankingMethod.h"

class SimpleCriteriaRelationUtil {
private:
    Node* root = nullptr;
    bool isValid = true;
    SimpleCriteriaRelation* simpleCriteriaRelation;

    void printNode(int level, Node* node);
    bool nodeToLexicograficOptimization(int *idSequence, Node* node);
    bool nodeToWeightOptimization(Node* node, int maxMark, std::map<int, double>& criteriaMarkMap);
public:
    SimpleCriteriaRelationUtil(SimpleCriteriaRelation *simpleCriteriaRelation);
    ~SimpleCriteriaRelationUtil();
    void print();

    AllCriteriaRelation* toAllCriteriaRelation();
    SimpleRankingMethod* toWeightCriteriaRelation();
};


#endif //DMLTESTER_SIMPLECRITERIARELATIONUTIL_H
