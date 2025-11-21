#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertfix(AVLNode<Key,Value>* parent_, AVLNode<Key,Value>* node);
    void rotateRight(AVLNode<Key, Value>* parentOfNodeRotate);
    void rotateLeft(AVLNode<Key, Value>* parentOfNodeRotate);
    void removeFix(AVLNode<Key, Value>* delNode, int diff); 

};

/*
I've written a bst tree, now i will write an avl tree. 
AVl tree and bst trees are similar except for the key property that avl trees are self balancing. 
Therefore after an insertion or removal, the avl tree must evaluate itself and determine if it is balance or not. 
    If the balance attribute is broken, we know that the balancing has been broken due to the latest removal or insertion and mumst recurse upward from the location of the modified node back up to the root and conduct rotations as needed along the way

*/

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //create a node to insert.
    if(root_ == NULL){
        root_ = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
        root_->setBalance(0);
        return;
    }
    else{
    //traverse the tree until we find the right parent to insert under.
        AVLNode<Key,Value>* foundParent = root_;
        AVLNode<Key, Value>* currChild = root_;
        Key workingKey = new_item.first;

        while(currChild != NULL){
            foundParent = currChild;
            if(workingKey == foundParent->getKey()){
                //update value
                foundParent->setValue(new_item.second);

                return;
            }
            else if(workingKey < foundParent->getKey()){

                currChild = foundParent->getLeft();
            }
            else if(workingKey > foundParent->getKey()){
                currChild = foundParent->getRight();
            }
        }
    //now insert under the foundParent
        AVLNode<Key, Value>* insertNode = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);   
        if(workingKey > foundParent->getKey()){
            insertNode->setParent(foundParent);
            foundParent->setRight(insertNode);  
        }
        else{
            insertNode->setParent(foundParent);
            foundParent->setLeft(insertNode);
        }
        insertNode->setBalance(0);

        if(foundParent->getBalance() == -1 || parent ->getBalance() ==1){
            foundParent->setBalance(0);
        }
        else if(foundParent->getBalance() == 0){
            if(foudnParent->getLeft() == insertNode){
                parent->setbalance(-1);
            }
            else{
                parent->setBalance(-1);
            }


        }
        insertfix(foundParent, insertNode);
    }

 return;
}

template<class Key, class Value>
void AVLTree<Key,Value>::insertfix(AVLNode<Key,Value>* parent_, AVLNode<Key,Value>* node){
    AVLNode<Key,Value>* parentOfParent = parent->getParent();
    if(parentOfParent == NULL || parent == NULL){
        //if one of these is null, then there are only two nodes connected and cannot cause a height imbalance
        //no action needed.
        return;
    }
    int balanceOfGrandparent = parentOfParent->getBalance();
    if(parentOfParent->getLeft() == parent){
        //proceed to check if this is zig left or zig right,do bookkeeping
        parentOfParent->setBalance( balanceOfGrandparent- 1);
    }

    else{
        parentOfParent->setBalance(balanceOfGrandparent+1);

    }

    balanceOfGrandparent = parentOfParent->getBalance();
    
    if(balanceOfGrandparent == 0){
        //
        return;
    }

    if(balanceOfGrandparent == -1 || balanceOfGrandparent == 1){
        //if balancing is right or left heavy...
        insertFix(parentOfParent,parent);
    }

    else if(balanceOfGrandparent == -2){
        if(parentOfParent->getLeft() == parent && parent->getLeft() == node){
            //this is a zig-zig case and we rotate right
            rotateRight(parentOfParent);
            parent->setBalance(0);
            parentOfParent->setBalance(0);
        }
        else{
            //if otherwise, a zig zag case
            rotateLeft(parent);
            rotateRight(parentOfParent);
            if(node->getBalance() == -1){
                parent->setBalance(0);
                parentOfParent->setBalance(1);
            }
            else if(node->getBalance() == 0){
                parent->setBalance(0);
                parentOfParent->setBalance(0);
    
            }

            else{
                parent->setBalance(-1);
                parentOfParent->setBalance(0);
            }
            node->setBalance(0);
        }
        return;
    }

    else if (balanceOfGradparent == 2){
         if(parentOfParent->getRight() == parent && parent->getRight() == node){
            //this is a zig-zig case but we rotate left
            rotateLeft(parentOfParent);
            parent->setBalance(0);
            parentOfParent->setBalance(0);
        }
        else{
            //if otherwise, a zig zag case
            rotateRight(parent);
            rotateLeft(parentOfParent);
            if(node->getBalance() == 1){
                parent->setBalance(0);
                parentOfParent->setBalance(-1);
            }
            else if(node->getBalance() == 0){
                parent->setBalance(0);
                parentOfParent->setBalance(0);
    
            }

            else{
                parent->setBalance(1);
                parentOfParent->setBalance(0);
            }
            node->setBalance(0);
        }
        return;
    }


}
// template<class Key, class Value>
// int BinarySearchTree<Key,Value>::calcDepth(AVLNode<Key,Value>* current_) const{
//     //check the subtrees of the given node
//     int leftSubTree = 0;
//     int rightSubTree = 0;

