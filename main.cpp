/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yuchen
 *
 * Created on January 19, 2017, 4:34 PM
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/*
 * 
 */

struct Node{
    int value;
    Node* left;
    Node* right;
    
    Node(int value){
        this->value = value;
        left = right = nullptr;
    }
};

class Tree{
    Node * root;
    
    void insert(Node* node, int value){
        if(node == nullptr){
            node = new Node(value);
        } else {
            if( value > node->value ){
                if(node->right == nullptr){
                    node->right = new Node(value);
                } else {
                    insert(node->right, value);
                }
            } else {
                if(node->left == nullptr){
                    node->left = new Node(value);
                } else {
                    insert(node->left, value);
                }
            }
        }
    }

    void traversePreorder(Node * node){
        if(node != nullptr){
            cout << node->value << " ";
            traversePreorder(node->left);
            traversePreorder(node->right);
        }
    }
    
    void traverseInorder(Node * node){
        if(node != nullptr){
            traverseInorder(node->left);
            cout << node->value << " ";
            traverseInorder(node->right);
        }
    }
    
    void traversePostorder(Node * node){
        if(node != nullptr){
            traversePostorder(node->left);
            traversePostorder(node->right);
            cout << node->value << " ";
        }
    }
    
    Node* search(Node* node, int value){
        if(node != nullptr){
            if(node->value == value){
                return node;
            } else if (value > node->value) {
                return search(node->right, value);
            } else {
                return search(node->left, value);
            }
        }
        return nullptr;
    }
    
    int getMaxDepth(Node* node){
        if(node == nullptr){
            return 0;
        } else {
            return max(getMaxDepth(node->left), getMaxDepth(node->right)) + 1;
        }
    }
    
    void destroyTree(Node * node){
        if(node != nullptr){
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
public:
    Tree():root(nullptr){}
    
    Tree(vector<int> & arr):Tree(){
        for(auto value : arr){
            insert(value);
        }
    }
    
    void insert(int value){
        if(root == nullptr){
            root = new Node(value);
        } else {
            insert(root, value);
        }
    }
    
    void traversePreorder(){
        traversePreorder(root);
    }
    
    void traversePostorder(){
        traversePostorder(root);
    }
    
    void traverseInorder(){
        traverseInorder(root);
    }
    
    Node* search(int value){
        return search(root, value);
    }
    
    Node* depthFirstSearch(int value){
        stack<Node *> stk;

        if(root != nullptr){
            stk.push(root);
            
            while(!stk.empty()){
                Node* currentNode = stk.top();
                stk.pop();
                
                cout << currentNode->value << "-";
                
                if(currentNode->value == value){
                    cout << endl;
                    return currentNode;
                } else {
                    if(currentNode->right != nullptr){
                        stk.push(currentNode->right);
                    }
                    if(currentNode->left != nullptr){
                        stk.push(currentNode->left);
                    }
                }
            }
        } else {
            cout << endl;
            return nullptr;
        }
    }
    
    Node* breadthFirstSearch(int value){
        queue<Node *> que;

        if(root != nullptr){
            que.push(root);
            
            while(!que.empty()){
                Node* currentNode = que.front();
                que.pop();
                
                cout << currentNode->value << "-";
                
                if(currentNode->value == value){
                    cout << endl;
                    return currentNode;
                } else {
                    if(currentNode->left != nullptr){
                        que.push(currentNode->left);
                    }
                    if(currentNode->right != nullptr){
                        que.push(currentNode->right);
                    }
                }
            }
        } else {
            cout << endl;
            return nullptr;
        }
    }
    
    int getMaxDepth(){
        return getMaxDepth(root);
    }
    
    ~Tree(){
        destroyTree(root);
    }
};

int main(int argc, char** argv) {

    int values[] = {5, 3, 7, 1, 4, 0, 2, 6, 9, 8, 10};
    vector<int> vect(values, values + 11);
    
    Tree tree(vect);
    
    tree.traversePreorder();
    cout << endl;
    
    tree.traverseInorder();
    cout << endl;
    
    tree.traversePostorder();
    cout << endl;
    
    Node * result = tree.search(10);
    if(result != nullptr)
        cout << result->value << endl;
    else
        cout << "No result" << endl;
    
    result = tree.search(11);
    if(result != nullptr)
        cout << result->value << endl;
    else
        cout << "No result" << endl;
    
    cout << tree.getMaxDepth() << endl;
    
    result = tree.depthFirstSearch(9);
    if(result != nullptr)
        cout << result->value << endl;
    else
        cout << "No result" << endl;
    
    result = tree.breadthFirstSearch(9);
    if(result != nullptr)
        cout << result->value << endl;
    else
        cout << "No result" << endl;
    
    Tree* tr = new Tree(vect);
    result = tr->breadthFirstSearch(9);
    if(result != nullptr)
        cout << result->value << endl;
    else
        cout << "No result" << endl;
    delete tr;
    
    return 0;
}

