#pragma once
using namespace std;
#include <string> 
#include <iostream>
#include <stack>
#include <fstream>

class Queue;
class Stack;
class QNode;

class Database_BST_Node // Database_BST_Node class for satisfied assignment specification
{
private:
    ofstream out;
    int number;
    string folder;
    string title;

    Database_BST_Node *leftChild;
    Database_BST_Node *rightChild;
    Database_BST_Node *parent;
    Database_BST_Node *next;

public:
    bool isInsert; // for use iterative post-order

    Database_BST_Node(); // constructor
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

    void setNext(Database_BST_Node *next)
    {
        this->next = next;
    }

    Database_BST_Node *getNext()
    {
        return this->next;
    }
};

class Database_BST // Database_BST class for satisfied assignment specification
{
private:
    Database_BST_Node *root;
    Database_BST_Node *parent;
    ofstream out;
public:
    int counting; // for counting 300
    Database_BST(); // constructor
    ~Database_BST(); // destructor
    Database_BST_Node *getRoot();
    
    void INSERT(string command, int number, string folder, string title, Database_BST_Node *curNode);
    void IN_ORDER(Database_BST_Node *curNode);
    stack<Database_BST_Node *> bufferStack;
    Database_BST_Node *PRE_ORDER_SELECT(Database_BST_Node *curNode, int numberBST);
    void POST_DELETE(Database_BST_Node *curNode); // post order memory deallocate
    void SEARCH_TRAVERSAL(Queue *queue, Database_BST_Node *initial); // iterative post order
    void SEARCH_BOYERMOORE(Queue *q, string title, string word, int lengthOfTitle, int lengthOfWord); // find word using boyer-moore algorithm
    bool SELECT_EXIST(Database_BST_Node *curNode, int number);
};

class Stack // Stack class
{
public:
    Database_BST_Node *top;
    Database_BST_Node *bottom;
    Stack() // constructor
    {
        this->top = NULL;
        this->bottom = NULL;
    }

    void push(int number, string title) // information save to stack
    {
        Database_BST_Node *newNode = new Database_BST_Node;
        newNode->setNumber(number);
        newNode->setTitle(title);

        if (top == NULL)
        {
            top = newNode;
            bottom = newNode;
        }
        else
        {
            top->setNext(newNode);
            top = top->getNext();
        }
    }
    void pop() // remove the top from stack
    {
        if (top == bottom)
        {
            top=NULL;
            bottom=NULL;
            return;
        }
        else if(bottom == NULL){
            return;
        }
        else
        {
            Database_BST_Node *temp = bottom;
            while (temp->getNext() != top && temp->getNext()!=NULL)
            {
                temp = temp->getNext();
            }

            delete top;
            temp->setNext(NULL);
            top = temp;
            return;
        }
    }
    bool isEmpty() // judge stack is empty
    {
        if (bottom == NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

class QNode // Queue's node class
{
private:
    string title;
    int number;
    QNode *next;
    QNode *prev;

public:
    QNode() // constructor
    {
        number = 0;
        next = NULL;
        prev = NULL;
    }
    void setTitle(string title) { this->title = title; }
    string getTitle() { return this->title; }
    void setNumber(int number) { this->number = number; }
    int getNumber() { return this->number; };
    void setNext(QNode *node) { this->next = node; }
    QNode *getNext() { return this->next; };
    void setPrev(QNode *node) { this->prev = node; }
    QNode *getPrev() { return this->prev; };
};

class Queue // Queue class
{
private:
    QNode *front; 
    QNode *rear;

public:
    Queue() // constructor
    {
        front = NULL;
        rear = NULL;
    }
    void setFront(QNode *node) { this->front = node; }
    QNode *getFront() { return this->front; }
    void setRear(QNode *node) { this->rear = node; }
    QNode *getRear() { return this->rear; }
    bool isEmpty() // judge queue is empty
    {
        if (front == NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void push(int number, string title) // push the information to queue
    {
        QNode *newNode = new QNode;
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
    void pop() // remove the front from the queue
    {
        if (front == rear)
        {
            delete front;
            front = NULL;
            rear = NULL;
            return;
        }
        else
        {
            QNode *delNode;
            delNode = front;
            front = front->getNext();
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