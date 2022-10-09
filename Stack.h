using namespace std;
#include <string>

class Node {
private:
   string title;
   int number;
   Node* next;
   

public:
   Node();
   void setTitle(string title);
   string getTitle();
   void setNumber(int number);
   int getNumber();
   void* setNext(Node* next);
   Node* getNext();
};

class Stack {
public:
   Node* top;
   Node* bottom;
   Stack();
   bool isEmpty();
   void push(int number, string title);
   void pop();
   //void printStack();
};