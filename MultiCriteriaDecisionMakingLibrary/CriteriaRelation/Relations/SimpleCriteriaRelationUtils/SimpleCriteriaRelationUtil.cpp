#include <vector>
#include <algorithm>
#include "SimpleCriteriaRelationUtil.h"

SimpleCriteriaRelationUtil::SimpleCriteriaRelationUtil(SimpleCriteriaRelation *simpleCriteriaRelation) {
    isValid = true;
    this->simpleCriteriaRelation = simpleCriteriaRelation;

    int relationCount = simpleCriteriaRelation->getRelationCount();
    auto relations = simpleCriteriaRelation->getTwoCriteriaRelationArray();
    std::vector<TwoCriteriaRelation*> skippedRelations;
    std::vector<Node*> nodesWithMoreCriteria;

    for (int i = 0; i < relationCount; ++i) {
        auto currentRelation = relations[i]->getConstraint() == CriteriaConstraint::Less ? relations[i]->invert() : relations[i];
        if (currentRelation->getConstraint() == CriteriaConstraint::Equivalent) {
            auto c1 = currentRelation->getFirstCriteriaId();
            auto c2 = currentRelation->getSecondCriteriaId();
            auto iterFirst = std::find_if(nodesWithMoreCriteria.begin(), nodesWithMoreCriteria.end(), [c1](Node *obj) {
                return obj->containsCriteria(c1);
            });
            bool firstFinded = iterFirst != nodesWithMoreCriteria.end();

            auto iterSecond = std::find_if(nodesWithMoreCriteria.begin(), nodesWithMoreCriteria.end(), [c2](Node *obj) {
                return obj->containsCriteria(c2);
            });
            bool secondFinded = iterSecond != nodesWithMoreCriteria.end();

            if (!(firstFinded || secondFinded)) {
                auto nodeWithCriteriaSet = new Node(c1);
                nodeWithCriteriaSet->addCriteriaOnNode(c2);
                nodesWithMoreCriteria.push_back(nodeWithCriteriaSet);
            } else if (firstFinded && secondFinded && iterFirst != iterSecond) {
                auto criteriaFromSecondList = (*iterSecond)->getCriteriaIdSet();
                for (const auto &criteriaFromSecond: criteriaFromSecondList)
                    (*iterFirst)->addCriteriaOnNode(criteriaFromSecond);
                delete (*iterSecond);
                nodesWithMoreCriteria.erase(iterSecond);
            } else
                firstFinded ? (*iterFirst)->addCriteriaOnNode(c2) : (*iterSecond)->addCriteriaOnNode(c1);
        }
        else {
            if (currentRelation->getConstraint() == CriteriaConstraint::More) {
                skippedRelations.push_back(currentRelation);
            }
            else {
                isValid = false;
                return;
            }
        }
    }

    while (skippedRelations.size() > 0) {
        int sizeBefore = skippedRelations.size();
        for (auto it = skippedRelations.begin(); it != skippedRelations.end();) {
            auto currentRelation = *it;
            int c1 = currentRelation->getFirstCriteriaId();
            int c2 = currentRelation->getSecondCriteriaId();

            // a > a - невалидно
            if (c1 == c2) {
                isValid = false;
                return;
            }

            auto iterFirst = std::find_if(nodesWithMoreCriteria.begin(), nodesWithMoreCriteria.end(), [c1](Node *obj) {
                return obj->containsCriteria(c1);
            });
            auto iterSecond = std::find_if(nodesWithMoreCriteria.begin(), nodesWithMoreCriteria.end(), [c2](Node *obj) {
                return obj->containsCriteria(c2);
            });

            bool firstFinded = iterFirst != nodesWithMoreCriteria.end();
            bool secondFinded = iterSecond != nodesWithMoreCriteria.end();

            if (root == nullptr) {
                if (firstFinded) {
                    root = (*iterFirst);
                    nodesWithMoreCriteria.erase(iterFirst);
                } else
                    root = new Node(c1);
                if (secondFinded) {
                    root->addChildNode(*iterSecond);
                    nodesWithMoreCriteria.erase(iterSecond);
                } else
                    root->addChildNode(new Node(c2));
                it = skippedRelations.erase(it);
            } else {
                Node* findFirstOnTree = root->find(c1);
                Node* findSecondOnTree = root->find(c2);

                // Если ничего не найдено то пропускаем
                if (findFirstOnTree == nullptr && findSecondOnTree == nullptr) {
                    it++;
                    continue;
                }

                // Найдено отношение a > b и при этом a ~ b
                if (findFirstOnTree == findSecondOnTree) {
                    isValid = false;
                    return;
                }

                // Оба узла уже есть в дереве
                if (findFirstOnTree != nullptr && findSecondOnTree != nullptr) {
                    findFirstOnTree->addChildNode(findSecondOnTree);
                    it = skippedRelations.erase(it);
                    continue;
                }

                if (findFirstOnTree != nullptr) {
                    if (secondFinded) {
                        findFirstOnTree->addChildNode(*iterSecond);
                        nodesWithMoreCriteria.erase(iterSecond);
                    } else {
                        findFirstOnTree->addChildNode(new Node(c2));
                    }
                    it = skippedRelations.erase(it);
                    continue;
                }

                if (findSecondOnTree == root) {
                    if (firstFinded) {
                        root = *iterFirst;
                        nodesWithMoreCriteria.erase(iterFirst);
                    } else {
                        root = new Node(c1);
                    }
                    root->addChildNode(findSecondOnTree);
                    it = skippedRelations.erase(it);
                    continue;
                }
            }
            it++;
        }
        if (sizeBefore - skippedRelations.size() == 0) {
            isValid = false;
            return;
        }
    }
}

