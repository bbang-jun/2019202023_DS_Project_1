#pragma once
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include "Loaded_LIST.h"
#include "Database_BST.h"
#include <iostream>
using namespace std;
#include <string>
#include <cstring> // use strtok
#include <string.h>
#include <algorithm>
#include "ImageNode.h"

class Manager
{
private:
    ofstream out;
public:
    FILE* input_file;
    unsigned char input_data[256][256];
    const char *filepath;
    string command, number, title, folder;
    string firstArg, secondArg;
    string outputPath, inputPath, outFileName;
    Loaded_LIST *list;
    Database_BST* tree;
    Queue* queue;
    Stack* stack;
    Image* image;
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