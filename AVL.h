#ifndef AVL_H
#define AVL_H

#include "Node.h"
#include "AVLInterface.h"

using namespace std;

class AVL : public AVLInterface {
    
private:
    Node* root = NULL;
    bool insertsuccess;
    bool deletesuccess;
    
public:
	AVL();
	~AVL();
    
    Node* getRootNode() const;

    bool add(int data);
    
    int balance(Node *T);
    
    Node * rightRotate(Node* &Y);
    
    Node * leftRotate(Node* &X);
    
    Node * insert(Node* T, int data);
    
    Node* predecessor(Node* T);

	bool remove(int data);
	
	Node * removerecursive(Node* &T, int data);
	
	void replace_parent(Node*& old_root, Node*& local_root);

	void clear();
	
	bool find(Node* T, int data);
	
	int max(int valA, int valB);
};
#endif