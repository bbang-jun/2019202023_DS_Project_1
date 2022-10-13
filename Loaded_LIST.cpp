#include "Loaded_LIST.h"
#include <iostream>
using namespace std;

// Loaded_LIST_Node definition
void Loaded_LIST_Node::setNumber(string number) { this->number = number; }
string Loaded_LIST_Node::getNumber() { return this->number; }
void Loaded_LIST_Node::setFolder(string folder) { this->folder = folder; }
string Loaded_LIST_Node::getFolder() { return this->folder; }
void Loaded_LIST_Node::setTitle(string title) { this->title = title; }
string Loaded_LIST_Node::getTitle() { return this->title; }
void Loaded_LIST_Node::setNext(Loaded_LIST_Node *next) { this->next = next; }
Loaded_LIST_Node *Loaded_LIST_Node::getNext() { return this->next; }
Loaded_LIST_Node::Loaded_LIST_Node() // constructor
{
    next = NULL;
    out.open("log.txt", ios::app);
}

// D2Node definition
void D2Node::setD2Next(D2Node *New) { this->D2Next = New; }
D2Node *D2Node::getD2Next() { return this->D2Next; }
void D2Node::setNext(Loaded_LIST_Node *next) { this->next = next; }
Loaded_LIST_Node *D2Node::getNext() { return this->next; }
void D2Node::setD2Folder(string folder) { this->folder = folder; }
string D2Node::getD2Folder() { return this->folder; }
D2Node::D2Node() // constructor
{
    out.open("log.txt", ios::app);
    nodeHead = NULL;
    nodeTail = NULL;
    next = NULL;
    D2Next = NULL;
}

Loaded_LIST::Loaded_LIST() // constructor
{
    out.open("log.txt", ios::app);
    folderHead = NULL;
    folderTail = NULL;
    imgCount = 0; // 100개 넘겼는지 판단
}

void Loaded_LIST::firstINSERT(string folder, D2Node *node) // insert folder name node
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
    else // connect last connected node with new insert node
    {
        folderTail->setD2Next(newNode);
        folderTail = folderTail->getD2Next();
    }
}

void Loaded_LIST::INSERT(string command, string number, string folder, string title, Loaded_LIST_Node *node)
{// INSERT each information node from read .CSV file
    if (imgCount == 100) // if Loaded_LIST structure has over 100 nodes, DELETE a first inserted node
    {
        DELETE(folderHead->getNext()->getFolder(), folderHead->getNext()->getTitle(), NULL);
        imgCount--; // reduction Loaded_LIST's node count
    }
    Loaded_LIST_Node *newNode = new Loaded_LIST_Node; // setting newNode
    newNode->setNumber(number);
    newNode->setFolder(folder);
    newNode->setTitle(title);
    newNode->setNext(NULL);
    D2Node *curD2Node = folderHead; 
    while (curD2Node->getD2Folder() != folder) // find insert location from 2D node
        curD2Node = curD2Node->getD2Next();

    if (command == "MODIFY") // if command is MODIFY, insert the node to memorizing location
    {                     // node = prevNode EXIST(node->getFolder(), node->getTitle()) == true
        if (node == NULL) // modify head node
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

        // modify middle node(except head, tail)
        Loaded_LIST_Node *tempNode = node->getNext();
        node->setNext(newNode);
        node->getNext()->setNext(tempNode);

        return; // return to fuction
    }

    if (curD2Node->getNext() == NULL) // insert head node
    {
        curD2Node->setNext(newNode);
        curD2Node->nodeHead = newNode;
        curD2Node->nodeTail = newNode;
    }
    else // insert other node
    {
        Loaded_LIST_Node *curNode = curD2Node->nodeTail;
        curNode->setNext(newNode);
        curNode = curNode->getNext();
        curD2Node->nodeTail = curNode;
    }
}

void Loaded_LIST::DELETE(string folder, string title, Loaded_LIST_Node *node)
{ // delete specific node
    Loaded_LIST_Node *delNode;
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *prevNode = node;

    while (curD2Node->getD2Folder() != folder) // find delete node location
        curD2Node = curD2Node->getD2Next();

    delNode = FIND(folder, title); // find delete node

    
    if (curD2Node->nodeHead == delNode) // delete head node
    {
        curD2Node->nodeHead = curD2Node->nodeHead->getNext();
        curD2Node->setNext(curD2Node->nodeHead);
        delete delNode;
        delete curD2Node; // delete foldername node, because any node is not exist
    }
    else if (curD2Node->nodeTail == delNode)
    { // delete tail node
        curD2Node->nodeTail = node;
        delete delNode; 
    }
    else
    { // delete middle node(except head node, tail node)
        prevNode->setNext(delNode->getNext());

        delete delNode; 
    }
}

