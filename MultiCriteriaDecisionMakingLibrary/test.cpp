#include <gtest/gtest.h>
#include "CriteriaRelation/Relations/TwoCriteriaRelation.h"
#include "CriteriaRelation/Relations/SimpleCriteriaRelation.h"
#include "CriteriaRelation/CriteriaRelationConverter.h"
#include "CriteriaRelation/Relations/WeightCriteriaRelations/SimpleRankingMethod.h"

using namespace std;

void fillSimpleRelationsForConvertSimpleToAll(TwoCriteriaRelation** relations) {
    int i = 0;

    relations[i++] = new TwoCriteriaRelation(2, CriteriaConstraint::More, 4);
    relations[i++] = new TwoCriteriaRelation(2, CriteriaConstraint::More, 5);
    relations[i++] = new TwoCriteriaRelation(1, CriteriaConstraint::More, 3);
    relations[i++] = new TwoCriteriaRelation(2, CriteriaConstraint::More, 3);
    relations[i++] = new TwoCriteriaRelation(1, CriteriaConstraint::More, 4);
    relations[i++] = new TwoCriteriaRelation(3, CriteriaConstraint::More, 4);
    relations[i++] = new TwoCriteriaRelation(1, CriteriaConstraint::More, 5);
    relations[i++] = new TwoCriteriaRelation(4, CriteriaConstraint::More, 5);
    relations[i++] = new TwoCriteriaRelation(1, CriteriaConstraint::More, 2);
    relations[i++] = new TwoCriteriaRelation(3, CriteriaConstraint::More, 5);
}

TEST(CriteriaRelationConverterTests, ConvertSimpleToAll) {
    int criteriaCount = 5; // 1, 2, 3, 4, 5
    int relationCount = 10;
    int* expectedResult = new int[] {1, 2, 3, 4,5};

    auto simpleRelations = new TwoCriteriaRelation* [relationCount];
    fillSimpleRelationsForConvertSimpleToAll(simpleRelations);

    auto srcRelation = new SimpleCriteriaRelation(simpleRelations, criteriaCount, relationCount);
    auto resRelation = CriteriaRelationConverter::convertToAllCriteriaRelation(srcRelation);

    bool isEqual = true;
    for (int j = 0; j < resRelation->getSequenceSize(); ++j) {
        if (expectedResult[j] != resRelation->getIdSequence()[j])
            isEqual = false;
    }

    delete expectedResult;
    delete resRelation;

    ASSERT_TRUE(isEqual);
}

void fillSimpleRelationsForConvertSimpleToWeight(TwoCriteriaRelation** relations) {
    int i = 0;
    relations[i++] = new TwoCriteriaRelation(6, CriteriaConstraint::More, 11);
    relations[i++] = new TwoCriteriaRelation(7, CriteriaConstraint::Equivalent, 8);
    relations[i++] = new TwoCriteriaRelation(4, CriteriaConstraint::More, 3);
    relations[i++] = new TwoCriteriaRelation(5, CriteriaConstraint::More, 12);
    relations[i++] = new TwoCriteriaRelation(9, CriteriaConstraint::Equivalent, 10);
    relations[i++] = new TwoCriteriaRelation(11, CriteriaConstraint::More, 12);
    relations[i++] = new TwoCriteriaRelation(5, CriteriaConstraint::Equivalent, 6);
    relations[i++] = new TwoCriteriaRelation(12, CriteriaConstraint::More, 9);
    relations[i++] = new TwoCriteriaRelation(3, CriteriaConstraint::More, 6);
    relations[i++] = new TwoCriteriaRelation(2, CriteriaConstraint::Equivalent, 3);
    relations[i++] = new TwoCriteriaRelation(4, CriteriaConstraint::More, 2);
    relations[i++] = new TwoCriteriaRelation(11, CriteriaConstraint::More, 10);
    relations[i++] = new TwoCriteriaRelation(3, CriteriaConstraint::More, 12);
    relations[i++] = new TwoCriteriaRelation(1, CriteriaConstraint::Equivalent, 4);
    relations[i++] = new TwoCriteriaRelation(4, CriteriaConstraint::More, 5);
    relations[i++] = new TwoCriteriaRelation(9, CriteriaConstraint::Equivalent, 7);
}

TEST(CriteriaRelationConverterTests, ConvertSimpleToWeight) {
    int criteriaCount = 12; // 1 .. 12
    int relationCount = 16;

    std::map<int, double> criteriaRanks = {
            {1, 1.5}, {4, 1.5}, {2, 3.5}, {3, 3.5}, {5, 5.5},{6, 5.5},
            {7, 10.5}, {8, 10.5}, {9, 10.5}, {10, 10.5}, {11, 7}, {12, 8}
    };

    auto expectedRelation = new SimpleRankingMethod(criteriaCount, criteriaRanks);

    auto simpleRelations = new TwoCriteriaRelation* [relationCount];
    fillSimpleRelationsForConvertSimpleToWeight(simpleRelations);

    auto srcRelation = new SimpleCriteriaRelation(simpleRelations, criteriaCount, relationCount);
    auto resRelation = CriteriaRelationConverter::convertToWeightCriteriaRelation(srcRelation);

    ASSERT_EQ(resRelation->getCriteriaWeightMap(), expectedRelation->getCriteriaWeightMap());
    delete expectedRelation;
    delete resRelation;
}

