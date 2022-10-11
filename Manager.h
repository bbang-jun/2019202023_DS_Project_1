#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Loaded_LIST.h"
#include "Database_BST.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <cstring> // use strtok
#include <string.h>
#include <algorithm>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    const char* ERROR_LOG_PATH = "logERR.txt";
    

    std::ofstream fout;
    std::ofstream ferr;


public:
    FILE* input_file;
    unsigned char input_data[256][256];
    const char *filepath;
    string command, number, title, folder;
    string firstArg, secondArg;
    Loaded_LIST *list;
    Database_BST* tree;
    Queue* queue;
    Stack* stack;
    Manager();
    ~Manager();
    void Run(const char* filepath);
    void LOAD();
    void ADD();
    void MODIFY();
    void MOVE();
    void PRINT();
    void SEARCH();
    void SELECT();
    void EDIT();
    void EXIT();

};