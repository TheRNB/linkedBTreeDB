#include "node.h"
#include <cstddef>
#include <vector>
#include <queue>

enum Comparisson {SMALLER=0, EQUAL, BIGGER};

class BTree {
public:
    BTree (std::string cName);
    std::vector<Node*> search(long long, Comparisson); //int queryValue, Comparisson queryType
    Node* insert(long long); //int queryValue
    void deleteNode(Node*, BTNode*);
    int size();
    std::string getName();
private:
    BTNode* root;
    std::string columnName; // 0 means ID column
    int sizee;
    Node* add(long long, BTNode*, BTNode*); //int queryValue, BTNode* curr
    void deleteSingleNode(Node*, BTNode*); //Node* queryValue, BTNode* curr
};
