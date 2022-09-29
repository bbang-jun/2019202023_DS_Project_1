#include <string>
using namespace std;

class Loaded_LIST_Node{
    private:
    string number;
    string folder;
    string title;
    Loaded_LIST_Node* next;
    
    public:
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
    string title;
    Loaded_LIST_Node* next;
    D2Node * img_files;
    D2Node * new_files;

    public:
    void setTitle(string title);
    string getTitle();
    void setNext(Loaded_LIST_Node* next); // 링링 가르키는 용도
    Loaded_LIST_Node* getNext(); // 링링 가져오는 용도
    void setToNew(D2Node* New); // img가 new 가리키는 용도
    D2Node* getToNew();
    //void setToImg(D2Node* Img); // new가 img 가리키는 용도
    //D2Node* getToImg();
};

class Loaded_LIST{
    private:
    Loaded_LIST_Node * imgHead;
    Loaded_LIST_Node * newHead;
    Loaded_LIST_Node * imgTail;
    Loaded_LIST_Node * newTail;
    Loaded_LIST_Node * imgPrev;
    Loaded_LIST_Node * newPrev;
    D2Node *img_files;
    D2Node *new_files;


    public:
    int imgCount;
    Loaded_LIST();
    void INSERT(string command, string number, string folder, string title);
    void DELETE(); // delete
    void FIND(); // 
    void PRINT();
    void ADD();
};

