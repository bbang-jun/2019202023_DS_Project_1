#include <string>
#include <iostream>
using namespace std;

class ImageNode
{
	friend class TreeNode;
	friend class BinarySearchTree;
	friend class TreeManager;
private:
	string m_name;
	string dirname;

	int unique_number;

public:
	ImageNode() { }
	ImageNode(string name, string dir, int number){

	}

	friend ostream& operator<<(ostream& os, const ImageNode& node) {
		os << "(node.m_name: " << node.m_name << "), "; //Debug with print
		return os;
	}
};