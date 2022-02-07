#include "node.h"
#include <cstddef>
#include <vector>
#include <queue>

enum Comparisson {SMALLER=0, EQUAL, BIGGER};

class BTree {
public:
    BTree (int cName);
    std::vector<Node*> search(int, Comparisson); //int queryValue, Comparisson queryType
    Node* insert(int); //int queryValue
    void deleteNode(Node*, BTNode*);
    int size();
    int getName();
private:
    BTNode* root;
    int columnName; // 0 means ID column
    int sizee;
    Node* add(int, BTNode*, BTNode*); //int queryValue, BTNode* curr
    void deleteSingleNode(Node*, BTNode*); //Node* queryValue, BTNode* curr
};