void Loaded_LIST::ALLDELETE() // delete all node in Loaded_LIST structure
{
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *curNode;
    Loaded_LIST_Node *delNode;

    while (curD2Node->getD2Next() != NULL) // curD2Node before folderTail node
    {
        curNode = curD2Node->getNext();

        while (curNode->getNext() != NULL) // curNode before imgTail node
        {
            delNode = curNode;
            curNode = curNode->getNext();
            delete delNode;
            if (curNode->getNext() == NULL)
                delete curNode; // delete node
        }

        if (curD2Node->getD2Next() == NULL) // last condition to delete node(finding foldernode)
        {
            curNode = curD2Node->getNext();

            while (curNode->getNext() != NULL) // last condition to delete node(finding node that inserted in foldernode)
            {
                delNode = curNode;
                curNode = curNode->getNext();
                delete delNode;
                if (curNode->getNext() == NULL)
                    delete curNode; // delete node
            }
        }
        curD2Node=curD2Node->getD2Next();
    }
 
    // The work in below, is delete folderName node. In current situation, only folderName nodes are exist
    D2Node*delD2Node;

    curD2Node=folderHead;

    while(curD2Node->getD2Next()!=NULL){ // delete folderName node

        delD2Node=curD2Node;
        curD2Node=curD2Node->getD2Next();
        delete delD2Node;
        if(curD2Node->getD2Next()==NULL){
            delete curD2Node;
        }
    }
    folderHead=NULL;
    folderTail=NULL;
}

Loaded_LIST_Node *Loaded_LIST::FIND(string folder, string title) // find specific node for delete function
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

bool Loaded_LIST::EXIST(string folder, string title) // if specific node is already exist, return false
{
    D2Node *curD2Node = folderHead;
    while (curD2Node != NULL) // move folderName node
    {
        if (curD2Node->getD2Folder() == folder)
        {
            Loaded_LIST_Node *findNode = curD2Node->getNext();
            while (findNode != NULL) // move node ins folerName node
            {
                if (findNode->getFolder() == folder && findNode->getTitle() == title)
                {
                    return false; // finding specific node and return false
                }
                findNode = findNode->getNext();
            }
        }
        curD2Node = curD2Node->getD2Next();
    }

    return true; // if specific node is not exist, return true
}

Loaded_LIST_Node *Loaded_LIST::returnPrevNode(string folder, string title) // return previous node for delete
{
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *curNode = FIND(folder, title); // finding to delete node

    while (curD2Node->getD2Folder() != folder) // finding folderName node
    {
        curD2Node = curD2Node->getD2Next();
    }

    if (curNode == curD2Node->getNext()) // if finding node is same with head node, return null
        return NULL;

    Loaded_LIST_Node *prevNode = curD2Node->nodeHead; // initialize

    while (prevNode->getNext() != curNode) // finding previous node
    {
        prevNode = prevNode->getNext();
    }

    return prevNode;
}

D2Node *Loaded_LIST::returnPrevD2Node(string folder) // return previous folderName node
{
    D2Node *curD2Node = folderHead;

    if (curD2Node->getD2Folder() == folder) // if folderName node is folderHead, it doesn't have previous node
        return NULL;
    else
    {
        while (curD2Node->getD2Next()->getD2Folder() != folder) // finding previous folder node
        {
            curD2Node = curD2Node->getD2Next();
        }
        return curD2Node;
    }
}

void Loaded_LIST::PRINT()
{
    if (folderHead == NULL) // if Loaded_LIST structure doesn't have any node, return
    {
        return;
    }
    D2Node *curD2Node = folderHead;
    Loaded_LIST_Node *curNode = folderHead->nodeTail;

    while (curD2Node->getD2Next() != NULL) // move folderName node for print
    {
        curNode = curD2Node->nodeHead;
        while (curNode->getNext() != NULL) // move node in folderName, for print
        {
            out << curNode->getTitle() << "/" << curNode->getNumber() << endl; // print Loaded_LIST's node
            curNode = curNode->getNext();
        }
        out << curNode->getTitle() << "/" << curNode->getNumber() << endl; // print Loaded_LIST's node
        curD2Node = curD2Node->getD2Next();
    }

    curNode = curD2Node->nodeHead;
    while (curNode->getNext() != NULL)
    {
        out << curNode->getTitle() << "/" << curNode->getNumber() << endl; // print Loaded_LIST's node
        curNode = curNode->getNext();
    }
    out << curNode->getTitle() << "/" << curNode->getNumber() << endl; // print Loaded_LIST's node
}

bool Loaded_LIST::LOADED_LIST_CHECK() // checking Loaded_LIST structure has any node
{
    if (folderHead == NULL)
        return true;
    else
        return false;
}

bool Loaded_LIST::Unique_Number_CHECK(string number) // checking specific unique number is exist
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