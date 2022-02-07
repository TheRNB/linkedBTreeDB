#include "node.h"
#include <cstddef>

BTNode::BTNode(int cID, BTNode* par = NULL) {
    sizee = 0;
    //parentIndex = -1;
    for (int i = 0; i < CHILD_MAX; ++i) {
        keys[i] = NULL;
        children[i] = NULL;
    }
    columnName = cID;
    parent = par;
}

void BTNode::addNodeByIndex(Node* newNode, int posID = 0) {
    // ADDS A NODE SOLELY IN BTNode AND NOT THE CHILDREN
    for (int i = CHILD_MAX; i > posID; --i) {
        keys[i] = keys[i-1];
        children[i] = children[i-1];
    }
    keys[posID] = newNode;
    sizee++;
    return;
}

int BTNode::addNode(Node* newNode) {
    for (int i = 0; i < sizee; ++i) {
        if (keys[i]->data >= newNode->data) {
            addNodeByIndex(newNode, i);
            return i;
        }
    }
    addNodeByIndex(newNode, sizee);
    return sizee-1;
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

//int BTNode::index() {
//    return parentIndex;
//}

//void BTNode::setParentIndex(int newIndex) {
//    parentIndex = newIndex;
//}

Node* BTNode::getKey(int posID = 0) {
    return keys[posID];
}

BTNode* BTNode::getChild(int posID = 0) {
    return children[posID];
}

BTNode* BTNode::getParent() {
    return parent;
}

void BTNode::setChild(BTNode* newChild, int posID) {
    children[posID] = newChild;
    return;
}

void BTNode::setParent(BTNode* newParent) {
    parent = newParent;
    return;
}

void BTNode::setKey(Node* newKey, int posID = 0) {
    keys[posID] = newKey;
    return;
}
