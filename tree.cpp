#include "tree.h"

BTree::BTree (int cName){
    root = NULL;
    columnName = cName;
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
    }