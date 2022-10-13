#include "Manager.h"
#include <algorithm>

void Run(const char *filepath);
void LOAD(const char *filepath);
void ADD(const char *filepath);
void MODIFY();
void MOVE();
void PRINT();
void SEARCH();
void SELECT();
void EDIT();
void EXIT();

Manager::~Manager() // destructor
{
    delete list;
}

Manager::Manager() // constructor
{
    list = new Loaded_LIST;
    tree = new Database_BST;
    queue = new Queue;
    stack = new Stack;
    image = new Image;
}

void Manager::Run(const char *filepath)
{
    ifstream inCommand(filepath);
    out.open("log.txt", ios::app);
    if (!inCommand) // if not open file, print error message
        out << "Unable to open command.txt" << endl;
    else
    {
        while (!inCommand.eof()) // when eof
        {
            // read one line and tokenization command.txt
            getline(inCommand, command, '\n');
            int str_length = command.length();
            char charCommand[100];
            strcpy(charCommand, command.c_str());
            char *ptr = strtok(charCommand, " ");

            command = ptr;

            if (command == "LOAD")
            {
                LOAD();
            }
            else if (command == "ADD")
            {
                ADD();
            }
            else if (command == "MODIFY")
            {
                MODIFY();
            }
            else if (command == "MOVE")
            {
                MOVE();
            }
            else if (command == "PRINT")
            {
                PRINT();
            }
            else if (command == "SEARCH")
            {
                SEARCH();
            }
            else if (command == "SELECT")
            {
                SELECT();
            }
            else if (command == "EDIT")
            {
                EDIT();
            }
            else if (command == "EXIT")
            {
                EXIT();
            }
            else{
                out<<"========ERROR========"<<endl;
                out << "777" << endl;
                out << "====================" << endl;
            }
        }
    }
}

void Manager::LOAD() // command LOAD
{
    ifstream inCSV("img_files/filesnumbers.csv");
    if (!inCSV) // 7p implementation CSV ERROR code
    {
        out << "========ERROR========" << endl;
        out << "100" << endl;
        out << "====================" << endl
             << endl;
    }
    else
    {
        bool first = true;
        out << "=======LOAD========" << endl;
        list->firstINSERT("img_files", NULL);
        while (!inCSV.eof())
        {
            // read one line and tokenization command.txt
            getline(inCSV, number, ','); // string
            int str_length1 = number.length();
            char ch1[100];
            strcpy(ch1, number.c_str()); // string -> char*
            char *ptr1 = strtok(ch1, ",\n ");
            if (ptr1 == NULL)
                continue;

            number = ptr1; // char* -> string

            if (first == true)
            { // encoding issue resolve
                number.erase(find(number.begin(), number.end(), '\xef'));
                number.erase(find(number.begin(), number.end(), '\xbb'));
                number.erase(find(number.begin(), number.end(), '\xbf'));

                first = false;
            }

            getline(inCSV, title, '\n'); // string
            int str_length2 = title.length();
            char ch2[100];
            strcpy(ch2, title.c_str()); // string -> char*
            char *ptr2 = strtok(ch2, "\r\n.RAW");
            title = ptr2; // char* -> string
            list->INSERT(command, number, "img_files", title, NULL); // insert node to Loaded_LIST
        }
        list->PRINT(); // print Loaded_LIST

        inCSV.close();
        out << "===================" << endl
             << endl;
    }
}

void Manager::ADD() // command ADD
{
    char *ptr1 = strtok(NULL, " "); // folder
    char *ptr2 = strtok(NULL, " "); // filename
    string path(ptr1); // find folder path
    path.append("/");
    path.append(ptr2);
    folder = ptr1;

    if (ptr1 == NULL || ptr2 == NULL || list->LOADED_LIST_CHECK()) // error validation
    {
        out << "========ERROR========" << endl;
        out << "200" << endl;
        out << "====================" << endl;
        return;
    }

    ifstream newCSV(path);
    if (!newCSV) // 7p implementation CSV ERROR code
    {
        out << "========ERROR========" << endl;
        out << "200" << endl;
        out << "====================" << endl;
    }
    else
    {
        // tokenization command.txt
        bool first = true;
        list->firstINSERT(ptr1, NULL);
        out << "=======ADD========" << endl;
        while (!newCSV.eof())
        {
            getline(newCSV, number, ','); // string
            int str_length1 = number.length();
            // char *ch3 = new char[str_length1];
            char ch3[100];
            strcpy(ch3, number.c_str()); // string -> char*
            char *ptr3 = strtok(ch3, ",\n ");

            if (ptr3 == NULL)
                continue;
            number = ptr3; // char* -> string 후 노드에 넣기

            if (first == true)
            { // resolve encoding issue
                number.erase(find(number.begin(), number.end(), '\xef'));
                number.erase(find(number.begin(), number.end(), '\xbb'));
                number.erase(find(number.begin(), number.end(), '\xbf'));

                first = false;
            }
            // tokenization command.txt
            getline(newCSV, title, '\n'); // string
            int str_length2 = title.length();
            // char *ch4 = new char[str_length2];
            char ch4[100];
            strcpy(ch4, title.c_str()); // string -> char*
            char *ptr4 = strtok(ch4, ".RAW\r\n");
            title = ptr4; // char* -> string 
            list->INSERT(command, number, folder, title, NULL); // insert node in Loaded_LIST
        }

        out << "success" << endl;
        out << "===================" << endl
             << endl;
        newCSV.close();
    }
}

