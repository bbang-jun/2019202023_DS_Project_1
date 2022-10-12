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

Manager::~Manager()
{
    delete list;
}

Manager::Manager()
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
    if (!inCommand)
        out << "Unable to open command.txt" << endl;
    else
    {
        while (!inCommand.eof())
        {
            getline(inCommand, command, '\n');
            int str_length = command.length();
            // char *charCommand = new char[str_length];
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
        }
    }
}

void Manager::LOAD()
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
            getline(inCSV, number, ','); // string
            int str_length1 = number.length();
            // char *ch1 = new char[str_length1];
            char ch1[100];
            strcpy(ch1, number.c_str()); // string -> char*
            char *ptr1 = strtok(ch1, ",\n ");
            if (ptr1 == NULL)
                continue;

            number = ptr1; // char* -> string 후 노드에 넣기

            if (first == true)
            {
                number.erase(find(number.begin(), number.end(), '\xef'));
                number.erase(find(number.begin(), number.end(), '\xbb'));
                number.erase(find(number.begin(), number.end(), '\xbf'));

                first = false;
            }

            getline(inCSV, title, '\n'); // string
            int str_length2 = title.length();
            // char *ch2 = new char[str_length2];
            char ch2[100];
            strcpy(ch2, title.c_str()); // string -> char*
            char *ptr2 = strtok(ch2, "\r\n.RAW");
            title = ptr2; // char* -> string 후 노드에 넣기
            list->INSERT(command, number, "img_files", title, NULL);
        }
        list->PRINT();

        inCSV.close();
        out << "===================" << endl
             << endl;
    }
}

void Manager::ADD()
{
    char *ptr1 = strtok(NULL, " "); // folder
    char *ptr2 = strtok(NULL, " "); // filename
    string path(ptr1);
    path.append("/");
    path.append(ptr2);
    folder = ptr1;

    if (ptr1 == NULL || ptr2 == NULL || list->LOADED_LIST_CHECK())
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
            {
                number.erase(find(number.begin(), number.end(), '\xef'));
                number.erase(find(number.begin(), number.end(), '\xbb'));
                number.erase(find(number.begin(), number.end(), '\xbf'));

                first = false;
            }

            getline(newCSV, title, '\n'); // string
            int str_length2 = title.length();
            // char *ch4 = new char[str_length2];
            char ch4[100];
            strcpy(ch4, title.c_str()); // string -> char*
            char *ptr4 = strtok(ch4, ".RAW\r\n");
            title = ptr4; // char* -> string 후 노드에 넣기
            list->INSERT(command, number, folder, title, NULL);
        }

        out << "success" << endl;
        out << "===================" << endl
             << endl;
        newCSV.close();
    }
}

void Manager::MODIFY()
{
    char *tokFolder, *tokTitle, *tokNumber, *temp;
    tokFolder = strtok(NULL, " ");
    temp = strtok(NULL, "");
    title = temp;
    title.erase(find(title.begin(), title.end(), '"'));
    strcpy(temp, title.c_str());
    tokTitle = strtok(temp, "\"");
    tokNumber = strtok(NULL, " ");

    if (tokFolder == NULL || tokTitle == NULL || tokNumber == NULL || list->Unique_Number_CHECK(tokNumber))
    {
        out << "========ERROR========" << endl;
        out << "300" << endl;
        out << "====================" << endl
             << endl;
        return;
    }
    else
    {
        Loaded_LIST_Node *prevNode = list->returnPrevNode(tokFolder, tokTitle); // 삭제할 노드의 이전 노드가 새로 생긴 노드를 가리켜야 하므로 생성
        list->DELETE(tokFolder, tokTitle, prevNode);
        list->INSERT(command, tokNumber, tokFolder, tokTitle, prevNode); // INSERT 안에서 prevNode가 새로 생긴 노드를 가리킴
        out << "=======MODIFY========" << endl;
        out << "SUCCESS" << endl;
        out << "=====================" << endl
             << endl;
    }
}

void Manager::MOVE()
{
    if(list->folderHead==NULL){
        out<<"========ERROR========"<<endl;
        out<<"400"<<endl;
        out<<"===================="<<endl;
    }
    D2Node *prevD2Node = list->folderHead;
    D2Node *curD2Node = list->folderTail;
    Loaded_LIST_Node *curNode;
    Loaded_LIST_Node *prevNode;
    int numberBST = 0;

    while (curD2Node != list->folderHead)
    {
        prevD2Node = list->returnPrevD2Node(curD2Node->getD2Folder());
        curNode = curD2Node->nodeTail;
        while (curNode != curD2Node->getNext())
        {
            prevNode = list->returnPrevNode(curNode->getFolder(), curNode->getTitle());
            numberBST = stoi(curNode->getNumber());
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot());
            curNode = prevNode;
        }
        if (curNode == curD2Node->getNext())
        {
            numberBST = stoi(curNode->getNumber());
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot());
        }
        curD2Node = prevD2Node;
    }
    if (curD2Node == list->folderHead)
    {
        curNode = curD2Node->nodeTail;
        while (curNode != curD2Node->getNext())
        {
            prevNode = list->returnPrevNode(curNode->getFolder(), curNode->getTitle());
            numberBST = stoi(curNode->getNumber());
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot());
            curNode = prevNode;
        }
        if (curNode == curD2Node->getNext())
        {
            numberBST = stoi(curNode->getNumber());
            tree->INSERT(command, numberBST, curNode->getFolder(), curNode->getTitle(), tree->getRoot());
        }
    }
    list->ALLDELETE();
}

