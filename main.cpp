#include "Manager.h"
#include "Loaded_LIST.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <cstring> // use strtok
#include <string.h>

int main(int argc, char *argv[])
{
    Loaded_LIST *list = new Loaded_LIST;

    ifstream inCommand("command.txt");
    if (!inCommand)
        cout << "Unable to open command.txt" << endl;
    else
    {
        while (!inCommand.eof())
        {
            string command;
            string number;
            string title;

            getline(inCommand, command, '\n');

            if (command == "LOAD")
            {
                int i = 0;
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
                        char ch1[str_length1];
                        strcpy(ch1, number.c_str()); // string -> char*
                        char*ptr1=strtok(ch1, ",\n "); 
                        if(ptr1==NULL) continue;
                        number = ptr1; // char* -> string 후 노드에 넣기

                        getline(inCSV, title, '\n'); // string
                        int str_length2 = title.length();
                        char ch2[str_length2];
                        strcpy(ch2, title.c_str()); // string -> char*
                        char*ptr2=strtok(ch2, ",\n.RAW");
                        title = ptr2; // char* -> string 후 노드에 넣기

                        list->INSERT(command, title, "img_files", number);

                    }
                    list->PRINT();
                    
                    inCSV.close();
                    cout << "===================" << endl;
                }
            }
        }
    }
    return 0;
}