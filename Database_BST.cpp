#include "Database_BST.h"
#include <iostream>
using namespace std;

Database_BST_Node::Database_BST_Node() // consturctor of Database_BST_Node
{
    number = 0;
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
}

void Database_BST_Node::setNumber(int number) { this->number = number; }
int Database_BST_Node::getNumber() { return this->number; }

void Database_BST_Node::setFolder(string folder) { this->folder = folder; }
string Database_BST_Node::getFolder() { return this->folder; }

void Database_BST_Node::setTitle(string title) { this->title = title; }
string Database_BST_Node::getTitle() { return this->title; }

void Database_BST_Node::setParent(Database_BST_Node *nextNode) { this->parent = nextNode; }
Database_BST_Node *Database_BST_Node::getParent() { return this->parent; }

void Database_BST_Node::setLeftChild(Database_BST_Node *leftChild) { this->leftChild = leftChild; }
Database_BST_Node *Database_BST_Node::getLeftChild() { return this->leftChild; }

void Database_BST_Node::setRightChild(Database_BST_Node *rightChild) { this->rightChild = rightChild; }
Database_BST_Node *Database_BST_Node::getRightChild() { return this->rightChild; }

Database_BST::Database_BST()
{ // constructor of Database_BST
    root = NULL;
    parent = NULL;
}

Database_BST::~Database_BST()
{               // destructor of Database_BST
    POST_DELETE(root); // 후위순회 순으로 동적할당 해제하는 함수
}

Database_BST_Node *Database_BST::getRoot() { return this->root; }

void Database_BST::INSERT(string command, int number, string folder, string title, Database_BST_Node *curNode)
{
    if (root == NULL)
    { // 루트 노드가 없는 경우
        Database_BST_Node *newNode = new Database_BST_Node;
        newNode->setNumber(number);   // newNode의 value는 intger
        newNode->setFolder(folder);
        newNode->setTitle(title);
        newNode->setLeftChild(NULL);  // newNode의 왼쪽 자식 NULL 초기화
        newNode->setRightChild(NULL); // newNode의 오른쪽 자식 NULL 초기화
        root = newNode;               // root 노드와 현재 노드를 newNode로 초기화
        curNode = root;
    }
    else if (curNode->getNumber() > number)
    { // 현재 노드에 저장된 값이 입력 받은 값보다 큰 경우(입력 받은 값이 작으므로 왼쪽에 삽입)
        if (curNode->getLeftChild() == NULL)
        {
            Database_BST_Node *newNode = new Database_BST_Node;
        newNode->setNumber(number);   // newNode의 value는 intger
        newNode->setFolder(folder);
        newNode->setTitle(title);
            newNode->setLeftChild(NULL);
            newNode->setRightChild(NULL);
            curNode->setLeftChild(newNode);
        }
        else
        { // 왼쪽 자식이 있을 경우 INSERT 함수를 다시 실행함으로써 현재 노드의 위치를 왼쪽 자식으로 이동
            if (curNode->getLeftChild()->getNumber() == number)
                return;
            INSERT(command, number, folder, title, curNode->getLeftChild());
        }
    }
    else if (curNode->getNumber() < number)
    { // 현재 노드에 저장된 값보다 입력 받은 값이 큰 경우(입력 받은 값이 크므로 오른쪽에 삽입)
        if (curNode->getRightChild() == NULL)
        {
            Database_BST_Node *newNode = new Database_BST_Node;
        newNode->setNumber(number);   // newNode의 value는 intger
        newNode->setFolder(folder);
        newNode->setTitle(title);
            newNode->setLeftChild(NULL);
            newNode->setRightChild(NULL);
            curNode->setRightChild(newNode);
        }
        else
        { // 오른쪽 자식이 있을 경우 INSERT 함수를 다시 실행함으로써 현재 노드의 위치를 오른쪽 자식으로 이동
            if (curNode->getRightChild()->getNumber() == number)
                return;
            INSERT(command, number, folder, title, curNode->getRightChild());
        }
    }
}

