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
}

Manager::Manager(){

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
        cout << "====================" << endl;
    }
    else
    {
        cout << "=======LOAD========" << endl;
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
            list->INSERT(command, title, "img_files", number);
        }
        list->PRINT();

        inCSV.close();
        cout << "===================" << endl;
    }
}

void Manager::ADD()
{
    char *ptr1, *ptr2;
    ptr1 = strtok(NULL, " ");
    ptr2 = strtok(NULL, " ");

    if (ptr1 == NULL || ptr2 == NULL || list->LOADED_LIST_CHECK())
    {
        cout << "========ERROR========" << endl;
        cout << "200" << endl;
        cout << "====================" << endl;
        return;
    }

    ifstream newCSV("new_files/new_filesnumbers.csv");
    if (!newCSV) // 7p implementation CSV ERROR code
    {
        cout << "========ERROR========" << endl;
        cout << "200" << endl;
        cout << "====================" << endl;
    }
    else
    {
        cout << "=======ADD========" << endl;
        cout << "success" << endl;
        cout << "===================" << endl;
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
            list->INSERT(command, title, "new_files", number);
        }
        // list->PRINT();

        newCSV.close();
    }
}

void Manager::MODIFY()
{
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
}