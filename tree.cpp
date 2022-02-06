#include "tree.h"

BTree::BTree (int cName){
    root = NULL;
    columnName = cName;
    size = 0;
}

Node* BTree::add(int queryValue, BTNode* curr) {
    if (curr == NULL) {
        curr = curr->getParent();
        Node* newNode = new Node();
        newNode->data = queryValue;
        newNode->self = curr;
        curr->addNode(newNode);
        
        return newNode;
    }

    Node* result = NULL;
    for (int i = 0; i < curr->size(); ++i) {
        if (queryValue <= curr->getKey(i)->data) {
            result = add(queryValue, curr->getChild(i));
            break;
        } else if (i == curr->size() - 1) {
            result = add(queryValue, curr->getChild(i+1));
            break;
        }
    }

    if (curr->size() == CHILD_MAX) {
        Node* twoOnOne = curr->getKey(CHILD_MAX/2);
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
            root->setParent(newRoot);
            root = newRoot;
        }
        newNodeParentIndex = curr->getParent()->addNode(curr->getKey(CHILD_MAX/2));

        curr->getParent()->setChild(curr, newNodeParentIndex);
        curr->getParent()->setChild(splitNode, newNodeParentIndex+1);

        for (int i = CHILD_MAX/2; i < CHILD_MAX; ++i) {
            curr->delNode(i);
        }
    }
    return result;
}

Node* BTree::insert(int queryValue) {
    if (root == NULL) {
        BTNode* newBTNode = new BTNode(columnName, NULL);
        Node* newNode = new Node();
        newNode->data = queryValue;
        newNode->self = newBTNode;
        newBTNode->addNode(newNode);
        root = newBTNode;
        return;
    }
    add(queryValue, root);
    size++;
    return;
}

std::vector<Node*> BTree::search(int queryValue, Comparisson queryType = EQUAL) {
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
            
        if (queryType == SMALLER or queryType == BIGGER) {
            for (int i = 0; i < curr->size(); ++i) {
                if (queryType == SMALLER)
                    if (curr->getKey(i)->data < queryValue)
                        result.push_back(curr->getKey(i));
                    else
                        break;
                
                else if (queryType == EQUAL)
                    if (curr->getKey(i)->data == queryValue)
                        result.push_back(curr->getKey(i));

                searchNode.push(curr->getChild(i));
                if (i == curr->size()-1)
                    searchNode.push(curr->getChild(i+1));
            }
        }
        else if (queryType == BIGGER) {
            for (int i = curr->size()-1; i >= 0; --i) {
                if (curr->getKey(i)->data > queryValue)
                    result.push_back(curr->getKey(i));
                else
                    break;

                searchNode.push(curr->getChild(i+1));
                if (i == 0)
                    searchNode.push(curr->getChild(i));
            }
        }
    }
    return result;
}
