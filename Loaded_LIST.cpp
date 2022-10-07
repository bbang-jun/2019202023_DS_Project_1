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
Loaded_LIST_Node::Loaded_LIST_Node(){next=NULL;}

void D2Node::setD2Next(D2Node *New) { this->D2Next = New; }
D2Node *D2Node::getD2Next() { return this->D2Next; }
void D2Node::setfNext(Loaded_LIST_Node *next) { this->next = next; } 
Loaded_LIST_Node *D2Node::getNext() { return this->next; }
void D2Node::setD2Folder(string folder) { this->folder = folder; }
string D2Node::getD2Folder() { return this->folder; }
D2Node::D2Node(){next=NULL; D2Next=NULL;}
 
Loaded_LIST::Loaded_LIST()
{
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
        folderHead->setfNext(NULL);
        folderHead->setD2Next(NULL);
    }
    else
    {
        folderTail->setD2Next(newNode);
        folderTail = folderTail->getD2Next();
    }
}

void Loaded_LIST::INSERT(string number, string folder, string title, Loaded_LIST_Node *node)
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

    if (curD2Node->getNext() == NULL)
    {
        curD2Node->setfNext(newNode);
        curD2Node->nodeHead = newNode;
        curD2Node->nodeTail = newNode;
    }
    else
    {
        Loaded_LIST_Node *curNode = curD2Node->nodeTail;
        //cout<<curNode<<" "<<curD2Node->nodeTail <<endl;
        curNode->setNext(newNode);
        curNode = curNode->getNext();
        curD2Node->nodeTail = curNode;
    }
}

void Loaded_LIST::DELETE(string folder, string title)
{
    Loaded_LIST_Node *curNode;
    D2Node *curD2Node;
    Loaded_LIST_Node *prevNode;

    while (curD2Node->getD2Folder() != folder)
        curD2Node = curD2Node->getD2Next();

    curNode = FIND(folder, title);

    if (curD2Node->nodeHead == curNode)
    {
        curD2Node->nodeHead = curNode->getNext();
        delete curNode;
    }
    else
    {
        prevNode = curD2Node->nodeHead;
        while (prevNode->getNext() != curNode)
            prevNode = prevNode->getNext();
        prevNode->setNext(curNode->getNext());
        delete curNode;
    }
}

Loaded_LIST_Node *Loaded_LIST::FIND(string folder, string title)
{
    Loaded_LIST_Node *curNode;
    D2Node *curD2Node = folderHead;

    while (curD2Node->getD2Folder() != folder)
        curD2Node = curD2Node->getD2Next();

    curNode = curD2Node->nodeHead;

    while (curNode->getTitle() != title)
        curNode = curNode->getNext();

    return curNode;
}

Loaded_LIST_Node *Loaded_LIST::returnPrevNode(string folderName, string title)
{
    // Loaded_LIST_Node *curNode = FIND(folderName, title);
    // Loaded_LIST_Node *prevNode;

    // if (folderName == "img_files")
    // {
    //     prevNode = imgHead;
    //     while (prevNode->getNext() != curNode)
    //         prevNode = prevNode->getNext();
    //     return prevNode;
    // }
    // else if (folderName == "new_files")
    // {
    //     prevNode = newHead;
    //     while (prevNode->getNext() != curNode)
    //         prevNode = prevNode->getNext();
    //     return prevNode;
    // }
}

void Loaded_LIST::PRINT()
{
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *curNode=folderHead->nodeTail;

    while (curD2Node != NULL)
    {
        curNode = curD2Node->nodeHead;
        while (curNode != NULL)
        {
            cout << curNode->getTitle() << "/" << curNode->getNumber() << endl;
            curNode=curNode->getNext();
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