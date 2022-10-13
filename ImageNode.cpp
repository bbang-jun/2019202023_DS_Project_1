#include "ImageNode.h"

// ImageNode class
ImageNode::ImageNode()
{
    this->next = NULL;
}
ImageNode::~ImageNode()
{
}
void ImageNode::setNext(ImageNode *next)
{
    this->next = next;
}
ImageNode *ImageNode::getNext()
{
    return this->next;
}
void ImageNode::setImagePixel(unsigned char imagePixel)
{
    this->imagePixel = imagePixel;
}
unsigned char ImageNode::getImagePixel()
{
    return this->imagePixel;
}

// Image class 
void Image::push(ImageNode *newNode) // push of stack & push of queue
{

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        ImageNode *curNode = head;
        while (curNode->getNext() != NULL)
        {
            curNode = curNode->getNext();
            if (curNode->getNext() == NULL)
                break;
        }
        curNode->setNext(newNode);
    }
}
ImageNode *Image::s_pop() // return most last inserted ImageNode
{ // pop of stack
    ImageNode *curNode = head;
    ImageNode *tempNode;

    if (head->getNext() == NULL)
    {
        return head;
    }
    else
    {
        while (curNode->getNext()->getNext() != NULL)
        {   
            curNode = curNode->getNext();
        }
        tempNode=curNode->getNext();
        curNode->setNext(NULL);
        return tempNode;
    }
}
ImageNode *Image::q_pop() // return first inserted ImageNode
{ // pop of queue
    if (head->getNext() == NULL)
    {
        return head;
    }
    else
    {
        ImageNode *tempNode = head;
        head = head->getNext();
        tempNode->setNext(NULL);
        return head;
    }
}

void Image::deleteMemory(){
    ImageNode* delNode;
    ImageNode* curNode=head;

    while(curNode->getNext()!=NULL){
        delNode=curNode;
        curNode = curNode->getNext();
        delete delNode;
    }
    delete curNode;
}