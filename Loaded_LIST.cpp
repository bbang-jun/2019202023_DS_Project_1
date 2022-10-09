#include "Loaded_LIST.h"
#include <iostream>
using namespace std;

void Loaded_LIST_Node::setNumber(string number) { this->number = number; }
string Loaded_LIST_Node::getNumber() { return this->number; }
void Loaded_LIST_Node::setFolder(string folder) { this->folder = folder; }
string Loaded_LIST_Node::getFolder() { return this->folder; }
void Loaded_LIST_Node::setTitle(string title) { this->title = title; }
string Loaded_LIST_Node::getTitle() { return this->title; }
void Loaded_LIST_Node::setNext(Loaded_LIST_Node *next) { this->next = next; }
Loaded_LIST_Node *Loaded_LIST_Node::getNext() { return this->next; }
Loaded_LIST_Node::Loaded_LIST_Node() { next = NULL; }

void D2Node::setD2Next(D2Node *New) { this->D2Next = New; }
D2Node *D2Node::getD2Next() { return this->D2Next; }
void D2Node::setNext(Loaded_LIST_Node *next) { this->next = next; }
Loaded_LIST_Node *D2Node::getNext() { return this->next; }
void D2Node::setD2Folder(string folder) { this->folder = folder; }
string D2Node::getD2Folder() { return this->folder; }
D2Node::D2Node()
{
    nodeHead = NULL;
    nodeTail = NULL;
    next = NULL;
    D2Next = NULL;
}

Loaded_LIST::Loaded_LIST()
{
    folderHead = NULL;
    folderTail = NULL;
    imgCount = 0; // 100개 넘겼는지 판단
}

void Loaded_LIST::firstINSERT(string folder, D2Node *node)
{
    D2Node *newNode = new D2Node;
    newNode->setD2Next(NULL);
    newNode->setD2Folder(folder);

    if (folderHead == NULL)
    {
        folderHead = newNode;
        folderTail = newNode;
        folderHead->setNext(NULL);
        folderHead->setD2Next(NULL);
    }
    else
    {
        folderTail->setD2Next(newNode);
        folderTail = folderTail->getD2Next();
    }
}

void Loaded_LIST::INSERT(string command, string number, string folder, string title, Loaded_LIST_Node *node)
{

    // if (node != NULL)
    // {
    //     // find하고 넣기
    //     return;
    // }
    if (this->imgCount == 100)
    {
        // todo:implementation
        //  delete
    }
    Loaded_LIST_Node *newNode = new Loaded_LIST_Node;
    newNode->setNumber(number);
    newNode->setFolder(folder);
    newNode->setTitle(title);
    newNode->setNext(NULL);
    D2Node *curD2Node = folderHead;
    while (curD2Node->getD2Folder() != folder)
        curD2Node = curD2Node->getD2Next();

    if (command == "MODIFY")
    {                                                           // node = prevNode EXIST(node->getFolder(), node->getTitle()) == true
        if (node==NULL) // modify head node
        {
            Loaded_LIST_Node *tempNode = curD2Node->nodeHead;
            curD2Node->setNext(newNode);
            curD2Node->nodeHead = curD2Node->getNext();
            curD2Node->nodeHead->setNext(tempNode);
            return;
        }
        if (node == curD2Node->nodeTail)
        { // modify tail node
            curD2Node->nodeTail->setNext(newNode);
            curD2Node->nodeTail = curD2Node->nodeTail->getNext();
            return;
        }

        // modify middle node
        Loaded_LIST_Node *tempNode = node->getNext();
        node->setNext(newNode);
        node->getNext()->setNext(tempNode);

        return;
    }

    if (curD2Node->getNext() == NULL)
    {
        curD2Node->setNext(newNode);
        curD2Node->nodeHead = newNode;
        curD2Node->nodeTail = newNode;
    }
    else
    {
        Loaded_LIST_Node *curNode = curD2Node->nodeTail;
        curNode->setNext(newNode);
        curNode = curNode->getNext();
        curD2Node->nodeTail = curNode;
    }
}

