#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class AVLNode {
public:
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const T& value) : data(value) {
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

template <typename T, typename Comparator>
class CustomAVLTree {
private:
    AVLNode<T>* root;
    Comparator comp;

    int getHeight(AVLNode<T>* node){
        if(node == nullptr){
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(AVLNode<T>* node){
        if(node == nullptr){
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode<T>* node){
        if(node == nullptr){
            return;
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y){
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x){
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, const T& value){
        if(node == nullptr){
            return new AVLNode<T>(value);
        }
        if(comp.compare(value, node->data)){
            node->left = insertNode(node->left, value);
        }
        else if(comp.compare(node->data, value)){
            node->right = insertNode(node->right, value);
        }
        else{
            return node;
        }
        updateHeight(node);
        int balance = getBalanceFactor(node);
        if(balance > 1 && comp.compare(value, node->left->data)){
            return rotateRight(node);
        }
        if(balance < -1 && comp.compare(node->right->data, value)){
            return rotateLeft(node);
        }
        if(balance > 1 && comp.compare(node->left->data, value)){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if(balance < -1 && comp.compare(value, node->right->data)){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void inorderTraversal(AVLNode<T>* node, vector<T>& result, int& count, int maxCount){
        if(node == nullptr || (maxCount != -1 && count >= maxCount)){
            return;
        }
        inorderTraversal(node->left, result, count, maxCount);
        if(maxCount == -1 || count < maxCount){
            result.push_back(node->data);
            count++;
        }
        inorderTraversal(node->right, result, count, maxCount);
    }
    bool searchNode(AVLNode<T>* node, const T& value){
        if(node == nullptr){
            return false;
        }
        if(comp.compare(value, node->data)){
            return searchNode(node->left, value);
        }
        else if(comp.compare(node->data, value)){
            return searchNode(node->right, value);
        }
        else{
            return true;
        }
    }

    void destroyTree(AVLNode<T>* node){
        if(node != nullptr){
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    CustomAVLTree(){
        root = nullptr;
    }

    ~CustomAVLTree(){
        destroyTree(root);
    }

    void insert(const T& value){
        root = insertNode(root, value);
    }

    vector<T> getElements(int n = -1){
        vector<T> result;
        int count = 0;
        inorderTraversal(root, result, count, n);
        return result;
    }

    bool contains(const T& value){
        return searchNode(root, value);
    }
};

#endif
