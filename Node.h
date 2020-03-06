#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "NodeInterface.h"

class Node : public NodeInterface {

private:
    friend class AVL;

public:
	int height;
	Node* left;
    Node* right;
    int value;
    
	Node();
	Node(int val);
	~Node();
	
	int getData() const;

	Node* getLeftChild() const;

	Node* getRightChild() const;
	
	int getHeight();

};
#endif