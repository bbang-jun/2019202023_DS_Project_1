#include "Stack.h"
#include <iostream>
using namespace std;

Node::Node(){
    next=NULL;
}

void Node::setTitle(string title){this->title=title;}
string Node::getTitle(){return this->title;}
void Node::setNumber(int number){this->number=number;}
int Node::getNumber(){return this->number;}
void* Node::setNext(Node* next){this->next=next;}
Node* Node::getNext(){return this->next;}


Stack::Stack() {
      this->top = NULL;
      this->bottom = NULL;
}


// void Stack::printStack() {
//    Node * curNode = bottom;

//    while (curNode != NULL) {
//       cout << curNode->getValue() << endl;
//       curNode = curNode->getNextAlpha();
//    }
//    cout << endl;
// }

void Stack::push(int number, string title) {
   Node* newNode = new Node;
   newNode->setNumber(number);
   newNode->setTitle(title);

   if (isEmpty()) {
      top = bottom = newNode;
   }
   else {
      top->setNext(newNode);
   }
}

void Stack::pop() {
   if (top == NULL) {
      cout << "stack underflow" << endl;
   }
   else {
      Node* newNode = top;
      top = top->getNext();
      delete newNode;
   }
}


bool Stack::isEmpty() {
   if (top==NULL)
      return true;
   else
      return false;
}