#include <gtest/gtest.h>
#include "../MathModel/Components/Criteria.h"

using namespace std;

TEST(CppFeaturesTests, Teststst) {
    std::unique_ptr<Criteria> pLarge(new Criteria(1, "aboba", CriteriaType::MAXIMIZATION));

    Criteria* b = pLarge.get();

    cout << b->getId();

    cout << pLarge->getName();
}