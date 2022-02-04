const int CHILD_MIN = 3;
const int CHILD_MAX = 5;

class Node{
public:
    int data;
    Node* nextField;
    BTNode* self;
};

class BTNode {
public:
    BTNode();
    void addNode(Node* newNode, int posID = 0); // SOLELY IN THIS BTNode
    void delNode(int posID = 0); // SOLELY IN THIS BTNode
    int size();
    int index();
private:
    Node* keys[CHILD_MAX + 1];
    Node* children[CHILD_MAX + 1];
    int parentIndex; //index of the this node among its parent
    int sizee;
};
