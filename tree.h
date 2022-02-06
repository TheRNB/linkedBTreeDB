#include "node.h"
#include <cstddef>
#include <vector>
#include <queue>

enum Comparisson {SMALLER=0, EQUAL, BIGGER};
enum Type {STRING=0, INTEGER, DATE};

class BTree {
public:
    BTree (int cName);
    std::vector<Node*> search(int queryValue, Comparisson queryType = EQUAL);
    Node* insert(int queryValue);
    Node* add(int queryValue, BTNode* root);
    void deleteSingleNode(int queryValue);
private:
    BTNode* root;
    int columnName; // 0 means ID column
    int size;
};