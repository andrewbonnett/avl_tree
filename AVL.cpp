#include <iostream>

#include "AVL.h"

using namespace std;

AVL::AVL() {
	
}

AVL::~AVL() {
    clear();
}
    
Node* AVL::getRootNode() const {
    return root;
}

bool AVL::add(int data) {
	insertsuccess = false;
	root = insert(root, data);
	return insertsuccess;
}

int AVL::balance(Node *T)  {  
    if (T == NULL) { 
        return 0;
    }
    if (T->left == NULL && T->right == NULL) {
		return 0;
	}
	else if (T->left == NULL && T->right != NULL) {
		return -1 * (T->right->height);
	}
	else if (T->right == NULL && T->left != NULL) {
		return T->left->height;
	}
	else if (T->left != NULL && T->right != NULL) {
    	return T->left->height - T->right->height;
	}
}

Node* AVL::rightRotate(Node* &Y)  {  
    Node *X = Y->left;  
    Node *Temp = X->right;  
  
    // Perform rotation  
    X->right = Y;  
    Y->left = Temp;  
  
	//update height of Y
	if (Y->left == NULL && Y->right == NULL) {
		Y->height = 1;
		cout << "*** New Height is 1" << endl;
	}
	else if (Y->left == NULL && Y->right != NULL) {
		Y->height = 1 + Y->right->height;
	}
	else if (Y->right == NULL && Y->left != NULL) {
		Y->height = 1 + Y->left->height;
	}
	else if (X->left != NULL && Y->right != NULL) {
		Y->height = 1 + max(Y->left->height, Y->right->height);
	}
    // Update height of X
    if (X->left == NULL && X->right == NULL) {
		X->height = 1;
	}
	else if (X->left == NULL && X->right != NULL) {
		X->height = 1 + X->right->height;
	}
	else if (X->right == NULL && X->left != NULL) {
		X->height = 1 + X->left->height;
	}
	else if (X->left != NULL && X->right != NULL) {
		X->height = 1 + max(X->left->height, X->right->height);
	}
    return X;
}

Node * AVL::leftRotate(Node* &X)  {
    Node *Y = X->right;
    Node *Temp = Y->left;
    // Rotate  
    Y->left = X;
    X->right = Temp;
    // Update height of X
    if (X->left == NULL && X->right == NULL) {
		X->height = 1;
		cout << "**New height is 1" << endl;
    }
	else if (X->left == NULL && X->right != NULL) {
		X->height = 1 + X->right->height;
	}
	else if (X->right == NULL && X->left != NULL) {
		X->height = 1 + X->left->height;
	}
	else if (X->left != NULL && X->right != NULL) {
		X->height = 1 + max(X->left->height, X->right->height);
	}
	// Update height of Y
	if (Y->left == NULL && Y->right == NULL) {
		Y->height = 1;
	}
	else if (Y->left == NULL && Y->right != NULL) {
		Y->height = 1 + Y->right->height;
	}
	else if (Y->right == NULL && Y->left != NULL) {
		Y->height = 1 + Y->left->height;
		cout << "New Height is " << Y->height << endl;
	}
	else if (X->left != NULL && Y->right != NULL) {
		Y->height = 1 + max(Y->left->height, Y->right->height);
	}
    return Y;
}  

Node* AVL::insert(Node* T, int data) {
	if (T == NULL) {
		T = new Node(data);
		insertsuccess = true;
		cout << "Value " << data << " has been inserted." << endl;
		return T;
	}
	else if (T->value == data) {
		return T;
	}
	else if (data > T->value) {
		T->right = insert(T->right, data);
	}
	else {
		T->left = insert(T->left, data);
	}
	//update height
	if (T->left == NULL && T->right == NULL) {
		T->height = 1;
	}
	else if (T->left == NULL && T->right != NULL) {
		T->height = 1 + T->right->height;
	}
	else if (T->right == NULL && T->left != NULL) {
		T->height = 1 + T->left->height;
	}
	else if (T->left != NULL && T->right != NULL) {
		T->height = 1 + max(T->left->height, T->right->height);
	}
	cout << "Height of node "<< T->value << " is " << T->height << endl;
	//for this parent node, check if imbalanced
	int balanceval = balance(T);
	cout << "Balanceval: " << balanceval << endl;
	
	//cases for balance less than -1 or greater than 1
	// L-L (Parent balance is +2, left child balance is +1)
    if (balanceval > 1 && (balance(T->left) > 0)) {
        cout << "This code is executing 1" << endl;
         return rightRotate(T); //why can I not assign back??
    }
    // R-R (Parent balance is -2, left child balance is -1)
    else if (balanceval < -1 && (balance(T->right) < 0)) {
        cout << "This code is executing 2" << endl;
        return leftRotate(T);
    }
    // L-R  (Parent balance is 2, left child balance is -1)
    else if (balanceval > 1 && (balance(T->left) < 0))  {  
        cout << "This code is executing 3" << endl;
        T->left = leftRotate(T->left);
        return rightRotate(T);
    }
    // R-L  (Parent balance is -2, left child balance is +1)
    else if (balanceval < -1 && (balance(T->right) > 0))  {  
        cout << "This code is executing 4" << endl;
        T->right = rightRotate(T->right);  
        return leftRotate(T);
    }
    return T;
    
}

