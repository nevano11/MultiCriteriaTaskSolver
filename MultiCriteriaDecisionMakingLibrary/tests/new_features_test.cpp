#include <gtest/gtest.h>
#include "../MathModel/MathModel.h"
#include "../CriteriaRelation/Relations/SimpleCriteriaRelation.h"
#include "../CriteriaRelation/CriteriaRelationConverter.h"
#include "../DecisionMakingMethod/Methods/ElectreMethod.h"

using namespace std;

TEST(NewFeaturesTests, AddElectreMethod) {
    Criteria **criteriaArray = new Criteria *[3];
    criteriaArray[0] = new Criteria(1, "c1", CriteriaType::MAXIMIZATION);
    criteriaArray[1] = new Criteria(2, "c2", CriteriaType::MINIMIZATION);
    criteriaArray[2] = new Criteria(3, "c3", CriteriaType::MAXIMIZATION);

    EstimateVector **alternatives = new EstimateVector *[5];
    alternatives[0] = new EstimateVector(0, "alt0", new double[]{10, 200, 4}, 3);
    alternatives[1] = new EstimateVector(1, "alt1", new double[]{8, 160, 3}, 3);
    alternatives[2] = new EstimateVector(2, "alt2", new double[]{15, 250, 5}, 3);
    alternatives[3] = new EstimateVector(3, "alt3", new double[]{10, 180, 2}, 3);
    alternatives[4] = new EstimateVector(4, "alt4", new double[]{12, 240, 4}, 3);

    MathModel *mathModel = new MathModel(criteriaArray, 3, alternatives, 5);

    TwoCriteriaRelation **tcr = new TwoCriteriaRelation *[2];
    tcr[0] = new TwoCriteriaRelation(1, CriteriaConstraint::More, 2);
    tcr[1] = new TwoCriteriaRelation(2, CriteriaConstraint::More, 3);

    SimpleCriteriaRelation *relation = new SimpleCriteriaRelation(tcr, 3, 2);
    ElectreMethod *eM = new ElectreMethod(mathModel, relation);

    delete mathModel;
    delete relation;
    delete eM;
    ASSERT_TRUE(true);
}

TEST(NewFeaturesTests, AddElectreMethod2) {
    Criteria **criteriaArray = new Criteria *[3];
    criteriaArray[0] = new Criteria(1, "c1", CriteriaType::MAXIMIZATION);
    criteriaArray[1] = new Criteria(2, "c2", CriteriaType::MINIMIZATION);
    criteriaArray[2] = new Criteria(3, "c3", CriteriaType::MAXIMIZATION);

    TwoCriteriaRelation **rels = new TwoCriteriaRelation *[3];
    rels[0] = new TwoCriteriaRelation(1, CriteriaConstraint::Equivalent, 2);
    rels[1] = new TwoCriteriaRelation(1, CriteriaConstraint::More, 3);
    rels[2] = new TwoCriteriaRelation(2, CriteriaConstraint::More, 3);

    SimpleCriteriaRelation *relation = new SimpleCriteriaRelation(rels, 3, 3);

    auto weightCriteriaRelation = CriteriaRelationConverter::convertToWeightCriteriaRelation(relation);

    auto map = weightCriteriaRelation->getCriteriaWeightMap();
    for (const auto &item: map) {
        cout << item.first << " " << item.second << '\n';
    }

    delete weightCriteriaRelation;
    for (int i = 0; i < 3; ++i) {
        delete criteriaArray[i];
        delete rels[i];
    }
    delete[] criteriaArray;
    delete[] rels;
}