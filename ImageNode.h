#include <string>
#include <iostream>
using namespace std;

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

class Image{
	private:
		ImageNode* head;
		
	public:
		void setHead(ImageNode* node);
		ImageNode* getHead();
		void push(ImageNode* node);
		ImageNode* s_pop(); // pop of stack
		ImageNode* q_pop(); // pop of queue
};