void Database_BST::DELETES(int number)
{
    Database_BST_Node *curNode = root;
    Database_BST_Node *delNode = NULL;
    Database_BST_Node *tempNode = NULL;
    while (1)
    { // while문이 끝났을 때 curNode의 값은 integer와 같다.
        if (curNode->getLeftChild() == NULL || curNode->getRightChild() == NULL)
            return;
        if (curNode->getNumber() < number)
        {
            parent = curNode;
            curNode = curNode->getRightChild();
        }
        else if (curNode->getNumber() > number)
        {
            parent = curNode;
            curNode = curNode->getLeftChild();
        }
        else
        {
            break;
        }
    }

    // leaf node가 삭제될 경우
    if (curNode->getLeftChild() == NULL && curNode->getRightChild() == NULL)
    {
        if (root->getLeftChild() == NULL && root->getRightChild() == NULL)
        {
            delete root;
            root = NULL;
            return;
        }
        delete curNode;
        curNode = NULL;
        return;
    }
    // child가 1개인 node가 삭제될 경우
    else if (curNode->getLeftChild() == NULL || curNode->getRightChild() == NULL)
    {
        if (curNode == root)
        {
            if (root->getLeftChild() != NULL)
            {
                tempNode = root->getLeftChild();
                delete root;
                root = tempNode;
                return;
            }
            else if (root->getRightChild() != NULL)
            {
                tempNode = root->getRightChild();
                delete root;
                root = tempNode;
                return;
            }
        }

        delNode = curNode;
        if (parent->getLeftChild() == curNode)
        {
            if (curNode->getLeftChild() != NULL)
            {
                parent->setLeftChild(curNode->getLeftChild());
                delete delNode;
                delNode = NULL;
                return;
            }
            else if (curNode->getRightChild() != NULL)
            {
                parent->setRightChild(curNode->getRightChild());
                delete delNode;
                delNode = NULL;
                return;
            }
        }
        else if (parent->getRightChild() == curNode)
        {
            if (curNode->getLeftChild() != NULL)
            {
                parent->setLeftChild(curNode->getLeftChild());
                delete delNode;
                delNode = NULL;
                return;
            }
            else if (curNode->getRightChild() != NULL)
            {
                parent->setRightChild(curNode->getRightChild());
                delete delNode;
                delNode = NULL;
                return;
            }
        }
    }
    // child가 2개인 node가 삭제될 경우
    else if (curNode->getLeftChild() != NULL && curNode->getRightChild() != NULL)
    {
        Database_BST_Node *tempParent = curNode;
        Database_BST_Node *rightSmall = curNode->getRightChild();
        int temp = 0;
        while (rightSmall->getLeftChild() != NULL)
        {
            tempParent = rightSmall;
            rightSmall = rightSmall->getLeftChild();
        }
        if (tempParent->getLeftChild() == rightSmall)
            tempParent->setLeftChild(rightSmall->getRightChild());
        else
            tempParent->setRightChild(rightSmall->getRightChild());

        curNode->setNumber(rightSmall->getNumber());
        curNode = rightSmall;
        // temp = rightSmall->getData();
        // rightSmall->setData(curNode->getData());
        // curNode->setData(temp);
        // DELETES(rightSmall->getData());
        // delete rightSmall;
        // rightSmall = NULL;
        delete curNode;
        curNode = NULL;
    }
}

void Database_BST::IN_ORDER(Database_BST_Node *curNode)
{
    if (curNode != NULL)
    {
        IN_ORDER(curNode->getLeftChild());
        cout << curNode->getFolder() << " / \"" << curNode->getTitle() << "\" / " << curNode->getNumber() << endl;
        IN_ORDER(curNode->getRightChild());
    }
}

Database_BST_Node* Database_BST::PRE_ORDER_SELECT(Database_BST_Node * curNode, int numberBST){

    if (curNode != NULL) {
        if(curNode->getNumber()==numberBST)
            return curNode;
        //PRE_ORDER_SELECT(curNode->getLeftChild());
       // PRE_ORDER_SELECT(curNode->getRightChild());
    }
}

void Database_BST::PRINT()
{
    IN_ORDER(root);
}

void Database_BST::POST_DELETE(Database_BST_Node *curNode)
{

    if (curNode == nullptr)
        return;

    POST_DELETE(curNode->getLeftChild());
    POST_DELETE(curNode->getRightChild());

    if (nullptr != curNode)
    {
        delete curNode;
        curNode = nullptr;
    }
}

void Database_BST::Iterative_POST_ORDER(Database_BST_Node* root){

}