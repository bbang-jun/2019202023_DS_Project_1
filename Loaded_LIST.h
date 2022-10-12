#pragma once
#include <string>
#include <fstream>
using namespace std;

class Loaded_LIST_Node{
    private:
    string number;
    string folder;
    string title;
    Loaded_LIST_Node* next;
    ofstream out;
    
    public:
    Loaded_LIST_Node();
    ~Loaded_LIST_Node(){}
    void setNumber(string number);
    string getNumber();
    void setFolder(string folder);
    string getFolder();
    void setTitle(string title);
    string getTitle();
    void setNext(Loaded_LIST_Node* next);
    Loaded_LIST_Node* getNext();
};

class D2Node{
    private:
    string folder;
    Loaded_LIST_Node* next; // 헤드 노드를 가리킴(가로)
    D2Node * D2Next; // 다음 파일 선행 노드를 가리킴(세로)
    ofstream out;
    
    public:
    D2Node();
    Loaded_LIST_Node* nodeHead;
    Loaded_LIST_Node* nodeTail;
    void setD2Folder(string folder);
    string getD2Folder();
    void setNext(Loaded_LIST_Node* next); // 링링 가르키는 용도
    Loaded_LIST_Node* getNext(); // 링링 가져오는 용도
    void setD2Next(D2Node* New); 
    D2Node* getD2Next();
};

class Loaded_LIST{
    public:
    ofstream out;
    D2Node* folderHead;
    D2Node* folderTail;
    int imgCount=0;
    Loaded_LIST();
    ~Loaded_LIST(){}
    void firstINSERT(string folder, D2Node* node);
    void INSERT(string command, string number, string folder, string title, Loaded_LIST_Node* node);
    void ALLDELETE();
    void DELETE(string folderName, string title, Loaded_LIST_Node* node); // delete
    Loaded_LIST_Node* FIND(string folderName, string title); // 
    Loaded_LIST_Node* returnPrevNode(string folderName, string title);
    D2Node * returnPrevD2Node(string folder);
    void PRINT();
    bool LOADED_LIST_CHECK();
    bool Unique_Number_CHECK(string number);
    bool EXIST(string folder, string title);
};