void Manager::MODIFY() // MODIFY command
{
    // proccess to argument
    char *tokFolder, *tokTitle, *tokNumber, *temp;
    tokFolder = strtok(NULL, " ");
    temp = strtok(NULL, "");
    title = temp;
    title.erase(find(title.begin(), title.end(), '"'));
    strcpy(temp, title.c_str());
    tokTitle = strtok(temp, "\"");
    tokNumber = strtok(NULL, " ");

    if (tokFolder == NULL || tokTitle == NULL || tokNumber == NULL || list->Unique_Number_CHECK(tokNumber)) // error validation
    {
        out << "========ERROR========" << endl;
        out << "300" << endl;
        out << "====================" << endl
             << endl;
        return;
    }
    else
    {
        Loaded_LIST_Node *prevNode = list->returnPrevNode(tokFolder, tokTitle); // generate a prevNode to point delete node
        list->DELETE(tokFolder, tokTitle, prevNode); // delete a node
        list->INSERT(command, tokNumber, tokFolder, tokTitle, prevNode); // memorise delete node's location and insert that location
        out << "=======MODIFY========" << endl;
        out << "SUCCESS" << endl;
        out << "=====================" << endl
             << endl;
    }
}

void Manager::MOVE() // MOVE command
{
    if(list->folderHead==NULL){ // error validation
        out<<"========ERROR========"<<endl;
        out<<"400"<<endl;
        out<<"===================="<<endl;
    }
    D2Node *prevD2Node = list->folderHead;
    D2Node *curD2Node = list->folderTail;
    Loaded_LIST_Node *curNode;
    Loaded_LIST_Node *prevNode;
    int numberBST = 0;

    while (curD2Node != list->folderHead) // reverse insert to BST(moving tail -> head)
    {
        prevD2Node = list->returnPrevD2Node(curD2Node->getD2Folder());
        curNode = curD2Node->nodeTail;
        while (curNode != curD2Node->getNext())
        {
            prevNode = list->returnPrevNode(curNode->getFolder(), curNode->getTitle()); // save prevNode to moving
            numberBST = stoi(curNode->getNumber()); // convert string to integer
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot()); // insert a node to BST
            curNode = prevNode;
        }
        if (curNode == curD2Node->getNext())
        {
            numberBST = stoi(curNode->getNumber()); // convert string to integer
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot()); // insert a node to BST
        }
        curD2Node = prevD2Node;
    }
    if (curD2Node == list->folderHead)
    {
        curNode = curD2Node->nodeTail;
        while (curNode != curD2Node->getNext())
        {
            prevNode = list->returnPrevNode(curNode->getFolder(), curNode->getTitle()); // save prevNode to moving
            numberBST = stoi(curNode->getNumber()); // convert string to integer
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot()); // insert a node to BST
            curNode = prevNode;
        }
        if (curNode == curD2Node->getNext())
        {
            numberBST = stoi(curNode->getNumber());
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot()); // insert a node to BST
        }
    }
    list->ALLDELETE(); // delete all node in Loaded_LIST structure
}

void Manager::PRINT() // PRINT command
{
    out << "=======PRINT================" << endl;
    tree->IN_ORDER(tree->getRoot()); // print node's information in BST to use In-order traversal
    out << "============================" << endl<<endl;
    if (tree->getRoot() == NULL) // error validation
    {
        out << "========ERROR========" << endl;
        out << "500" << endl;
        out << "====================" << endl;
    }
}

void Manager::SEARCH() // SEARCH command
{
    // proccess of arugment
    string word;
    char *tokWord = strtok(NULL, "");
    word = tokWord;
    word.erase(find(word.begin(), word.end(), '"'));
    word.erase(find(word.begin(), word.end(), '"'));
    out << "=======SEARCH===============" << endl;
    tree->SEARCH_TRAVERSAL(queue, tree->getRoot()); // use Iterative post-order to find word(push to queue)

    while (1) // loop
    {
        int lengthOfTitle = queue->getFront()->getTitle().length();
        int lengthOfWord = word.length();
        tree->SEARCH_BOYERMOORE(queue, queue->getFront()->getTitle(), word, lengthOfTitle, lengthOfWord); // use boyer-moore algorithm
        queue->pop(); // after searching, pop from the queue
        if (queue->isEmpty() == false) // queue is empty, break the loop
            break;
    }
    out << "===========================" << endl
         << endl;
}

