#include "tree.h"
#include<iostream>

BTree::BTree (int cName){
    root = NULL;
    columnName = cName;
    sizee = 0;
}

Node* BTree::add(int queryValue, BTNode* curr, BTNode* parent) {
    if (curr == NULL) {
        Node* newNode = new Node();
        newNode->data = queryValue;
        newNode->self = parent;
        parent->addNode(newNode);
        
        return newNode;
    }

    Node* result = NULL;
    for (int i = 0; i < curr->size(); ++i) {
        if (queryValue <= curr->getKey(i)->data) {
            result = add(queryValue, curr->getChild(i), curr);
            break;
        } else if (i == curr->size() - 1) {
            result = add(queryValue, curr->getChild(i+1), curr);
            break;
        }
    }

    if (curr->size() == CHILD_MAX) {
        Node* localRoot = curr->getKey(CHILD_MAX/2);
        BTNode* splitNode = new BTNode(columnName, curr->getParent());
        for(int i = (CHILD_MAX/2)+1; i < CHILD_MAX; ++i) {
            splitNode->addNodeByIndex(curr->getKey(i), splitNode->size() );
            splitNode->setChild(curr->getChild(i), splitNode->size()-1);
            if (i == CHILD_MAX-1) {
                splitNode->setChild(curr->getChild(i+1), splitNode->size());    
            }
        }
        
        int newNodeParentIndex = -1;
        if (curr->getParent() == NULL) { //curr node is the root
            BTNode* newRoot = new BTNode(columnName, NULL);
            curr->setParent(newRoot);
            splitNode->setParent(newRoot);
            root = newRoot;
        }
        newNodeParentIndex = curr->getParent()->addNode(localRoot);
        curr->getParent()->setChild(curr, newNodeParentIndex);
        curr->getParent()->setChild(splitNode, newNodeParentIndex+1);

        for (int i = CHILD_MAX/2; i < CHILD_MAX; ++i) {
            curr->delNode(i);
        }
    }
    return result;
}

Node* BTree::insert(int queryValue) {
    sizee++;
    if (root == NULL) {
        BTNode* newBTNode = new BTNode(columnName, NULL);
        Node* newNode = new Node();
        newNode->data = queryValue;
        newNode->self = newBTNode;
        newBTNode->addNode(newNode);
        root = newBTNode;
        return newNode;
    }
    Node* newNode = add(queryValue, root, NULL);
    return newNode;
}

/*void BTree::deleteSingleNode(Node* queryValue, BTNode* curr) {
    if (curr == NULL) {
        return;
    }

    int queryValueIndex = -1;
    for(int i = 0; i < curr->size(); ++i) {
        if (curr->getKey(i)->data < queryValue->data) {
            queryValueIndex = i;
        }
    }
    if (queryValueIndex+1 < curr->size() and 
        curr->getKey(queryValueIndex+1)->data == queryValue->data) { //found the desired node
        
        if (curr->getChild(queryValueIndex+1) == NULL or curr->getChild(queryValueIndex+2) == NULL) {
            //It is a leaf
            if (curr->getChild(queryValueIndex+1) != NULL)
                curr->setChild(curr->getChild(queryValueIndex+1), queryValueIndex+2);
            sizee--;

            curr->delNode(queryValueIndex+1);
            if (curr->size() >= CHILD_MIN)
                return;


            for (int i = 0; i <= curr->getParent()->size(); ++i) {
                if (curr->getParent()->getChild(i) == curr) {
                    if (i < curr->getParent()->size() - 1 and
                        curr->getParent()->getChild(i+1)->size() > CHILD_MIN) {
                        BTNode* rightSibling = curr->getParent()->getChild(i+1);
                        curr->addNodeByIndex(curr->getParent()->getKey(i), curr->size());
                        curr->getParent()->setKey(rightSibling->getKey(), i);
                        rightSibling->delNode();
                    } else if (i > 0 and
                        curr->getParent()->getChild(i)->size() > CHILD_MIN) {
                        BTNode* leftSibling = curr->getParent()->getChild(i);
                        curr->addNodeByIndex(curr->getParent()->getKey(i), 0);
                        curr->getParent()->setKey(leftSibling->getKey(leftSibling->size()-1), i);
                        leftSibling->delNode(leftSibling->size()-1);
                    } else if (i < curr->getParent()->size() - 1) {
                        curr->addNode(curr->getParent()->getKey(i));
                        BTNode* rightSibling = curr->getParent()->getChild(i+1);
                        for (int i = 0; i < rightSibling->size(); ++i) {
                            curr->addNodeByIndex(rightSibling->getKey(i), curr->size());
                            curr->setChild(rightSibling->getChild(i), curr->size()-1);
                        }
                        delete curr->getParent()->getChild(i+1);
                        curr->getParent()->setChild(curr, i);
                        curr->getParent()->delNode(i);
                    } else {
                        curr->addNode(curr->getParent()->getKey(i));
                        BTNode* leftSibling = curr->getParent()->getChild(i);
                        for (int i = leftSibling->size()-1; i >= 0; --i) {
                            curr->addNodeByIndex(leftSibling->getKey(i), 0);
                            curr->setChild(leftSibling->getChild(i), 0);
                        }
                        delete curr->getParent()->getChild(i);
                        curr->getParent()->setChild(curr, i+1);
                        curr->getParent()->delNode(i);
                    }
                }
                return;
            }
        } else {
            //It is an internal node
            Node* tmp = curr->getChild(queryValueIndex+2)->getKey();
            curr->getChild(queryValueIndex+2)->setKey(curr->getKey(queryValueIndex+1));
            curr->setKey(tmp, queryValueIndex+1);
            deleteSingleNode(queryValue, curr->getChild(queryValueIndex+2));
            return;
        }


    } else {
        deleteSingleNode(queryValue, curr->getChild(queryValueIndex+1));
    }
}*/

