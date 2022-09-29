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
void D2Node::setToNew(D2Node *New) { img_files->setToNew(New); }
void D2Node::setNext(Loaded_LIST_Node* next){this->next=next;}
Loaded_LIST_Node* D2Node::getNext(){return this->next;}
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
    img_files = new D2Node;
    new_files = new D2Node;
}

void Loaded_LIST::INSERT(string command, string title, string folder, string number)
{
    Loaded_LIST_Node *newNode = new Loaded_LIST_Node;
    newNode->setNumber(number);
    newNode->setFolder(folder);
    newNode->setTitle(title);
    newNode->setNext(NULL);

    if (command == "LOAD")
    {
        if (img_files->getNext() == NULL)
        {
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
        if (new_files->getNext() == NULL)
        {
            newHead = newNode;
            newTail = newHead;
            img_files->setToNew(new_files);
            new_files->setNext(newHead);
        }
    }
}

void Loaded_LIST::DELETE()
{
}

void Loaded_LIST::FIND()
{
}

void Loaded_LIST::PRINT()
{
    Loaded_LIST_Node *curNode = imgHead;

    while (curNode != NULL)
    {
        cout << curNode->getNumber() << "/" << curNode->getTitle() << endl;
        curNode = curNode->getNext();
    }
}

void Loaded_LIST::ADD()
{
}