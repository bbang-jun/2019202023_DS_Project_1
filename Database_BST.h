using namespace std;
#include <string> // for use string library

class Database_BST_Node
{
private:
    int number;
    string folder;
    string title;
    Database_BST_Node *leftChild;
    Database_BST_Node *rightChild;
    Database_BST_Node *parent;

public:
    Database_BST_Node();
    void setNumber(int number);
    int getNumber();

    void setFolder(string folder);
    string getFolder();

    void setTitle(string title);
    string getTitle();

    void setParent(Database_BST_Node *nextNode);
    Database_BST_Node *getParent();

    void setLeftChild(Database_BST_Node *leftChild);
    Database_BST_Node *getLeftChild();

    void setRightChild(Database_BST_Node *rightChild);
    Database_BST_Node *getRightChild();
};

class Database_BST
{
private:
    Database_BST_Node *root;
    Database_BST_Node *parent;

public:
    Database_BST();
    ~Database_BST();
    Database_BST_Node *getRoot();
    void INSERT(string command, int number, string folder, string title, Database_BST_Node *curNode);
    void DELETES(int number);
    void IN_ORDER(Database_BST_Node* curNode);
    void POST_ORDER();
    Database_BST_Node* PRE_ORDER_SELECT(Database_BST_Node* curNode, int numberBST);
    void PRINT();
    void POST_DELETE(Database_BST_Node *curNode); // 후위순회 순으로 동적할당 해제하는 함수
    void Iterative_POST_ORDER(Database_BST_Node* root);
};