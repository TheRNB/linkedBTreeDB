#include "node.h"
#include <cstddef>
#include <vector>
#include <queue>

enum Comparisson {SMALLER=0, EQUAL, BIGGER};

class BTree {
public:
    BTree (long long cName);
    std::vector<Node*> search(long long, Comparisson); //int queryValue, Comparisson queryType
    Node* insert(long long); //int queryValue
    void deleteNode(Node*, BTNode*);
    int size();
    long long getName();
private:
    BTNode* root;
    long long columnName; // 0 means ID column
    int sizee;
    Node* add(long long, BTNode*, BTNode*); //int queryValue, BTNode* curr
    void deleteSingleNode(Node*, BTNode*); //Node* queryValue, BTNode* curr
};
