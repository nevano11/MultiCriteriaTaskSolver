#ifndef DMLTESTER_NODE_H
#define DMLTESTER_NODE_H

#include <set>

class Node {
private:
    std::set<int> criteriaIdSet;
    int depth = -1;
    std::set<Node*> childNodes;
public:
    Node();
    Node(int criteriaId);

    void addCriteriaOnNode(int criteriaId);
    void addChildNode(Node* childNode);

    bool containsCriteria(int criteriaId);

    std::set<Node*> getChildNodes();
    std::set<int> getCriteriaIdSet();

    int getDepth();
    void setDepth(int depth, int criteriaCount);

    Node *find(int criteriaId);

    void deleteChilds();
};


#endif //DMLTESTER_NODE_H
