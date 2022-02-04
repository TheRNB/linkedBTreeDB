const int CHILD_MIN = 3;
const int CHILD_MAX = 6;

class Node{
public:
    int data;
    Node* nextField;
    BTNode* self;
};

class BTNode {
public:
    BTNode() {
        parentIndex = -1;
    }
private:
    Node* keys[CHILD_MAX - 1];
    Node* children[CHILD_MAX];
    int parentIndex; //index of the node among its parent
};