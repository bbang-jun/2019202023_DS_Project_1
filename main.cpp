#include "Manager.h"
#include<iostream>
using namespace std;
#include<fstream>
#include<string>

int main(int argc, char* argv[])
{
    // const char* commandFilepath = "command.txt";
    // if (argc > 1)
    //     commandFilepath = argv[1];

    // Manager m;
    // m.Run(commandFilepath);


    string str;
    fstream fs;
    fs.open("img_files/filesnumbers.csv", ios::in);

    while(!fs.eof()){
        getline(fs, str, ',');
        cout<<str<<endl;
    }
    fs.close();
    
    
    ifstream in("command.txt");
    if(!in)
        cout<<"Unable to open command.txt"<<endl;
    else{
        
    }


    return 0;
} 