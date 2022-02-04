#include "node.h"
#include <vector>

class BTree {
public:
    BTree (int cName){
        root = nullptr;
        columnName = cName;
    }
    vector<Node*> search(int value) {
        //pass
    }
private:
    BTNode* root;
    int columnName; // 0 means ID column
};