TEST(CriteriaRelationConverterTests, ConvertAllToWeight) {
    int criteriaCount = 5; // 1, 2, 3, 4, 5

    std::map<int, double> criteriaRanks = {
            {1, 1}, {2, 2},{3, 3},{4, 4},{5, 5}
    };
    auto expectedRelation = new SimpleRankingMethod(criteriaCount, criteriaRanks);
    auto srcRelation = new AllCriteriaRelation(criteriaCount, new int[] {1, 2, 3, 4, 5});
    auto resRelation = CriteriaRelationConverter::convertToWeightCriteriaRelation(srcRelation);

    ASSERT_EQ(resRelation->getCriteriaWeightMap(), expectedRelation->getCriteriaWeightMap());
    delete expectedRelation;
    delete resRelation;
}

TEST(CriteriaRelationConverterTests, ConvertAllToSimple) {
    int criteriaCount = 5; // 1, 2, 3, 4, 5
    int relationCount = 4;

    auto simpleRelations = new TwoCriteriaRelation* [relationCount];
    int i = 0;
    simpleRelations[i++] = new TwoCriteriaRelation(1, CriteriaConstraint::More, 2);
    simpleRelations[i++] = new TwoCriteriaRelation(2, CriteriaConstraint::More, 3);
    simpleRelations[i++] = new TwoCriteriaRelation(3, CriteriaConstraint::More, 4);
    simpleRelations[i++] = new TwoCriteriaRelation(4, CriteriaConstraint::More, 5);

    auto srcRelation = new AllCriteriaRelation(criteriaCount, new int[] {1, 2, 3, 4, 5});
    auto resRelation = CriteriaRelationConverter::convertToSimpleCriteriaRelation(srcRelation);

    bool isValid = true;
    for (int j = 0; j < resRelation->getRelationCount(); ++j) {
        auto rel = resRelation->getTwoCriteriaRelationArray()[j];
        if (!rel->isEqual(simpleRelations[j]))
            isValid = false;
    }

    ASSERT_TRUE(isValid);
    delete simpleRelations;
    delete resRelation;
}

TEST(CriteriaRelationConverterTests, ConvertWeightToAll) {
    int criteriaCount = 5; // 1 .. 5

    std::map<int, double> criteriaRanks = {
            {1, 1}, {2, 2},{3, 3},{4, 4},{5, 5}
    };
    auto expectedIdSequence = new int[] {1, 2, 3, 4, 5};
    auto srcRelation = new SimpleRankingMethod(criteriaCount, criteriaRanks);
    auto resRelation = CriteriaRelationConverter::convertToAllCriteriaRelation(srcRelation);

    bool isEqual = true;
    for (int j = 0; j < resRelation->getSequenceSize(); ++j)
        if (expectedIdSequence[j] != resRelation->getIdSequence()[j])
            isEqual = false;

    ASSERT_TRUE(isEqual);
    delete resRelation;
}

TEST(CriteriaRelationConverterTests, ConvertWeightToSimple) {
    int criteriaCount = 5; // 1 .. 5

    std::map<int, double> criteriaRanks = {
            {1, 1.5}, {2, 1.5},{3, 3},{4, 4},{5, 5}
    };

    int relationCount = 4;

    auto simpleRelations = new TwoCriteriaRelation* [relationCount];
    int i = 0;
    simpleRelations[i++] = new TwoCriteriaRelation(1, CriteriaConstraint::Equivalent, 2);
    simpleRelations[i++] = new TwoCriteriaRelation(2, CriteriaConstraint::More, 3);
    simpleRelations[i++] = new TwoCriteriaRelation(3, CriteriaConstraint::More, 4);
    simpleRelations[i++] = new TwoCriteriaRelation(4, CriteriaConstraint::More, 5);

    auto srcRelation = new SimpleRankingMethod(criteriaCount, criteriaRanks);
    auto resRelation = CriteriaRelationConverter::convertToSimpleCriteriaRelation(srcRelation);

    bool isValid = true;
    for (int j = 0; j < relationCount; ++j) {
        auto currentRel = simpleRelations[j];
        bool isResRelationContainsExpectedRelation = false;
        for (int k = 0; k < resRelation->getRelationCount(); ++k) {
            if (resRelation->getTwoCriteriaRelationArray()[k]->isEqual(currentRel))
                isResRelationContainsExpectedRelation = true;
        }
        if (!isResRelationContainsExpectedRelation)
            isValid = false;
    }

    ASSERT_TRUE(isValid);
    delete resRelation;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}