void Manager::SELECT() // SELECT command
{
    inputPath = ""; // initialize for re-used
    outFileName = ""; // initialize for re-used
    char *tokNumber;
    tokNumber = strtok(NULL, " ");
    number = tokNumber;
    int selectNum = stoi(number); // string to integer
    if ((tree->SELECT_EXIST(tree->getRoot(), selectNum) != true) || tokNumber==NULL)
    {
        out << "========ERROR========" << endl;
        out << "700" << endl;
        out << "====================" << endl<<endl;
        return;
    }
    Database_BST_Node *selectNode = tree->PRE_ORDER_SELECT(tree->getRoot(), selectNum); // use pre-order traversal, to find file number
    inputPath.append(selectNode->getFolder()); // make input file path for EDIT command
    inputPath.append("/");
    inputPath.append(selectNode->getTitle());
    inputPath.append(".RAW");
    outFileName.append(selectNode->getTitle());

    inputFile = fopen(inputPath.c_str(), "rb"); // open the input file
    if (inputFile == NULL)
    {
        out << "inputFile is NULL" << endl;
    }
    fread(inputData, sizeof(unsigned char), 256 * 256, inputFile); // read proccess

    fclose(inputFile); // close the input file

    out << "==========SELECT============" << endl;
    out << "SUCCESS" << endl;
    out << "==========================" << endl
         << endl;
}

void Manager::EDIT() // EDIT command
{
    FILE *outputFile; // declar
    unsigned char outputData[256][256]; // declare pixel's size
    char *tokWay, *tokLight;
    string way;
    outputPath = ""; // initialize to reused
    int light = 0;
    tokWay = strtok(NULL, " ");
    if (tokWay == NULL) // error validation
    {
        out << "========ERROR========" << endl;
        out << "800" << endl;
        out << "====================" << endl;
        return;
    }
    way = tokWay;

    if (way == "-f") // point symmetry
    {
        for (int i = 0; i < 256; i++) // allocate imageNode
        {
            for (int j = 0; j < 256; j++)
            {
                ImageNode *imageNode = new ImageNode;
                imageNode->setImagePixel(inputData[i][j]); // save file pixel data
                image->push(imageNode); // stack push
            }
        }
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                outputData[i][j] = image->s_pop()->getImagePixel(); // stack pop
            }
        }
        outFileName.append("_flipped"); // make file name
        outputPath.append("./Result/"); // make output file's save path
        outputPath.append(outFileName);
        outputFile = fopen(outputPath.c_str(), "wb");
        fwrite(outputData, sizeof(unsigned char), 256 * 256, outputFile); // write proccess
        fclose(outputFile); // close the file
        out << "==========EDIT============" << endl;
        out << "SUCCESS" << endl;
        out << "=========================" << endl
             << endl;
    }
    else if (way == "-l") // light change
    {
        tokLight = strtok(NULL, " ");
        if (tokLight == NULL)
        {
            out << "========ERROR========" << endl;
            out << "800" << endl;
            out << "====================" << endl;
            return;
        }
        else
        {
            light = atoi(tokLight);
            for (int i = 0; i < 256; i++)
            {
                for (int j = 0; j < 256; j++)
                {
                    ImageNode *imageNode = new ImageNode;
                    imageNode->setImagePixel(inputData[i][j]); // save file pixel data
                    image->push(imageNode); // push to queue
                }
            }

            for (int i = 0; i < 256; i++)
            {
                for (int j = 0; j < 256; j++)
                {
                    int sum = image->q_pop()->getImagePixel() + light; // unsigned char max size is 255, so change the data type
                    if (sum > 255) // fixing max light is 255
                    {
                        outputData[i][j] = 255; 
                    }
                    else if (sum < 0) // fixing min ligh is 0
                    {
                        outputData[i][j] = 0;
                    }
                    else if (sum >= 0 && sum <= 255)
                    {
                        outputData[i][j] = sum;
                    }
                }
            }
            outFileName.append("_adjusted"); // make file name
            outputPath.append("./Result/"); // make output file's save path
            outputPath.append(outFileName);
            outputFile = fopen(outputPath.c_str(), "wb");
            fwrite(outputData, sizeof(unsigned char), 256 * 256, outputFile);
            fclose(outputFile);
            out << "==========EDIT============" << endl;
            out << "SUCCESS" << endl;
            out << "=========================" << endl
                 << endl;
        }
    }
    else if (way == "-r") // resize
    {
        unsigned char outputData[128][128]; // to make size 1/4, declare size
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                // near four pixel's average value
                outputData[i][j] = (inputData[2 * i][2 * j] + inputData[2 * i][(2 * j) + 1] + inputData[(2 * i) + 1][2 * j] + inputData[(2 * i) + 1][(2 * j) + 1]) / 4;
            }
        }
        outFileName.append("_resized"); // make file name
        outputPath.append("./Result/"); // make file path
        outputPath.append(outFileName);
        outputFile = fopen(outputPath.c_str(), "wb");
        fwrite(outputData, sizeof(unsigned char), 256 * 256, outputFile); // write proccess
        fclose(outputFile); // close the file
        out << "==========EDIT============" << endl;
        out << "SUCCESS" << endl;
        out << "=========================" << endl
             << endl;
    }
}

void Manager::EXIT()
{
    tree->POST_DELETE(tree->getRoot()); // BST's memory deallocate
    out << "=======EXIT========" << endl;
    out << "SUCCESS" << endl;
    out << "===================" << endl
         << endl;
}