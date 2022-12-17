#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include<iostream>
#include<math.h>
using namespace std;

template <class T>
class AVLTree {
private:
    struct Node{
        T data;
        int height;
        Node* left;
        Node* right;
        Node(T data, int height = 1, Node* left = nullptr, Node* right = nullptr){
            this->data = data;
            this->height = height;
            this->left = left;
            this->right = right;
        }
    };
    Node* root;
    int nums;
public:
    AVLTree(){
        root = nullptr;
        nums = 0;
    }
    
    int height(Node *node){
        if (node == nullptr) return 0;
        return node->height;
    }

    void RightRotate(Node *&node){
        Node* temp = node->left;
        Node* sub = temp->right;
        temp->right = node;
        node->left = sub;
        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        node = temp;
    }

    void LeftRotate(Node *&node){
        Node* temp = node->right;
        Node* sub = temp->left;
        temp->left = node;
        node->right = sub;
        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        node = temp;
    }

    int balanceMetric(Node *temp){
        if (temp == nullptr) return 0;
        return height(temp->left) - height(temp->right);
    }

    void balance(Node* &temp){
        int balance = balanceMetric(temp);
        int balanceL = balanceMetric(temp->left);
        int balanceR = balanceMetric(temp->right);
        if (balance > 1 && balanceL>=0) RightRotate(temp);
        else if (balance < -1 && balanceR<=0) LeftRotate(temp);
        else if (balance > 1 && balanceL<0){
            LeftRotate(temp->left);
            RightRotate(temp);
        }
        else if (balance < -1 && balanceR>0){
            RightRotate(temp->right);
            LeftRotate(temp);
        }
    }

    void insertRec(Node *&node, T data){
        if (!node) {node = new Node(data); nums++;}
        else{
            if (data < node->data) insertRec(node->left, data);
            else insertRec(node->right, data);
        }
        node->height = 1 + max(height(node->left), height(node->right)); 
        balance(node);
    }

    void insert(T data){
        insertRec(root, data);
    }

    void removeRec(Node *&node, T data){
        if (!node) return;
        if (data<node->data) removeRec(node->left, data);
        else if (data>node->data) removeRec(node->right, data);
        else{
            if (node->left == nullptr){
                Node* temp = node;
                node = node->right;
                delete temp; nums--;
            }
            else if (node->right == nullptr){
                Node* temp = node;
                node = node->left;
                delete temp; nums--;
            }
            else{
                Node* temp = node->left;
                while (temp->right!=nullptr) temp = temp->right;
                node->data = temp->data;
                removeRec(node->left, temp->data);
            }
        }
        if (node!=nullptr){
            node->height = 1 + max(height(node->left), height(node->right));
            balance(node);
        }
    }

    void remove(T data){
        removeRec(root, data);
        if (nums == 0) root = nullptr;
    }

    bool searchRec(Node* node, T value){
        if (!node) return false;
        if (value<node->data) return searchRec(node->left, value);
        else if (value>node->data) return searchRec(node->right, value);
        else return true;
    }

    bool search (T value){
        return searchRec(root, value);
    }

    void displayRec(Node* node, int space) {
        if (!node) return;
        space += 10;
        displayRec(node->right, space);
        cout << endl;
        for (int i = 10; i < space; i++) cout<<" ";
        cout<<node->data<<endl; 
        displayRec(node->left, space);
    }

    void display() {
        displayRec(root, 0);
    }
    
    int size() const{
        return nums;
    }
};

#endif