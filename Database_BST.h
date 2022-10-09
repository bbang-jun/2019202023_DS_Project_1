using namespace std;
#include <string> // for use string library
#include <iostream>
#include <stack>
# define NO_OF_CHARS 256  
// class Database_BST;

class Node
{
private:
    string title;
    int number;
    Node *next;
    Node *prev;

public:
    Node()
    {
        number = 0;
        next = NULL;
        prev = NULL;
    }
    void setTitle(string title) { this->title = title; }
    string getTitle() { return this->title; }
    void setNumber(int number) { this->number = number; }
    int getNumber() { return this->number; };
    void setNext(Node *node) { this->next = node; }
    Node *getNext() { return this->next; };
    void setPrev(Node *node) { this->prev = node; }
    Node *getPrev() { return this->prev; };
};

class Queue
{
private:
    Node *front;
    Node *rear;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
    }
    void setFront(Node *node) { this->front = node; }
    Node *getFront() { return this->front; }
    void setRear(Node *node) { this->rear = node; }
    Node *getRear() { return this->rear; }
    bool isEmpty(){
        if(front==NULL){
            return false;
        }
        else{
            return true;
        }
    }

    void push(int number, string title)
    {
        Node *newNode = new Node;
        newNode->setNumber(number);
        newNode->setTitle(title);

        if (front == NULL)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->setNext(newNode);
            rear = rear->getNext();
        }
    }
    void pop()
    {

            if (front == rear)
            {
                delete front;
                front=NULL;
                rear=NULL;
                return;
            }
            else{
                Node*delNode;
                delNode=front;
                front=front->getNext();
                delete delNode;
                return;
            }
        
    }

    int returnNumber()
    {
        return front->getNumber();
    };

    string returnTitle()
    {
        return front->getTitle();
    }
};

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
    int checkSum;
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
    // Stack* s;
    Database_BST();
    ~Database_BST();
    Database_BST_Node *getRoot();
    void INSERT(string command, int number, string folder, string title, Database_BST_Node *curNode);
    void DELETES(int number);
    void IN_ORDER(Database_BST_Node *curNode);
    void POST_ORDER();
    Database_BST_Node *PRE_ORDER_SELECT(Database_BST_Node *curNode, int numberBST);
    void PRINT();
    void POST_DELETE(Database_BST_Node *curNode); // 후위순회 순으로 동적할당 해제하는 함수
    void Iterative_POST_ORDER(Queue *q);
    void BoyerMoore(Queue* q, string txt, string pat);
    void badChar(string str, int size,  int badchar[NO_OF_CHARS]);
};
