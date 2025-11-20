#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int findDepth(Node* root);


bool equalPaths(Node * root)
{
    // Add your code below

    /*
    here's maybe how i'd do it. In my main function, i'll first go ahead and call my helper function.
         This helper function would take an argument of a pointer to a node. 
         The helper function would internally would recurse and evaluate at each node and subtree and eventually return an int depth of the subtree with left or right child as the root/arg
    I would call the helper function twice, one for the left child of the root and the other for the right child of the root. Return depth of the main function where i would then assign the return values to two variabls to compare. 
    If the variables ==, 
        then return true, 
        if not, false
    */

    //trivially true if no tree
    if(root == NULL){
        return true;
    }

    else if(root->left == NULL && root->right == NULL){
        return true;
    }

    int leftTree = 0;
    int rightTree = 0;

    //if there is a left sub tree.. but no right, we have to check if there is a subtree at the left child
    if(root->left != NULL && root->right == NULL){
        return equalPaths(root->left);
    }
    //if there is a right sub tree.. but no left, we have to check if there is a subtree at the left child
    else if(root->right != NULL && root->left == NULL){
        return equalPaths(root->right);
    }

    //else if both exist, check the depths of both subtrees and compare depths
    leftTree = findDepth(root->left);
    rightTree = findDepth(root->right);

    //compare the depths at right and left, return bool
    return (leftTree == rightTree);    
}

int findDepth(Node* root){
    int rightSubtree = 0;
    int leftSubtree = 0;


    //if no children at root (null), then return depth + 1 (meaning one node depth which is the root node itself)
    if(root->left == NULL && root->right == NULL){
        return 1;
    }

    //else if children exist, recurse downward
    else{
        if(root->left != NULL){
            leftSubtree = findDepth(root->left);
        }
        if(root->right != NULL){
            rightSubtree = findDepth(root->right);
        }


    }   

    //while traversing from either right or left, if we detect a mismatch in depth early in a sub tree
    if(rightSubtree == -1 || leftSubtree == -1){
        return -1;
    }

    //traversing up one child
    if(rightSubtree == 0 && leftSubtree != 0){
        return leftSubtree+1;
    }
    if(rightSubtree != 0 && leftSubtree == 0){
        return rightSubtree+1;
    }
    

    //traversing back up from both children
    if(rightSubtree == leftSubtree){
        return leftSubtree+1;
    }


    return -1;
}
