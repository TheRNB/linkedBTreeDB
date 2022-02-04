#include "node.h"
#include <cstddef>

BTNode::BTNode(int cID) {
    sizee = 0;
    parentIndex = -1;
    for (int i = 0; i < CHILD_MAX; ++i) {
        keys[i] = NULL;
        children[i] = NULL;
    }
    columnName = cID;
}

void BTNode::addNode(Node* newNode, int posID = 0) {
    // ADDS A NODE SOLELY IN BTNode AND NOT THE CHILDREN
    for (int i = CHILD_MAX; i > posID; --i) {
        keys[i] = keys[i-1];
        children[i] = children[i-1];
    }
    sizee++;
    return;
}

void BTNode::delNode(int posID = 0) {
    // DELETES A NODE SOLELY IN BTNode AND NOT THE CHILDREN
    for (int i = posID; i <= CHILD_MAX; ++i) {
        keys[i] = keys[i+1];
        children[i] = children[i+1];
    }
    sizee--;
        return;
}

int BTNode::size() {
    return sizee;
}

int BTNode::index() {
    return parentIndex;
}

Node* BTNode::getKey(int posID = 0) {
    return keys[posID];
}

BTNode* BTNode::getChild(int posID = 0) {
    return children[posID];
}