void Manager::PRINT()
{
    out << "=======PRINT================" << endl;
    tree->PRINT();
    out << "============================" << endl<<endl;
    if (tree->getRoot() == NULL)
    {
        out << "========ERROR========" << endl;
        out << "500" << endl;
        out << "====================" << endl;
    }
}

void Manager::SEARCH()
{
    string word;
    char *tokWord = strtok(NULL, "");
    word = tokWord;
    word.erase(find(word.begin(), word.end(), '"'));
    word.erase(find(word.begin(), word.end(), '"'));
    out << "=======SEARCH===============" << endl;
    tree->SEARCH_TRAVERSAL(queue, tree->getRoot());

    while (1)
    {
        int lengthOfTitle = queue->getFront()->getTitle().length();
        int lengthOfWord = word.length();
        tree->SEARCH_BOYERMOORE(queue, queue->getFront()->getTitle(), word, lengthOfTitle, lengthOfWord);
        queue->pop();
        if (queue->isEmpty() == false)
            break;
    }
    out << "===========================" << endl
         << endl;
}

void Manager::SELECT()
{
    inputPath = "";
    outFileName = "";
    char *tokNumber;
    tokNumber = strtok(NULL, " ");
    if (tokNumber == NULL)
    {
        out << "========ERROR========" << endl;
        out << "700" << endl;
        out << "====================" << endl;
        return;
    }
    number = tokNumber;
    int selectNum = stoi(number);
    Database_BST_Node *selectNode = tree->PRE_ORDER_SELECT(tree->getRoot(), selectNum);
    inputPath.append(selectNode->getFolder());
    inputPath.append("/");
    inputPath.append(selectNode->getTitle());
    inputPath.append(".RAW");
    outFileName.append(selectNode->getTitle());

    input_file = fopen(inputPath.c_str(), "rb");
    if (input_file == NULL)
    {
        out << "file not found" << endl;
    }
    fread(input_data, sizeof(unsigned char), 256 * 256, input_file);

    // for(int i=0; i<256; i++)
    //     for(int j=0; j<256; j++)
    //         output_data[i][j]=255-input_data[i][j];

    // output_file = fopen("./the booooo.RAW", "wb");
    // fwrite(output_data, sizeof(unsigned char), 256*256, output_file);
    fclose(input_file);

    out << "==========SELECT============" << endl;
    out << "SUCCESS" << endl;
    out << "==========================" << endl
         << endl;
}

void Manager::EDIT()
{
    FILE *output_file;
    unsigned char output_data[256][256];
    char *tokWay, *tokLight;
    string way;
    outputPath = "";
    // output files path
    int light = 0;
    tokWay = strtok(NULL, " ");
    if (tokWay == NULL)
    {
        out << "========ERROR========" << endl;
        out << "800" << endl;
        out << "====================" << endl;
        return;
    }
    way = tokWay;

    if (way == "-f")
    {
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                ImageNode *imageNode = new ImageNode;
                imageNode->setImagePixel(input_data[i][j]);
                image->push(imageNode);
            }
        }
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                output_data[i][j] = image->s_pop()->getImagePixel();
            }
        }
        outFileName.append("_flipped");
        outputPath.append("./Result/");
        outputPath.append(outFileName);
        output_file = fopen(outputPath.c_str(), "wb");
        fwrite(output_data, sizeof(unsigned char), 256 * 256, output_file);
        fclose(output_file);
        out << "==========EDIT============" << endl;
        out << "SUCCESS" << endl;
        out << "=========================" << endl
             << endl;
    }
    else if (way == "-l")
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
                    imageNode->setImagePixel(input_data[i][j]);
                    image->push(imageNode);
                }
            }

            for (int i = 0; i < 256; i++)
            {
                for (int j = 0; j < 256; j++)
                {
                    int sum = image->q_pop()->getImagePixel() + light;
                    if (sum > 255)
                    {
                        output_data[i][j] = 255;
                    }
                    else if (sum < 0)
                    {
                        output_data[i][j] = 0;
                    }
                    else if (sum >= 0 && sum <= 255)
                    {
                        output_data[i][j] = sum;
                    }
                }
            }
            outFileName.append("_adjusted");
            outputPath.append("./Result/");
            outputPath.append(outFileName);
            output_file = fopen(outputPath.c_str(), "wb");
            fwrite(output_data, sizeof(unsigned char), 256 * 256, output_file);
            fclose(output_file);
            out << "==========EDIT============" << endl;
            out << "SUCCESS" << endl;
            out << "=========================" << endl
                 << endl;
        }
    }
    else if (way == "-r")
    {
        unsigned char output_data[128][128];
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                output_data[i][j] = (input_data[2 * i][2 * j] + input_data[2 * i][(2 * j) + 1] + input_data[(2 * i) + 1][2 * j] + input_data[(2 * i) + 1][(2 * j) + 1]) / 4;
            }
        }
        outFileName.append("_resized");
        outputPath.append("./Result/");
        outputPath.append(outFileName);
        output_file = fopen(outputPath.c_str(), "wb");
        fwrite(output_data, sizeof(unsigned char), 256 * 256, output_file);
        fclose(output_file);
        out << "==========EDIT============" << endl;
        out << "SUCCESS" << endl;
        out << "=========================" << endl
             << endl;
    }
}

void Manager::EXIT()
{
    out << "=======EXIT========" << endl;
    out << "SUCCESS" << endl;
    out << "===================" << endl
         << endl;
}