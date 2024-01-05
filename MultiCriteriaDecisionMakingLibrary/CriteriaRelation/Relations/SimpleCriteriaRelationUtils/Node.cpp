#include <climits>
#include "Node.h"

Node::Node() {

}

Node::Node(int criteriaId) {
    criteriaIdSet.emplace(criteriaId);
}

std::set<Node *> Node::getChildNodes() {
    return childNodes;
}

void Node::addCriteriaOnNode(int criteriaId) {
    criteriaIdSet.insert(criteriaId);
}

void Node::addChildNode(Node *childNode) {
    if (childNode != nullptr)
        childNodes.insert(childNode);
}

std::set<int> Node::getCriteriaIdSet() {
    return criteriaIdSet;
}

Node *Node::find(int criteriaId) {
    if (criteriaIdSet.find(criteriaId) != criteriaIdSet.end())
        return this;

    for (const auto &childNode: childNodes) {
        auto findNode = childNode->find(criteriaId);
        if (findNode != nullptr)
            return findNode;
    }
    return nullptr;
}

bool Node::containsCriteria(int criteriaId) {
    return criteriaIdSet.find(criteriaId) != criteriaIdSet.end();
}

int Node::getDepth() {
    return depth;
}

void Node::setDepth(int depth, int criteriaCount) {
    if (this->depth < depth)
        this->depth = depth;
    if (depth >= criteriaCount) {
        this->depth = INT_MIN;
        return;
    }
    for (const auto &childNode: childNodes) {
        childNode->setDepth(this->depth + 1, criteriaCount);
    }
}

void Node::deleteChilds() {
    for (auto it = childNodes.begin(); it != childNodes.end();) {
        if (*it != nullptr)
            it = childNodes.erase(it);
        else it++;
    }
}
