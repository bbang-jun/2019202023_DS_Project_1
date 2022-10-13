#include "Database_BST.h"

Database_BST_Node::Database_BST_Node() // consturctor of Database_BST_Node
{
    isInsert = false;
    number = 0;
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
    next = NULL;
}

void Database_BST_Node::setNumber(int number) { this->number = number; }
int Database_BST_Node::getNumber() { return this->number; }

void Database_BST_Node::setFolder(string folder) { this->folder = folder; }
string Database_BST_Node::getFolder() { return this->folder; }

void Database_BST_Node::setTitle(string title) { this->title = title; }
string Database_BST_Node::getTitle() { return this->title; }

void Database_BST_Node::setParent(Database_BST_Node *nextNode) { this->parent = nextNode; }
Database_BST_Node *Database_BST_Node::getParent() { return this->parent; }

void Database_BST_Node::setLeftChild(Database_BST_Node *leftChild) { this->leftChild = leftChild; }
Database_BST_Node *Database_BST_Node::getLeftChild() { return this->leftChild; }

void Database_BST_Node::setRightChild(Database_BST_Node *rightChild) { this->rightChild = rightChild; }
Database_BST_Node *Database_BST_Node::getRightChild() { return this->rightChild; }

Database_BST::Database_BST()
{ // constructor of Database_BST
    counting = 0;
    out.open("log.txt", ios::app);
    root = NULL;
    parent = NULL;
}

Database_BST::~Database_BST() // destructor of Database_BST
{
    POST_DELETE(root); // post order way delete
}

Database_BST_Node *Database_BST::getRoot() { return this->root; } // reuturn root

void Database_BST::INSERT(string command, int number, string folder, string title, Database_BST_Node *curNode) // bst insert function
{
    if (this->counting == 300) // if over 300 nodes, delete most small node
    {
        Database_BST_Node *curNode = root;
        Database_BST_Node *delNode;
        if (curNode->getLeftChild() == NULL) // curNode is root
        {
            if (curNode->getRightChild() != NULL)
            {
                root = curNode->getRightChild();
            }
            delete curNode;
        }
        else // curNode is not root
        {
            while (curNode->getLeftChild() != NULL) // find most small node and delete
            {
                if (curNode->getLeftChild()->getLeftChild() != NULL)
                {
                    delNode = curNode->getLeftChild();
                    curNode->setLeftChild(delNode->getRightChild());
                    delete delNode;
                }
                curNode = curNode->getLeftChild();
                if (curNode->getLeftChild() == NULL)
                {
                    delete curNode;
                }
            }
        }
        counting--;
    }
    if (root == NULL) // case: root is NULL
    {                 // setting node
        Database_BST_Node *newNode = new Database_BST_Node;
        newNode->setNumber(number);
        newNode->setFolder(folder);
        newNode->setTitle(title);
        newNode->setLeftChild(NULL);
        newNode->setRightChild(NULL);
        root = newNode;
        counting++;
        return;
    }
    else if (curNode->getNumber() > number) // case: insert left
    {
        if (curNode->getLeftChild() == NULL)
        { // setting node
            Database_BST_Node *newNode = new Database_BST_Node;
            newNode->setNumber(number);
            newNode->setFolder(folder);
            newNode->setTitle(title);
            newNode->setLeftChild(NULL);
            newNode->setRightChild(NULL);
            curNode->setLeftChild(newNode);
            counting++;
            return;
        }
        else
        {
            if (curNode->getLeftChild()->getNumber() == number)
                return;
            INSERT(command, number, folder, title, curNode->getLeftChild()); // if left child is exist, go to leftchild and reinsert
        }
    }
    else if (curNode->getNumber() < number)
    {
        if (curNode->getRightChild() == NULL) // bst is not have same value node
        {
            Database_BST_Node *newNode = new Database_BST_Node;
            newNode->setNumber(number);
            newNode->setFolder(folder);
            newNode->setTitle(title);
            newNode->setLeftChild(NULL);
            newNode->setRightChild(NULL);
            curNode->setRightChild(newNode);
            counting++;
            return;
        }
        else
        {
            if (curNode->getRightChild()->getNumber() == number) // bst is not have same value node
                return;
            INSERT(command, number, folder, title, curNode->getRightChild()); // if right child is exist, go to right and reinsert
        }
    }
}

void Database_BST::IN_ORDER(Database_BST_Node *curNode) // PRINT command's  In-order traversal print
{
    if (curNode != NULL)
    {
        IN_ORDER(curNode->getLeftChild()); // recursive
        out << curNode->getFolder() << " / \"" << curNode->getTitle() << "\" / " << curNode->getNumber() << endl;
        IN_ORDER(curNode->getRightChild()); // recursive
    }
}

Database_BST_Node *Database_BST::PRE_ORDER_SELECT(Database_BST_Node *curNode, int selectNum) // SELECT command's Pre-order traversal, for find image path
{
    if (curNode != NULL)
    {
        if (curNode->getNumber() == selectNum)
            return curNode; // for find image path, it is node
        else if (curNode->getNumber() > selectNum)
            PRE_ORDER_SELECT(curNode->getLeftChild(), selectNum); // recursive
        else if (curNode->getNumber() < selectNum)
            PRE_ORDER_SELECT(curNode->getRightChild(), selectNum); // recursive
    }
}

