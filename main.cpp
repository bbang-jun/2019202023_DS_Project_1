#include "Manager.h"
#include "Loaded_LIST.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <cstring> // use strtok

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
            string temp;

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
                    while (getline(inCSV, number, ',')&&getline(inCSV, title, '\n'))
                    {
                        cout<<number<<'/'<<title<<endl;
                        list->INSERT(command, title, "img_files", number);
                        //cout<<title<<"/"<<number<<endl;
                    }
                    getline(inCSV, temp, ',');
                    
                    //temp2=temp.c_str();
                    inCSV.close();
                    cout << "===================" << endl;
                }
            }
        }
    }
    //list->PRINT();
    return 0;
}