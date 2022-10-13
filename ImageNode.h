#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// ImageNode class for EDIT command
class ImageNode{
	private:
		ImageNode* next;
		unsigned char imagePixel;

	public:
		ImageNode();
		~ImageNode();
		void setNext(ImageNode* next);
		ImageNode* getNext();
		void setImagePixel(unsigned char imagePixel);
		unsigned char getImagePixel();
};

// Image class for EDIT command
class Image{
	private:
		ImageNode* head;
		
	public:
		void push(ImageNode* node); // push of stack, push of queue
		ImageNode* s_pop(); // pop of stack
		ImageNode* q_pop(); // pop of queue
		void deleteMemory();
};