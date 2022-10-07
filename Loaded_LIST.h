#include <string>
using namespace std;

class Loaded_LIST_Node{
    private:
    string number;
    string folder;
    string title;
    Loaded_LIST_Node* next;
    
    public:
    Loaded_LIST_Node();
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
    
    public:
    D2Node();
    Loaded_LIST_Node* nodeHead;
    Loaded_LIST_Node* nodeTail;
    void setD2Folder(string folder);
    string getD2Folder();
    void setfNext(Loaded_LIST_Node* next); // 링링 가르키는 용도
    Loaded_LIST_Node* getNext(); // 링링 가져오는 용도
    void setD2Next(D2Node* New); 
    D2Node* getD2Next();
};

class Loaded_LIST{
    public:
    D2Node* folderHead;
    D2Node* folderTail;
    int imgCount=0;
    Loaded_LIST();
    void firstINSERT(string folder, D2Node* node);
    void INSERT(string number, string folder, string title, Loaded_LIST_Node* node);
    void DELETE(string folderName, string title); // delete
    Loaded_LIST_Node* FIND(string folderName, string title); // 
    Loaded_LIST_Node* returnPrevNode(string folderName, string title);
    void PRINT();
    bool LOADED_LIST_CHECK();
};