Node* AVL::predecessor(Node* T) {  
    Node* current = T;
    
    while (current->right != NULL)  
        current = current->right;  
  
    return current;  
}


bool AVL::remove(int data) {
	deletesuccess = false;
	root = removerecursive(root, data);
	return deletesuccess;
}

Node * AVL::removerecursive(Node* &T, int data) {
    if (T == NULL) {
		return T;
	}
	cout << "Attempting to delete " << data << " at node " << T->value << endl;
	if (data > T->value) {
		T->right = removerecursive(T->right, data);
	}
	else if (data < T->value) {
		T->left = removerecursive(T->left, data);
	}
	
	else { //(T->value == data)
		// I need to erase this node
		Node *victim = T;
		//No Children
		if (T->left == NULL || T->right == NULL) {
			//No children
			if (T->left == NULL && T->right == NULL) {
	            T = NULL;
			}
			//One Child
			else if (T->right != NULL) {
				T = T->right;
			}
			else if (T->left != NULL) {
				T = T->left;
			}
			delete victim;
			deletesuccess = true;
			
		}
        else {  
            // inorder predecessor (largest in the left subtree)  
            Node* temp = predecessor(T->left);  
  
            // Copy the inorder successor's  
            // data to this node  
            T->value = temp->value;  
  
            // Delete the inorder successor  
            T->left = removerecursive(T->left, temp->value);  
        }  
    }  
  
    // If the tree had only one node then return  
    if (T == NULL)  
    	return T;  
  
    //UPDATE HEIGHT OF THE CURRENT NODE
    if (T->left == NULL && T->right == NULL) {
		T->height = 1;
	}
	else if (T->left == NULL && T->right != NULL) {
		T->height = 1 + T->right->height;
	}
	else if (T->right == NULL && T->left != NULL) {
		T->height = 1 + T->left->height;
	}
	else if (T->left != NULL && T->right != NULL) {
		T->height = 1 + max(T->left->height, T->right->height);
	}
  
    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balanceval = balance(T);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  //cases for balance less than -1 or greater than 1
	// L-L (Parent balance is +2, left child balance is +1)
    if (balanceval > 1 && (balance(T->left) >= 0)) {
        cout << "This code is executing 1" << endl;
         return rightRotate(T); //why can I not assign back??
    }
    // R-R (Parent balance is -2, left child balance is -1)
    else if (balanceval < -1 && (balance(T->right) <= 0)) {
        cout << "This code is executing 2" << endl;
        return leftRotate(T);
    }
    // L-R  (Parent balance is 2, left child balance is -1)
    else if (balanceval > 1 && (balance(T->left) < 0))  {  
        cout << "This code is executing 3" << endl;
        T->left = leftRotate(T->left);
        return rightRotate(T);
    }
    // R-L  (Parent balance is -2, left child balance is +1)
    else if (balanceval < -1 && (balance(T->right) > 0))  {  
        cout << "This code is executing 4" << endl;
        T->right = rightRotate(T->right);  
        return leftRotate(T);
    }
    return T;  
}

void AVL::replace_parent(Node* &old_root, Node* &local_root) {
	if (local_root->right != NULL) {
		replace_parent(old_root, local_root->right);
	}
	else {
	    old_root->value = local_root->value;
	    old_root = local_root;
	    local_root = local_root->left;
	}
}

void AVL::clear() {
    while (root != NULL) {
    	remove(root->value);
    }
}

int AVL::max(int valA, int valB)  {  
    if (valA > valB)
        return valA;
    else
        return valB;
}