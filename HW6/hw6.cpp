/**
*  Author: 范真瑋
*  Date: Nov. 25, 2016
*  Purpose: Given a sequence of numbers, determine those numbers that appear 2n+1 times,
*            where n is an integer and n ≥ 0.
*/

#include <iostream>
using namespace std;

class Node {  //  tree node
friend class Tree;
public:
	Node (const int& d) {
		data = d;
		left = NULL;
		right = NULL;
	}
    int data;
    Node *left;
    Node *right;
};

class Tree {  //  binary search tree
public:
    Tree();  //  constructor set the tree to null
	void in (const int& );  //  insert
	bool rm (const int& );  //  remove
	void de (Node*);  //  delete tree nodes
	void clean (void);  //  reset the tree
	void printNode(Node*);  //  print the nodes
	void printLeft(Node*);  //  print the left nodes
	void printRight(Node*);  //  print the right nodes
	void print(void);  //  print the answer
private:
    Node *root;
    int maxN;  //  store the maximum number
};

Tree::Tree() {
    root = NULL;
    maxN = 0;
}

void Tree::in (const int& data) {  //  insert
    if (data > maxN) {
        maxN = data;  //  maximum number
    }

    Node *temp = new Node(data);

    if (!root) {  //  the tree is null
        root = temp;
    }
    else {
        Node *current = root;
        Node *parent = NULL;

        while (current) {  //  finding the position to insert
            parent = current;
            if (temp->data > current->data) {
                current = current->right;
            }
            else {
                current = current->left;
            }
        }

        if (temp->data < parent->data) {  //  smaller numbers are stored in the left subtree
            parent->left = temp;
        }
        else {
            parent->right = temp;  //  larger ones are stored in the right subtree
        }
    }
}

bool Tree::rm (const int& data) {  //  remove
    bool found = false;  //  not found

    if (!root) {  //  the tree is null
        return false;
    }
    Node *current = root, *parent = NULL;
    while (current) {  //  finding the same number
        if (current->data == data) {  //  found
            found = true;
            break;
        }
        else {
            parent = current;
            if (data > current->data) {
                current = current->right;
            }
            else {
                current = current->left;
            }
        }
    }

    if  (!found) {  //  not found
        return false;
    }

    //  remove a leaf node
    if (current->left == NULL && current->right == NULL) {
        if (current == root) {  //  remove the root
            delete current;
            current = NULL;
            root = NULL;
            maxN = 0;

            return true;
        }

        if (current->data == maxN) {
            maxN = parent->data;
        }

        if (parent->left == current) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        delete current;
        current = NULL;

        return true;
    }

    //  remove a nonleaf node that has only one son
    if ( (current->left == NULL && current->right != NULL) ||
        (current->left != NULL && current->right == NULL) ) {

       if (current->left == NULL && current->right != NULL) {  //  right son
           if (current == root) {  //  remove the root
                root = current->right;
           }
           else if (parent->left == current) {
             parent->left = current->right;
           }
           else {
             parent->right = current->right;
             if (current->data == maxN) {
                maxN = current->right->data;
             }
           }
       }
       else {  //  left son
            if (current == root) {  //  remove the root
                root = current->left;
            }
            else if (parent->left == current) {
                parent->left = current->left;
            }
            else {
                parent->right = current->left;
                if (current->data == maxN) {
                    maxN = current->left->data;
                }
           }
       }
        delete current;
        current = NULL;

        return true;
    }

    //  remove a nonleaf node that has two sons
    if (current->left != NULL && current->right != NULL) {
        Node *r = current->right;
        Node *temp;
        if ((r->left == NULL) && (r->right == NULL) && (current != root)) {  //  right subtree only has one node
            temp = current;
            if (parent->left == current) {
                parent->left = r;
            }
            else {
                parent->right = r;
            }
            r->left = current->left;
            current = r;
            delete temp;
            temp = NULL;
        }
        else {
            if ((current->right)->left != NULL) {
                Node *q;
                Node *parent;
                parent = current->right;
                q = (current->right)->left;
                while(q->left != NULL) {  //  finding the left-most node q in the right subtree
                   parent = q;
                   q = q->left;
                }
		 		current->data = q->data;
		 		if (q->right) {
                    parent->left = q->right;
		 		}
		 		else {
                    parent->left = NULL;
		 		}
                delete q;
                q = NULL;
           }
           else {  //  current->right is the left-most node in the right subtree
               Node *temp;
               temp = current->right;
               current->data = temp->data;
               current->right = temp->right;
               delete temp;
               temp = NULL;
           }

        }

		 return true;
    }

}

void Tree::de (Node *leaf) {  //  delete tree nodes
    if (leaf) {
        de (leaf->left);
        de (leaf->right);
        delete leaf;
        leaf = NULL;
    }
}

void Tree::clean (void) {  //  reset the tree
    de (root);
    root = NULL;
    maxN = 0;
}

void Tree::printNode(Node *leaf) {  //  print the nodes
    if(leaf)
    {
        if(leaf->left) {
            printNode(leaf->left);
        }

        cout << leaf->data;
        if (leaf->data != maxN) {
            cout << " ";
        }

        if(leaf->right) {
            printNode(leaf->right);
        }
    }
    else {  //  the tree is null
        return;
    }
}

void Tree::printLeft(Node *leaf) {  //  print the left nodes
    if(leaf)
    {
        if(leaf->left) {
            printLeft(leaf->left);
        }

        if (leaf->left) {
            cout << leaf->left->data;
        }
        else {  //  the left node is null
            cout << leaf->left;
        }
        if (leaf->data != maxN) {
            cout << " ";
        }

        if(leaf->right) {
            printLeft(leaf->right);
        }
    }
    else {  //  the tree is null
        return;
    }
}

void Tree::printRight(Node *leaf) {  //  print the right nodes
    if(leaf)
    {
        if(leaf->left) {
            printRight(leaf->left);
        }

        if (leaf->right) {
            cout << leaf->right->data;
        }
        else {  //  the right node is null
            cout << leaf->right;
        }
        if (leaf->data != maxN) {
            cout << " ";
        }

        if(leaf->right) {
            printRight(leaf->right);
        }
    }
    else {  //  the tree is null
        return;
    }
}

void Tree::print(void) {  //  print the answer
    cout << "node: ";
    printNode(root);
    cout << "\nleft: ";
    printLeft(root);
    cout << "\nright: ";
    printRight(root);
}

int main(void) {
	Tree myTree;
	int n;
	bool first = true;

	while (cin >> n) {  //  input positive numbers
		if (n == -1) {  //  ends with a number -1
            if (first) {  //  no new lines before the first test case
                first = false;
            }
            else {
                cout << endl << endl;  //  two cases are separated by a new line
            }
            myTree.print();  //  print the answer
            myTree.clean();  //  reset myTree
			continue;
		}

		if (!myTree.rm(n)) {  //  For each number n, search n in the binary search tree.
            myTree.in(n);   //  If n is already in the tree, which means that n has appeared for 2n+1 times, then the node n should be removed.
		}                  //  Otherwise, a new node for n should be inserted into the binary tree, because n appeared 2n times before (n may be zero).
	}

    return 0;
}
