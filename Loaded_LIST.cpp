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

void D2Node::setTitle(string title) { this->title = title; }
string D2Node::getTitle() { return this->title; }
void D2Node::setD2Next(D2Node *New) { this->D2Next = New; }
D2Node *D2Node::getD2Next() { return this->D2Next; }
void D2Node::setNext(Loaded_LIST_Node *next) { this->next = next; }
Loaded_LIST_Node *D2Node::getNext() { return this->next; }
// void D2Node::setToImg(D2Node* Img){new_files->setToImg(Img);}

Loaded_LIST::Loaded_LIST()
{
    imgHead = NULL;
    newHead = NULL;
    imgTail = NULL;
    newTail = NULL;
    imgPrev = NULL;
    newPrev = NULL;
    imgCount = 0; // 100개 넘겼는지 판단
}

void Loaded_LIST::INSERT(string command, string title, string folder, string number)
{
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
    if (command == "LOAD")
    {

        if (img_files == NULL)
        {
            img_files = new D2Node;
            imgHead = newNode;
            imgTail = imgHead;
            img_files->setNext(imgHead);

            this->imgCount++;
        }
        else
        {
            imgTail->setNext(newNode);
            imgTail = imgTail->getNext();
            this->imgCount++;
        }
    }
    else if (command == "ADD")
    {
        if (new_files == NULL)
        {
            new_files = new D2Node;
            newHead = newNode;
            newTail = newHead;
            img_files->setD2Next(new_files);
            new_files->setNext(newHead);

            this->imgCount++;
        }
        else
        {
            newTail->setNext(newNode);
            newTail = newTail->getNext();
            this->imgCount++;
        }
    }
}

void Loaded_LIST::DELETE(string folderName, string title, string number)
{
    Loaded_LIST_Node *delNode;
    Loaded_LIST_Node *curNode;
    Loaded_LIST_Node *prevNode;

    curNode = FIND(folderName, title);

    if (folderName == "img_files")
    {
        if (curNode == imgHead)
        {
            delNode = imgHead;
            imgHead = imgHead->getNext();
            delete delNode;
        }
        else
        {
            while (prevNode->getNext() != curNode)
                prevNode = prevNode->getNext();
        }
    }
    else if (folderName == "new_files")
    {
        if (curNode == newHead)
        {
            delNode = newHead;
            newHead = newHead->getNext();
            delete delNode;
        }
    }
}

Loaded_LIST_Node *Loaded_LIST::FIND(string folderName, string title)
{

    Loaded_LIST_Node *curNode = new Loaded_LIST_Node;

    if (folderName == "img_files")
    {
        curNode = imgHead;

        while (curNode->getTitle() != title)
        {
            if (curNode->getTitle() == title)
                return curNode;
        }
    }
    else if (folderName == "new_files")
    {
        curNode = newHead;

        while (curNode->getTitle() != title)
        {
            if (curNode->getTitle() == title)
                return curNode;
        }
    }
}

void Loaded_LIST::PRINT()
{
    Loaded_LIST_Node *curNode = imgHead;

    while (curNode != NULL)
    {
        cout << curNode->getTitle() << "/" << curNode->getNumber() << endl;
        curNode = curNode->getNext();
    }
    // ADD까지 출력

    // curNode = newHead;

    // while (curNode != NULL)
    // {
    //     cout << curNode->getTitle() << "/" << curNode->getNumber() << endl;
    //     curNode = curNode->getNext();
    // }
}

void Loaded_LIST::ADD()
{
}

bool Loaded_LIST::LOADED_LIST_CHECK()
{
    if (imgHead == NULL)
        return true;
    else
        return false;
}