void BTree::deleteSingleNode(Node* queryValue, BTNode* curr) {
    if (curr == NULL) {
        return;
    }

    int index = -1;
    for (int i = 0; i < curr->size(); ++i) {
        if (curr->getKey(i) == queryValue) {
            index = i;
            break;
        }
    }
    if (index == -1)
        return;
    
    if (curr->getChild(index) != NULL and curr->getChild(index+1) != NULL) {
        //curr is an internal node here
        curr->setKey(curr->getChild(index+1)->getKey(0), index);
        curr->getChild(index+1)->setKey(queryValue, 0);
        deleteSingleNode(queryValue, curr->getChild(index+1));
        return;
    }
    
    //curr is a leaf
    curr->delNode(index);
    while (curr != root) {
        if(curr->size() >= CHILD_MIN)
            return;

        int parentIndex = -1;
        for (int i = 0; i <= curr->getParent()->size(); ++i) {
            if (curr->getParent()->getChild(i) == curr) {
                parentIndex = i;
                break;
            }
        }

        if (parentIndex < curr->getParent()->size() and 
            curr->getParent()->getChild(parentIndex+1)->size() > CHILD_MIN) {
                BTNode* rightBrother = curr->getParent()->getChild(parentIndex+1);
                curr->addNodeByIndex(curr->getParent()->getKey(parentIndex), curr->size());
                curr->getParent()->setKey(rightBrother->getKey(0), parentIndex);
                curr->setChild(rightBrother->getChild(0), curr->size());
                rightBrother->delNode(0);
        }

        if (parentIndex > 0 and 
            curr->getParent()->getChild(parentIndex-1)->size() > CHILD_MIN) {
                BTNode* leftBrother = curr->getParent()->getChild(parentIndex-1);
                curr->addNodeByIndex(curr->getParent()->getKey(parentIndex-1), 0);
                curr->getParent()->setKey(leftBrother->getKey(leftBrother->size()-1), parentIndex-1);
                curr->setChild(leftBrother->getChild(leftBrother->size()), 0);
                leftBrother->delNode(leftBrother->size()-1);
        }

        if (parentIndex < curr->getParent()->size()) {
                BTNode* rightBrother = curr->getParent()->getChild(parentIndex+1);
                curr->addNode(curr->getParent()->getKey(parentIndex));
                int childCount = curr->size();
                curr->setChild(rightBrother->getChild(0), childCount++);
                for (int i = 1; i <= rightBrother->size(); ++i) {
                    curr->addNodeByIndex(rightBrother->getKey(i-1), curr->size());
                    curr->setChild(rightBrother->getChild(i), childCount++);
                }
                delete rightBrother;
        }

        if (parentIndex > 0) {
                BTNode* leftBrother = curr->getParent()->getChild(parentIndex-1);
                curr->addNode(curr->getParent()->getKey(parentIndex-1));
                curr->setChild(leftBrother->getChild(leftBrother->size()), 0);
                for (int i = leftBrother->size(); i > 0; --i) {
                    curr->setChild(leftBrother->getChild(i), 0);
                    curr->addNodeByIndex(leftBrother->getKey(i-1), 0);
                }
                curr->setChild(leftBrother->getChild(0), 0);
                delete leftBrother;
        }
        curr->getParent()->delNode(parentIndex);
        if(curr->getParent()->size() == 0) {
            BTNode* emptyPar = curr->getParent();
            curr->setParent(curr->getParent()->getParent());
            delete emptyPar;
            if (curr->getParent() == NULL) {
                root = curr;
                continue;
            }
        }
        curr = curr->getParent();
    }
    return;
}

void BTree::deleteNode(Node* queryValue, BTNode* curr) {
    sizee--;
    deleteSingleNode(queryValue, curr);
    return;
}

std::vector<Node*> BTree::search(int queryValue, Comparisson queryType) {
    std::vector<Node*> result;
    if (root == NULL)
        return result;

    std::queue<BTNode*> searchNode;
    searchNode.push(root);
    BTNode* curr;
    while(searchNode.empty() == false) {
        curr = searchNode.front();
        searchNode.pop();
        if (curr == NULL) continue;
            
        if (queryType == SMALLER or queryType == EQUAL) {
            for (int i = 0; i < curr->size(); ++i) {
                if (queryType == SMALLER) {
                    if (curr->getKey(i)->data < queryValue) {
                        result.push_back(curr->getKey(i));
                        searchNode.push(curr->getChild(i));
                    } else {
                        searchNode.push(curr->getChild(i));
                        break;
                    }
                    if (i == curr->size()-1) {
                        searchNode.push(curr->getChild(i+1));
                    }
                } else if (queryType == EQUAL) {
                    if (curr->getKey(i)->data == queryValue) {
                        result.push_back(curr->getKey(i));
                        searchNode.push(curr->getChild(i));
                    } else if (curr->getKey(i)->data > queryValue) {
                        searchNode.push(curr->getChild(i));
                        break;                    
                    }
                    if (i == curr->size()-1) {
                        searchNode.push(curr->getChild(i+1));
                    }
                }
                

            }
        } else if (queryType == BIGGER) {
            for (int i = curr->size()-1; i >= 0; --i) {
                if (curr->getKey(i)->data > queryValue) {
                    searchNode.push(curr->getChild(i+1));
                    result.push_back(curr->getKey(i));
                } else {
                    searchNode.push(curr->getChild(i+1));
                    break;
                }
                if (i == 0) {
                    searchNode.push(curr->getChild(i));
                }
            }
        }
    }
    return result;
}

int BTree::size() {
    return sizee;
}

int BTree::getName() {
    return columnName;
}
