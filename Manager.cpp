#include "Manager.h"

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
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
    delete list;
}

Manager::Manager()
{
    list = new Loaded_LIST;
}

void Manager::Run(const char *filepath)
{
    ifstream inCommand(filepath);
    if (!inCommand)
        cout << "Unable to open command.txt" << endl;
    else
    {
        while (!inCommand.eof())
        {
            getline(inCommand, command, '\n');
            int str_length = command.length();
            char *charCommand = new char[str_length];
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
            }
            else if (command == "PRINT")
            {
            }
            else if (command == "SEARCH")
            {
            }
            else if (command == "SELECT")
            {
            }
            else if (command == "EDIT")
            {
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
        cout << "========ERROR========" << endl;
        cout << "100" << endl;
        cout << "====================" << endl<<endl;
    }
    else
    {
        cout << "=======LOAD========" << endl;
        list->firstINSERT("img_files", NULL);
        while (!inCSV.eof())
        {
            getline(inCSV, number, ','); // string
            int str_length1 = number.length();
            char *ch1 = new char[str_length1];
            strcpy(ch1, number.c_str()); // string -> char*
            char *ptr1 = strtok(ch1, ",\n ");
            if (ptr1 == NULL)
                continue;
            number = ptr1; // char* -> string 후 노드에 넣기

            getline(inCSV, title, '\n'); // string
            int str_length2 = title.length();
            char *ch2 = new char[str_length2];
            strcpy(ch2, title.c_str()); // string -> char*
            char *ptr2 = strtok(ch2, "\r\n.RAW");
            title = ptr2; // char* -> string 후 노드에 넣기
            list->INSERT(command, number, "img_files", title, NULL);
        }
        //list->PRINT();

        inCSV.close();
        cout << "===================" << endl << endl;
    }
}

void Manager::ADD()
{
    char *ptr1 = strtok(NULL, " "); // folder
    char* ptr2 = strtok(NULL, " "); // filename 
    string path(ptr1);
    path.append("/");
    path.append(ptr2);
    folder=ptr1;

    if (ptr1 == NULL || ptr2 == NULL || list->LOADED_LIST_CHECK())
    {
        cout << "========ERROR========" << endl;
        cout << "200" << endl;
        cout << "====================" << endl;
        return;
    }

    ifstream newCSV(path);
    if (!newCSV) // 7p implementation CSV ERROR code
    {
        cout << "========ERROR========" << endl;
        cout << "200" << endl;
        cout << "====================" << endl;
    }
    else
    {
        list->firstINSERT(ptr1, NULL);
        cout << "=======ADD========" << endl;
        while (!newCSV.eof())
        {
            getline(newCSV, number, ','); // string
            int str_length1 = number.length();
            char *ch3 = new char[str_length1];
            strcpy(ch3, number.c_str()); // string -> char*
            char *ptr3 = strtok(ch3, ",\n ");

            if (ptr3 == NULL)
                continue;
            number = ptr3; // char* -> string 후 노드에 넣기

            getline(newCSV, title, '\n'); // string
            int str_length2 = title.length();
            char *ch4 = new char[str_length2];
            strcpy(ch4, title.c_str()); // string -> char*
            char *ptr4 = strtok(ch4, ".RAW\r\n");
            title = ptr4; // char* -> string 후 노드에 넣기
            // cout<<title<<" "<<number<<endl;
            list->INSERT(command, number, folder, title, NULL);
        }

        cout << "success" << endl;
        cout << "===================" << endl << endl;
        newCSV.close();
    }
}

void Manager::MODIFY()
{
    char *tokFolder, *tokTitle, *tokNumber, *temp;
    string temp2;
    tokFolder = strtok(NULL, " "); 
    temp = strtok(NULL, "");
    title=temp;
    title.erase(find(title.begin(), title.end(), '"'));
    strcpy(temp, title.c_str());
    tokTitle = strtok(temp, "\"");
    tokNumber = strtok(NULL, " ");

    if (tokFolder == NULL || tokTitle == NULL || tokNumber == NULL || list->Unique_Number_CHECK(tokNumber))
    {
        cout << "========ERROR========" << endl;
        cout << "300" << endl;
        cout << "====================" << endl << endl;
        return;
    }
    else
        {
        Loaded_LIST_Node *prevNode = list->returnPrevNode(tokFolder, tokTitle); // 삭제할 노드의 이전 노드가 새로 생긴 노드를 가리켜야 하므로 생성
        list->DELETE(tokFolder, tokTitle, prevNode);
        list->INSERT(command, tokNumber, tokFolder, tokTitle, prevNode); // INSERT 안에서 prevNode가 새로 생긴 노드를 가리킴
        list->PRINT();
        cout << "=======MODIFY========" << endl;
        cout << "SUCCESS" << endl;
        cout << "=====================" << endl << endl;
     }
}

void Manager::MOVE()
{
}

void Manager::PRINT()
{
}

void Manager::SEARCH()
{
}

void Manager::SELECT()
{
}

void Manager::EDIT()
{
}

void Manager::EXIT()
{
    cout<<"=======EXIT========"<<endl;
    cout<<"SUCCESS"<<endl;
    cout<<"==================="<<endl << endl;
}