void Database_BST::POST_DELETE(Database_BST_Node *curNode) // delete memory use post order
{
    if (curNode == nullptr)
        return;

    POST_DELETE(curNode->getLeftChild());  // recursive
    POST_DELETE(curNode->getRightChild()); // recursive

    if (nullptr != curNode)
    {
        delete curNode;
        curNode = nullptr;
    }
}

void Database_BST::SEARCH_TRAVERSAL(Queue *queue, Database_BST_Node *present) // SEARCH command's post-order to use iterative. It have argument queue and present
{
    while (true) // infinite loop
    {
        if (present == NULL) // if present node is NULL, return the function
        {
            return;
        }

        if (present->isInsert == false) // if present node is not push to queue
        {
            bufferStack.push(present); // if node is not insert in stack, push the node in stack
        }
        else if (present->isInsert == true) // judge push to queue
        {
            while (present->isInsert == true) // judge push to queue
            {
                bufferStack.pop();       // pop for make next top
                if (bufferStack.empty()) // if stack is empty
                {
                    return;
                }
                present = bufferStack.top(); // present node is stack's top.(pop function is using assign present to top)
            }
        }

        if ((present->getLeftChild() != NULL && present->getLeftChild()->isInsert == false) || (present->getRightChild() != NULL && present->getRightChild()->isInsert == false))
        {
            if (present->getLeftChild() != NULL && present->getLeftChild()->isInsert == false) // if present node is have left child and not insert to queue
            {
                present = present->getLeftChild(); // change present node

                goto repeat; // ignore push to stack
            }
            else if (present->getRightChild() != NULL && present->getRightChild()->isInsert == false) // if present node is have right child and not insert to queue
            {
                present = present->getRightChild(); // change present node

                goto repeat; // ignore push to stack
            }
        }
        else
        {
            queue->push(present->getNumber(), present->getTitle()); // push to queue. and queue has tree node's title(file name), number
            bufferStack.pop();                                      // insert after q, pop stack's top node
            present->isInsert = true;                               // after push to queue. change isInsert variable to judge next.
        }

        if (bufferStack.empty() == false) // if stack is not empty
        {
            present = bufferStack.top(); // present node is stack's top node
        }
        else if (bufferStack.empty() == true) // if stack is empty
        {
            return; // return the function
        }

    repeat:; // ; is use to prevent syntax error.
    }
}

void Database_BST::SEARCH_BOYERMOORE(Queue *queue, string title, string word, int lengthOfTitle, int lengthOfWord) // SEARCH command's Boyer-Moore algorithm
{
    int count = 0, temp = 0, wordMoveCount = 0;      // count is for array bch's index
    int minusPrint = lengthOfWord - 1;               // minusPrint is word(finding)'s length - 1
    int differLength = lengthOfTitle - lengthOfWord; // differLength is difference between title's length and word's length
    int bch[500];                                    // bad character int array, size is 500

    while (count < 500) // array bch's index<500
    {
        bch[count] = -1; // initialize array bch to -1 value
        count++;         // count=count+1
    }

    for (count = 0; count < lengthOfWord; count++) // counting until lengthOfWord
    {
        temp = word[count]; // temp is for have one letter(convert to integer)
        bch[temp] = count;  // save count value to bch's temp index
    }

    while (!(wordMoveCount > differLength)) // word moving relative for title
    {
        while (!(minusPrint < 0) && word[minusPrint] == title[wordMoveCount + minusPrint]) // while corresponding title and word, postfix decrement for minusPrint variable
            minusPrint--;                                                                  // postfix decrement operate

        int titleIndex = wordMoveCount + minusPrint; // title index is same word moving count + judge printing timing variable
        int bchIndex = title[titleIndex];            // initialize bchIndex variable to title's index to word moving count + judge printing timing variable

        if (minusPrint < 0) // if judge printing timing variable is have minus, printing the result
        {
            out << "\"" << queue->getFront()->getTitle() << "\"" // printing result
                << " / " << queue->getFront()->getNumber() << endl;
            return; // return the funtion
        }
        else                                    // if judge printing timing variable is have 0, or plus value
        {                                       // next setting for word moving relative for title
            if (minusPrint - bch[bchIndex] > 1) // if left hand side is bigger than 1
            {
                wordMoveCount += minusPrint - bch[bchIndex]; // setting the wordMoveCount
            }
            else if (minusPrint - bch[bchIndex] < 1) // if left hand side is smaller than 1
            {
                wordMoveCount += 1; // word moving counting increment
            }
            else // if left hand side is same with 1
            {
                wordMoveCount += 1; // word moving counting increment
            }
        }
    }
}

bool Database_BST::SELECT_EXIST(Database_BST_Node *curNode, int number)
{
    if(curNode==NULL){
        return false;
    }
    else if (curNode->getNumber()==number)
            return true; // for find image path, it is node
    else if (curNode->getNumber() > number)
            SELECT_EXIST(curNode->getLeftChild(), number); // recursive
    else if (curNode->getNumber() < number)
            SELECT_EXIST(curNode->getRightChild(), number); // recursive
}