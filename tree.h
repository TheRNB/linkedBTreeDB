#include "node.h"
#include <cstddef>
#include <vector>
#include <queue>

enum Comparisson {SMALLER=0, EQUAL, BIGGER};

class BTree {
public:
    BTree (int cName);
    std::vector<Node*> search(int queryValue, Comparisson queryType = EQUAL);
    Node* insert(int queryValue);
    Node* add(int queryValue, BTNode* curr);
    void deleteSingleNode(int queryValue, BTNode* curr);
private:
    BTNode* root;
    int columnName; // 0 means ID column
    int size;
};