//     if(current_ == NULL){
//         //no node given
//         return 0;
//     }



//     //by default, we want to return the greater of two subheights + 1 
//     //we calculate the difference earlier which if BALANCED shold always be less than 1
//     //we add one to include the node we are counting from 
//     return 
// }


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* delNode = root_;

    if(root_ == NULL){
        //nothing to be deleted
        return;
    }

    else{
        while(delNode != NULL && key != delNode->getKey()){
            //only exit loop if we've hit the bottom of the tree or if we've found the node
            if(key < delNode->getKey()){
                delNode = delNode->getLeft();
            }
            else if(key > delNode->getKey()){
                delNode = delNode->getRight();
            }
        }

    }
    //traverse nodes to find the correct key
    if(delNode == NULL){
        return;
    }

    AVLNode<Key, Value>* parentdelNode = delNode->getParent();
    int diff = 0;

    if (parentdelNode != NULL) {
        if(parentdelNode->getLeft() == delNode){
            diff = +1;
        }
        else{
            diff = -1;
        }
    }


    AVLNode<Key, Value>* childdelNode = NULL;
    //if delNode isn't NULL, implies we broke out the loop bc we found the right node
    /*
    now that i've done, the traversal, if delNode isn't a nullptr, it must mean that delNode points to a valid Node. Now we need to find out how many children exist to do the right operations. 
        If both children exist, we need to swap with the predecessor and so on. 
        If one of them exist, then we need to find out which of them exists and swap with them. 
        If neither exist, delete
    */
    if(delNode->getRight() != NULL && delNode->getLeft() != NULL){
        AVLNode<Key,Value>* predecessorNode = predecessor(delNode);
        nodeSwap(delNode, predecessorNode); //swap positions

        if(parentdelNode != NULL){
            if(parentdelNode->getLeft() == delNode){
                diff = diff + 1;

            }
            else{
                diff = diff - 1;
            }
        }
    }

    if(delNode->getRight() != NULL || delNode->getLeft() != NULL){
        //after swapping with the predecessor, it's guaranteed that the delNode will have 0 or 1 child
        //find which node exists under delNode
        if(delNode->getRight() != NULL){
            childdelNode = delNode->getRight();
        }
        else if(delNode->getLeft() != NULL){
            childdelNode = delNode->getLeft();
        }

        //prepare to perform delNode and delNode pointer swapping
        parentdelNode = delNode->getParent();
        childdelNode->setParent(parentdelNode);

        //if parent is null, delNode must be a root, it's child is therefore the new root
        if(parentdelNode == NULL) {
            root_ = childdelNode;
        }
        else if(parentdelNode->getRight() == delNode){
            //if delNode is a right child of it's parent, replace it with it's child 
            parentdelNode->setRight(childdelNode);
        }
        else if(parentdelNode->getLeft() == delNode){
            //if delNode is a left child of it's parent, replace it with it's child
            parentdelNode->setLeft(childdelNode);

        }   

    }      
    else{
        //leaf case, handle setting parent of del node to null
        parentdelNode = delNode->getParent();
        if(parentdelNode == NULL){
            root_ = NULL;
        }
        else if(parentdelNode->getLeft() == delNode){
            parentdelNode->setLeft(NULL);
        }
        else{
            parentdelNode->setRight(NULL);
        }
        
    }  
    



    //delete, if the to be deleted node does not have any children, it's safe to delete and skip above if-condition block
    delete delNode;

    if(parentdelNode != NULL){
        removeFix(parentdelNode, diff);
    }
    return;

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* delNode, int diff) 
{
    if (delNode == nullptr) {
        return;
    }
    
    AVLNode<Key, Value>* parent = delNode->getParent();
    int8_t newDiff = 0;

    if (parent != NULL) {
        if (parent->getLeft() == delNode) {
            newDiff = 1;
        } else {
            newDiff = -1;
        }
    }
    if (node->getBalance() + diff == -2) { 
        //when the tree is left heavy...
        AVLNode<Key, Value>* child = delNode->getLeft();
        if (child->getBalance() == -1) { 
            //balance is -1, we do zig zig rotate right to fix left left
            rotateRight(delNode);

            child->setBalance(0);
            delNode->setBalance(0);

            removeFix(parent, newDiff);
        } 
        else if (child->getBalance() == 0) { 
            //balance is 0, rotate once so that delnode and it's child is children to delnode parent
            rotateRight(delNode);
            child->setBalance(1);
            delNode->setBalance(-1);

            return;
        } 
        else if (child->getBalance() == 1) { //Case 1c
            //zig zag rotation cause child balance indicaes it as right child
            //do left right rotation depending on grandchild
            AVLNode<Key, Value>* grandChild = child->getRight();
            rotateLeft(child);
            rotateRight(delNode);
            if (grandChild->getBalance() == 1) {
                delNode->setBalance(0);
                child->setBalance(-1);

                grandChild->setBalance(0);
            } 
            else if (grandChild->getBalance() == 0) {

                delNode->setBalance(0);
                child->setBalance(0);

                grandChild->setBalance(0);
            } 
            else if (grandChild->getBalance() == -1) {
                delNode->setBalance(1);
                child->setBalance(0);

                grandChild->setBalance(0);
            }
        removeFix(parent, newDiff);
        }
    } 


    else if (delNode->getBalance() + diff == -1) {
        //if the balance after adding the difference to the to be deleted node is under 2, we're still good
        delNode->setBalance(-1);

        return;
    } 

    else if (delNode->getBalance() + diff == 1) {
        delNode->setBalance(1);

        return;
    } 

    else if (delNode->getBalance() + diff == 0) {
        //make sure that the rest of the tree isn't unbalanced above bc the height is -1 now since it's a perfect rotate
        delNode->setBalance(0);
        removeFix(parent, newDiff);
    } 


    //we just mirror again copy and paste but opposite rotations for the right heavy case
    
     if (node->getBalance() + diff == 2) { 
        //when the tree is right heavy...
        AVLNode<Key, Value>* child = delNode->getRight();
        if (child->getBalance() == -1) { 
            //balance is -1, we do zig zig rotate left to fix right right
            rotateLeft(delNode);

            child->setBalance(0);
            delNode->setBalance(0);

            removeFix(parent, newDiff);
        } 
        else if (child->getBalance() == 0) { 
            //balance is 0, rotate once so that delnode and it's child is children to delnode parent
            rotateLeft(delNode);
            child->setBalance(1);
            delNode->setBalance(-1);

            return;
        } 
        else if (child->getBalance() == -1) { //Case 1c
            //zig zag rotation cause child balance indicaes it as left child
            //do right left rotation depending on grandchild
            AVLNode<Key, Value>* grandChild = child->getLeft();
            rotateRight(child);
            rotateLeft(delNode);
            if (grandChild->getBalance() == -1) {
                delNode->setBalance(0);
                child->setBalance(1);

                grandChild->setBalance(0);
            } 
            else if (grandChild->getBalance() == 0) {

                delNode->setBalance(0);
                child->setBalance(0);

                grandChild->setBalance(0);
            } 
            else if (grandChild->getBalance() == 1) {
                delNode->setBalance(-1);
                child->setBalance(0);

                grandChild->setBalance(0);
            }
        removeFix(parent, newDiff);
        }
    } 


    
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* parentOfNodeRotate){
    AVLNode<Key, Value>* parent = parentOfNodeRotate->getLeft(); //Get parent

    parentOfNodeRotate->setLeft(parent->getRight()); //Set grandparent's right to parent's left
    
    if (parent->getRight() != nullptr) {
        parent->getRight()->setParent(parentOfNodeRotate);
    }
    parent->setParent(parentOfNodeRotate->getParent()); 

    //If the parent is the root, then we just need to  update root,
    //if not update great grandparent to child
    if (parent->getParent() == nullptr) {
        this->root_ = parent;
    } 
    else if (parentOfNodeRotate == parentOfNodeRotate->getParent()->getLeft()){
        parentOfNodeRotate->getParent()->setLeft(parent);
    } 
    else if (parentOfNodeRotate == parentOfNodeRotate->getParent()->getRight()) {
        parentOfNodeRotate->getParent()->setRight(parent);
    }

    //Update parent and grandparent relation
    parent->setRight(parentOfNodeRotate);
    grandparent->setParent(parent); 
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* parentOfNodeRotate)
{
    AVLNode<Key, Value>* parent = parentOfNodeRotate->getRight(); //Get parent

    parentOfNodeRotate->setRight(parent->getLeft()); 

    if (parent->getLeft() != nullptr) {
        parent->getLeft()->setParent(parentOfNodeRotate);
    }
    parent->setParent(parentOfNodeRotate->getParent()); //set parent to grandparent old position
    

    //If the parent is the root, then we just need to  update root,
    //if not update great grandparent to child
    if (parent->getParent() == nullptr) {
        this->root_ = parent;
    } 
    else if (parentOfNodeRotate == grandparent->getParent()->getLeft()){
        parentOfNodeRotate->getParent()->setLeft(parent);
    } 
    else if (parentOfNodeRotate == parentOfNodeRotate->getParent()->getRight()) {
        parentOfNodeRotate->getParent()->setRight(parent);
    }

    parent->setLeft(parentOfNodeRotate);
    parentOfNodeRotate->setParent(parent);

    
}


#endif
