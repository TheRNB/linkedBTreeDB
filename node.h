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
    BTNode(int cID, BTNode* par);
    void addNodeByIndex(Node* newNode, int posID = 0); // SOLELY IN THIS BTNode
    int addNode(Node* newNode);
    void delNode(int posID = 0); // SOLELY IN THIS BTNode
    void setChild(BTNode* child, int posID = 0);
    void setParent(BTNode* newParent);
    void BTNode::setParentIndex(int newIndex);
    int size();
    int index();
    Node* getKey(int posID = 0);
    BTNode* getChild(int posIS = 0);
    BTNode* getParent();
private:
    Node* keys[CHILD_MAX + 2];
    BTNode* children[CHILD_MAX + 2];
    int parentIndex; //index of the this node among its parent
    BTNode* parent;
    int sizee;
    int columnName;
};
