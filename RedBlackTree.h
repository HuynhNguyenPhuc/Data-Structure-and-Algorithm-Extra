#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

#include<iostream>
#include<math.h>
using namespace std;

template <class T>
class RedBlackTree{
    private:
        struct Node{
            T data;
            bool color; // BLACK: false, RED: true
            Node* left;
            Node* right;
            Node* parent;
            Node(T data, bool color = false, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr){
                this->data = data;
                this->color = color;
                this->parent = parent;
                this->left = left;
                this->right = right;
            }
        };
        Node* root;
        bool ll;
        bool rr;
        bool lr;
        bool rl;
    private:
        string getColor(Node* node) {
            if (node->color == true)
                return "R";
            return "B";
        }
        void displayRec(Node* node, int space) {
            if (!node) return;
            space += 10;
            displayRec(node->right, space);
            cout << endl;
            for (int i = 10; i < space; i++) cout<<" ";
            cout<<node->data<<" ("<<getColor(node)<<") "<<endl; 
            displayRec(node->left, space);
        }
             
        bool searchRec(Node* node, T value){
            if (!node) return false;
            if (value<node->data) return searchRec(node->left, value);
            else if (value>node->data) return searchRec(node->right, value);
            else return true;
        }
        
        Node* rotateRight(Node * node){
            Node *temp = node->left; // Left child of node 
            Node *sub = temp->right; // Right child of left node
            Node *par= node->parent; // Parent of node
            if (par){
                if (par->left == node) par->left = temp;
                else par->right = temp;
            } // Update chill for parent
            else{
                this->root = temp;
            } // If node->parent is nullptr, node is this->root, so we update root.
            // Rotate right
            temp->right = node;
            node->left = sub;
            // Update parent
            if (sub) sub->parent = node;
            temp->parent = par;
            node->parent = temp;
            return temp;
        }
        Node* rotateLeft(Node * node){
            Node *temp= node->right; // Right child of node
            Node *sub = temp->left; // left child of right node
            Node *par = node->parent; // Parent of node
            if (par){
                if (par->left == node) par->left = temp;
                else par->right = temp;
            } // Update chill for parent
            else{
                this->root = temp;
            } // If node->parent is nullptr, node is this->root, so we update root.
            // Rotate left
            temp->left = node;
            node->right = sub;
            // Update parent
            if (sub) sub->parent = node;
            temp->parent = par;
            node->parent = temp;
            return temp;
        }
        Node* insertRec(Node* node, int data) {
            bool check = false; // check = true when RED-REC conflict occurs
            if (data < node->data) {
                if (node->left) insertRec(node->left, data);
                else node->left = new Node(data, true, node, nullptr, nullptr);
                // New node has RED color
                if (node != this->root) {
                    if (node->color && node->left->color) check = true;
                }
            }
            else {
                if (node->right) insertRec(node->right, data);
                else node->right = new Node(data, true, node, nullptr, nullptr);
                // New node has RED color
                if (node != this->root) {
                    if (node->color && node->right->color) check = true;
                }
            }
            // Four imbalance cases in Red parent - Black uncle
            // Case 1 : Left Left - Trái trái
            if (ll) {
                node = rotateRight(node);
                node->color = false;
                node->right->color = true;
                ll = false;
            }
            // Case 2 : Right Right - Phải phải
            else if (rr) {
                node = rotateLeft(node);
                node->color = false;
                node->left->color = true;
                rr = false;
            }
            // Case 3 : Left Right - Phải trái
            else if (lr) {
                node->left = rotateLeft(node->left);
                node = rotateRight(node);
                node->color = false;
                node->right->color = true;
                lr = false;
            }
            // Case 4 : Right Left
            else if (rl) {
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
                node->color = false;
                node->left->color = true;
                rl = false;
            }

            // Handle RED-RED conflict
            // In this case, this node is parent, node's parent is grandparent.
            if (check) {
                if (node->parent->right == node) { // Parent is grandparent's right child
                    if (!node->parent->left || !node->parent->left->color) {
                        // Red parent - black uncle (rr or rl)
                        if (node->left && node->left->color) rl = true;
                        if (node->right && node->right->color) rr = true;
                    }
                    else {
                        // Red parent - red uncle
                        node->color = node->parent->left->color = false; // Parent, Uncle: BLACK
                        if (node!=this->root) node->parent->color = true; // Grandparent: RED
                    }
                }
                else { // Parent is grandparent's left child
                    if (!node->parent->right || !node->parent->right->color) {
                        // Red parent - black uncle (ll or lr)
                        if (node->left && node->left->color) ll = true;
                        if (node->right && node->right->color) lr = true;
                    }
                    else {
                        // Red parent - red uncle
                        node->color = node->parent->right->color = false; // Parent, Uncle: BLACK
                        if (node!=this->root) node->parent->color = true; // Grandparent: RED
                    }
                }
                check = false;
            }
            return node;
        }
        Node* sibling(Node* node) {
            if (!node->parent) return nullptr;
            if (node->parent->left == node) return node->parent->right;
            return node->parent->left;
        }
        bool hasRedChild(Node* node) {
            if (node->left){
                if (node->left->color) return true;
            }
            if (node->right){
                if (node->right->color) return true;
            }
            return false;
        }
        Node* maxValueLeftSubtree(Node* node){
            Node* temp = node->left;
            while (temp->right) temp = temp->right;
            return temp;            
        }
        void fixDoubleBlack(Node* node) {
            if (node == this->root) return;
            Node* sib = sibling(node);
            Node* par = node->parent;
            if (!sib) fixDoubleBlack(par);
            else {
                if (sib->color == true) {
                    par->color = true;
                    sib->color = false;
                    if (sib->parent->left == sib) par = rotateRight(par);
                    else par = rotateLeft(par);
                    fixDoubleBlack(node);
                }
                else {
                    if (hasRedChild(sib)) {
                        if (sib->parent->left == sib) {
                            if (sib->left != nullptr && sib->left->color) {
                                sib->left->color = sib->color;
                                sib->color = par->color;
                                par->color = false;
                                par = rotateRight(par);
                            }
                            else {
                                sib->right->color = par->color;
                                par->color = false;
                                sib = rotateLeft(sib);
                                par = rotateRight(par);
                            }
                        }
                        else {
                            if (sib->right != nullptr && sib->right->color) {
                                sib->right->color = sib->color;
                                sib->color = par->color;
                                par->color = false;
                                par = rotateLeft(par);
                            }
                            else {
                                sib->left->color = par->color;
                                par->color = false;
                                sib = rotateRight(sib);
                                par = rotateLeft(par);
                            }
                        }
                    }
                    else {
                        sib->color = true;
                        if (!par->color) fixDoubleBlack(par);
                        else par->color = false;
                    }
                }
            }
        }
        Node* searchNodeRec(Node* node, T value){
            if (!node) return nullptr;
            if (value<node->data) return searchNodeRec(node->left, value);
            else if (value>node->data) return searchNodeRec(node->right, value);
            else return node;
        }
        Node* searchNode (T value){
            return searchNodeRec(root, value);
        }
        void removeRec(Node* node){
            Node* replace = nullptr;
            if (!node->left) replace = node->right;
            else if (!node->right) replace = node->left;
            else replace = maxValueLeftSubtree(node);
            bool doubleBlack = ((!replace) || (!replace->color)) && (!node->color);
            Node* par = node->parent;
            Node* sib = sibling(node);
            if (!replace) {
                if (node == this->root) this->root = nullptr;
                else {
                    if (doubleBlack) fixDoubleBlack(node);
                    else if (sib) sib->color = true;
                    if (node->parent->left == node) par->left = NULL;
                    else par->right = NULL;
                }
                delete node;
                return;
            }
        
            if (!node->left || !node->right) {
                if (node == this->root) {
                    node->data = replace->data;
                    node->left = node->right = NULL;
                    delete replace;            
                }
                else {
                    if (node->parent->left == node) par->left = replace;
                    else par->right = replace;
                    delete node;
                    replace->parent = par;
                    if (doubleBlack) fixDoubleBlack(replace);
                    else replace->color = false; 
                }
                return;
            }
            node->data = replace->data; // Replace node->data with replace->data;
            removeRec(replace); // Then delete node replace;
        }
        void deleteNode(Node* node){
            if (!node) return;
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }
    public:
        RedBlackTree(){
            root = nullptr;
            ll = rr = lr = rl = false;
        }
        bool search (T value){
            return searchRec(root, value);
        }
        
        void insert(int data) {
            if (root == nullptr) {
                root = new Node(data, 0, nullptr, nullptr, nullptr);
            }
            else {
                root =  insertRec(root, data);
                if (root->color == true) root->color = false;
            }
        }
        void remove(T value){
            Node* temp = searchNode(value);
            if (!temp) return;
            else removeRec(temp);
        }
        
        void display() {
            displayRec(root, 0);
        }
        ~RedBlackTree(){
            deleteNode(this->root);
            this->root = nullptr;
        }
};

#endif