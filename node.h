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
    BTNode() {
        sizee = 0;
        parentIndex = -1;
        for (int i = 0; i < CHILD_MAX; ++i)
            keys[i] = children[i] = NULL;
    }
    void addNode(Node* newNode, int posID = 0) {
        // ADDS A NODE SOLELY IN BTNode AND NOT THE CHILDREN
        for (int i = CHILD_MAX; i > posID; --i) {
            keys[i] = keys[i-1];
            children[i] = children[i-1];
        }
        return;
    }
    void delNode(int posID = 0) {
        // DELETES A NODE SOLELY IN BTNode AND NOT THE CHILDREN
        for (int i = posID; i <= CHILD_MAX; ++i) {
            keys[i] = keys[i+1];
            children[i] = children[i+1];
        }
        return;
    }
    int size() {
        return sizee;
    }
    int index() {
        return parentIndex;
    }
private:
    Node* keys[CHILD_MAX + 1];
    Node* children[CHILD_MAX + 1];
    int parentIndex; //index of the node among its parent
    int sizee;
};
