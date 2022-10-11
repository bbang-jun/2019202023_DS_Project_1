using namespace std;
#include <string> // for use string library
#include <iostream>
#include <stack>
#include <vector>
#pragma once

class Queue;
class Stack;
class QNode;

class Database_BST_Node
{
private:
    int number;
    string folder;
    string title;

    Database_BST_Node *leftChild;
    Database_BST_Node *rightChild;
    Database_BST_Node *parent;
    Database_BST_Node *next;

public:
    bool isInsert;

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

    void setNext(Database_BST_Node *next)
    {
        this->next = next;
    }

    Database_BST_Node *getNext()
    {
        return this->next;
    }
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
    void IN_ORDER(Database_BST_Node *curNode);
    Database_BST_Node *PRE_ORDER_SELECT(Database_BST_Node *curNode, int numberBST);
    void PRINT();
    void POST_DELETE(Database_BST_Node *curNode); // 후위순회 순으로 동적할당 해제하는 함수
    void SEARCH_TRAVERSAL(Queue *queue, Database_BST_Node *initial);
    void SEARCH_BOYERMOORE(Queue *q, string title, string word, int lengthOfTitle, int lengthOfWord);
    void numberFind(Database_BST_Node *curNode);
};

class QNode
{
private:
    string title;
    int number;
    QNode *next;
    QNode *prev;

public:
    QNode()
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

class Queue
{
private:
    QNode *front;
    QNode *rear;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
    }
    void setFront(QNode *node) { this->front = node; }
    QNode *getFront() { return this->front; }
    void setRear(QNode *node) { this->rear = node; }
    QNode *getRear() { return this->rear; }
    bool isEmpty()
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

    void push(int number, string title)
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
    void pop()
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

// class SNode
// {
// private:
//     string title;
//     int number;
//     SNode *next;
//     SNode * prev;

// public:
//     SNode()
//     {
//         next = NULL;
//         prev = NULL;
//     }
//     void setTitle(string title)
//     {
//         this->title = title;
//     }
//     string getTitle(){
//         return this->title;
//     }
//     void setNumber(int number){
//         this->number=number;
//     }
//     int getNumber(){
//         return this->number;
//     }
//     void *setNext(SNode *next){
//         this->next=next;
//     }
//     SNode *getNext(){
//         return this->next;
//     }
//     void *setPrev(SNode * prev){
//         this->prev=prev;
//     }
//     SNode * getPrev(){
//         return this->prev;
//     }
// };

class Stack
{
public:
    Database_BST_Node *top;
    Database_BST_Node *bottom;
    Stack()
    {
        this->top = NULL;
        this->bottom = NULL;
    }

    void push(int number, string title)
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
    void pop()
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
    bool isEmpty()
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