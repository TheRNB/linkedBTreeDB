#include "node.h"
#include <cstddef>
#include <vector>
#include <queue>

enum Comparisson {SMALLER=0, EQUAL, BIGGER};

class BTree {
public:
    BTree (int cName);
    std::vector<Node*> search(int queryValue, Comparisson queryType);
    Node* insert(int queryValue);
    void deleteSingleNode(Node* queryValue, BTNode* curr);
    int size();
    int getName();
private:
    BTNode* root;
    int columnName; // 0 means ID column
    int sizee;
    Node* add(int queryValue, BTNode* curr);
};
