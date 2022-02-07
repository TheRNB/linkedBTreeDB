const int CHILD_MIN = 3;
const int CHILD_MAX = 7;

class BTNode;

class Node{
public:
    long long data;
    Node* nextField;
    BTNode* self;
};

class BTNode {
public:
    BTNode(int, BTNode*); //int cID, BTNode* par
    void addNodeByIndex(Node*, int); // SOLELY IN THIS BTNode
    int addNode(Node*);
    void delNode(int); // SOLELY IN THIS BTNode
    void setChild(BTNode*, int);
    void setParent(BTNode*);
    void setKey(Node*, int);
    //void BTNode::setParentIndex(int);
    int size();
    int index();
    Node* getKey(int);
    BTNode* getChild(int);
    BTNode* getParent();
private:
    Node* keys[CHILD_MAX + 2];
    BTNode* children[CHILD_MAX + 2];
    //int parentIndex; //index of the this node among its parent
    BTNode* parent;
    int sizee;
    int columnName;
};