void Loaded_LIST::DELETE(string folder, string title, Loaded_LIST_Node *node)
{
    Loaded_LIST_Node *delNode;
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *prevNode = node;

    while (curD2Node->getD2Folder() != folder)
        curD2Node = curD2Node->getD2Next();

    delNode = FIND(folder, title);

    // head 삭제
    if (curD2Node->nodeHead == delNode)
    {
        curD2Node->nodeHead = curD2Node->nodeHead->getNext();
        curD2Node->setNext(curD2Node->nodeHead);
        delete delNode;
    }
    else if (curD2Node->nodeTail == delNode)
    { // tail 삭제
        curD2Node->nodeTail = node;
        delete delNode;
    }
    else
    { // head와 tail제외 중간 삭제
        prevNode->setNext(delNode->getNext());

        free(delNode);
    }
}

Loaded_LIST_Node *Loaded_LIST::FIND(string folder, string title)
{
    Loaded_LIST_Node *findNode;
    D2Node *curD2Node = folderHead;
    while (curD2Node->getD2Folder() != folder)
        curD2Node = curD2Node->getD2Next();

    findNode = curD2Node->nodeHead;

    while (findNode->getTitle() != title)
        findNode = findNode->getNext();

    return findNode;
}

bool Loaded_LIST::EXIST(string folder, string title)
{
    D2Node *curD2Node = folderHead;
    while (curD2Node != NULL)
    {
        if (curD2Node->getD2Folder() == folder)
        {
            Loaded_LIST_Node *findNode = curD2Node->getNext();
            while (findNode != NULL)
            {
                if (findNode->getFolder() == folder && findNode->getTitle() == title)
                {
                    return false;
                }
                findNode = findNode->getNext();
            }
        }
        curD2Node = curD2Node->getD2Next();
    }

    return true;
}

Loaded_LIST_Node *Loaded_LIST::returnPrevNode(string folder, string title)
{
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *curNode = FIND(folder, title); // 삭제할 노드 찾기

    while (curD2Node->getD2Folder() != folder)
    {
        curD2Node = curD2Node->getD2Next();
    }

    if (curNode == curD2Node->getNext())
        return NULL;

    Loaded_LIST_Node *prevNode = curD2Node->nodeHead;

    while (prevNode->getNext() != curNode)
    {
        prevNode = prevNode->getNext();
    }

    return prevNode;
}

D2Node *Loaded_LIST::returnPrevD2Node(string folder)
{
    D2Node *curD2Node = folderHead;

    if (curD2Node->getD2Folder() == folder)
        return NULL;
    else
    {
        while (curD2Node->getD2Next()->getD2Folder() != folder)
        {
            curD2Node = curD2Node->getD2Next();
        }
        return curD2Node;
    }
}

void Loaded_LIST::PRINT()
{
    if (folderHead == NULL)
    {
        return;
    }
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *curNode = folderHead->nodeTail;

    while (curD2Node != NULL)
    {
        curNode = curD2Node->nodeHead;
        while (curNode != NULL)
        {
            cout << curNode->getTitle() << "/" << curNode->getNumber() << endl;
            curNode = curNode->getNext();
        }
        curD2Node = curD2Node->getD2Next();
    }
}

bool Loaded_LIST::LOADED_LIST_CHECK()
{
    if (folderHead == NULL)
        return true;
    else
        return false;
}

bool Loaded_LIST::Unique_Number_CHECK(string number)
{
    D2Node *curD2Node = folderHead;

    Loaded_LIST_Node *curNode;
    while (curD2Node != NULL)
    {
        curNode = curD2Node->nodeHead;
        while (curNode != NULL)
        {
            if (curNode->getNumber() == number)
                return true; // if exit, true
            curNode = curNode->getNext();
        }
        curD2Node = curD2Node->getD2Next();
    }
    return false; // if not exist, false
}