void SimpleCriteriaRelationUtil::print() {
    if (root == nullptr) {
        std::cout << "Empty tree";
        return;
    }
    root->setDepth(0, simpleCriteriaRelation->getCriteriaCount());
    printNode(0, root);
}

void SimpleCriteriaRelationUtil::printNode(int level, Node *node) {
    for (int i = 0; i < level; ++i) {
        std::cout << "|";
    }
    std::cout << "( ";
    for (const auto &item: node->getCriteriaIdSet()) {
        std::cout << item << " ";
    }
    std::cout << ") " << node->getDepth() << std::endl;
    for (const auto &item: node->getChildNodes()) {
        printNode(level + 1, item);
    }
}

SimpleCriteriaRelationUtil::~SimpleCriteriaRelationUtil() {
    if (root == nullptr)
        return;

    root->deleteChilds();
    delete root;
}

AllCriteriaRelation *SimpleCriteriaRelationUtil::toAllCriteriaRelation() {
    if (!isValid)
        return nullptr;
    int* idSequence = new int[simpleCriteriaRelation->getCriteriaCount()];
    root->setDepth(0, simpleCriteriaRelation->getCriteriaCount());
    return nodeToLexicograficOptimization(idSequence, root) ? new AllCriteriaRelation(simpleCriteriaRelation->getCriteriaCount(), idSequence) : nullptr;
}

bool SimpleCriteriaRelationUtil::nodeToLexicograficOptimization(int* idSequence, Node *node) {
    if (node->getDepth() < 0 || node->getCriteriaIdSet().size() < 1)
        return false;

    idSequence[node->getDepth()] = *node->getCriteriaIdSet().begin();
    for (const auto &childNode: node->getChildNodes()) {
        if (childNode->getDepth() == node->getDepth() + 1)
            return nodeToLexicograficOptimization(idSequence, childNode);
    }

    return true;
}

bool SimpleCriteriaRelationUtil::nodeToWeightOptimization(Node *node, int maxMark, std::map<int, double>& criteriaMarkMap) {
    auto set = node->getCriteriaIdSet();

    if (node->getDepth() < 0 || set.size() < 1)
        return false;

    int sum = 0;
    for (int i = 0; i < set.size(); ++i) {
        sum += maxMark++;
    }
    double avg = sum * 1.0 / set.size();
    for (const auto &criteriaId: set) {
        criteriaMarkMap.emplace(criteriaId, avg);
    }
    for (const auto &childNode: node->getChildNodes()) {
        if (childNode->getDepth() == node->getDepth() + 1)
            return nodeToWeightOptimization(childNode, maxMark, criteriaMarkMap);
    }

    return true;
}

SimpleRankingMethod *SimpleCriteriaRelationUtil::toWeightCriteriaRelation() {
    if (!isValid)
        return nullptr;
    root->setDepth(0, simpleCriteriaRelation->getCriteriaCount());
    std::map<int, double> criteriaMarkMap;
    return nodeToWeightOptimization(root, 1, criteriaMarkMap) ? new SimpleRankingMethod(simpleCriteriaRelation->getCriteriaCount(), criteriaMarkMap) : nullptr;
}
