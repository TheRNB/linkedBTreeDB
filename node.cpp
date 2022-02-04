#include "node.h"

BTNode::BTNode() {
    sizee = 0;
        parentIndex = -1;
        for (int i = 0; i < CHILD_MAX; ++i)
            keys[i] = children[i] = nullptr;
}

void BTNode::addNode(Node* newNode, int posID = 0) {
    // ADDS A NODE SOLELY IN BTNode AND NOT THE CHILDREN
    for (int i = CHILD_MAX; i > posID; --i) {
        keys[i] = keys[i-1];
        children[i] = children[i-1];
    }
    return;
}

void BTNode::delNode(int posID = 0) {
    // DELETES A NODE SOLELY IN BTNode AND NOT THE CHILDREN
        for (int i = posID; i <= CHILD_MAX; ++i) {
            keys[i] = keys[i+1];
            children[i] = children[i+1];
        }
        return;
}

int BTNode::size() {
    return sizee;
}

int BTNode::index() {
    return parentIndex;
}
