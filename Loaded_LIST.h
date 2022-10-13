#pragma once
#include <string>
#include <fstream>
using namespace std;

class Loaded_LIST_Node
{ // Loaded_LIST_Node class for Loaded_LIST class
private:
    string number;
    string folder;
    string title;
    Loaded_LIST_Node *next;
    ofstream out;

public:
    Loaded_LIST_Node();
    ~Loaded_LIST_Node() {}
    void setNumber(string number);
    string getNumber();
    void setFolder(string folder);
    string getFolder();
    void setTitle(string title);
    string getTitle();
    void setNext(Loaded_LIST_Node *next);
    Loaded_LIST_Node *getNext();
};

class D2Node
{ // D2Node class, it is folderName node
private:
    string folder;
    Loaded_LIST_Node *next; 
    D2Node *D2Next;        
    ofstream out;

public:
    D2Node(); // constructor
    Loaded_LIST_Node *nodeHead;
    Loaded_LIST_Node *nodeTail;
    void setD2Folder(string folder);
    string getD2Folder();
    void setNext(Loaded_LIST_Node *next);
    Loaded_LIST_Node *getNext();          
    void setD2Next(D2Node *New);
    D2Node *getD2Next();
};

class Loaded_LIST
{ // Loaded_LIST class is management structure class..
public:
    ofstream out;
    D2Node *folderHead;
    D2Node *folderTail;
    int imgCount = 0;
    Loaded_LIST(); // constructor
    ~Loaded_LIST() {} // desctuctor
    void firstINSERT(string folder, D2Node *node);
    void INSERT(string command, string number, string folder, string title, Loaded_LIST_Node *node);
    void ALLDELETE();
    void DELETE(string folderName, string title, Loaded_LIST_Node *node); 
    Loaded_LIST_Node *FIND(string folderName, string title);              
    Loaded_LIST_Node *returnPrevNode(string folderName, string title);
    D2Node *returnPrevD2Node(string folder);
    void PRINT();
    bool LOADED_LIST_CHECK();
    bool Unique_Number_CHECK(string number);
    bool EXIST(string folder, string title); // 보류
};