#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

#include <algorithm>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{



}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here

    int calcDepth(Node<Key,Value>* current_) const;
    void clearWithArg(Node<Key,Value>* current_);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
    
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
  
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    /*
    In-order processing describes, traversing left node, root, then right node
    always go from the root in counterclockwise direction around the tree. 

    Inorder, left, node, then right (visit literally in order)
    Pre order, left, right, node (down up tree)
    Post order, node, left right (top down tree)

    In this function, we are incrementing forward and thus we are looking for the SUCCESSOR 
    to the current node.

    BST are for ordered nodes, imagine we spread out bst into a line of subsequent nodes
        In this visualization, we are spreading out the branches of each node 
            the left spread to the left, right spread to the right.

          8
         / \
        3   10
       /\    \
      1  6    14
        / \   /\
       4   7 13 20
                /
               18
    Spreads out into 
    1-3-(4-6-7)-8-10-(13-14)

        The sucessor is defined to be the left most node in a right subtree. 
    If the right subtree does not exist,
    traverse upward thru parents until we find the first node that is a left child to a 
    parent. The parent of left child is the sucessor.
    

    */

    if(current_->getRight() != NULL){
        current_ = current_->getRight();
        //find left most node in current right subtree
        while( current_->getLeft() != NULL){
            current_ = current_->getLeft();
        }
    }
    else{
        Node<Key, Value>* parent  = current_->getParent();
        while((parent != NULL) &&  current_ == parent->getRight() ){
            current_ = parent;
            parent = parent->getParent();
        }
        current_ = parent;
    }
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    /* 
    We should deallocate nodes from the bottom up.
    dealloc right or left child if they exist before deleting the parent
        This is pre-order traversal (children then parents, bottom-up traversal)

    To do this, I should probably make a recursive helper function that recurses downward
    Then as we go up the tree, do our dealloc operations there
    this is the clear function already protoyped


    */



    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //create a node to insert.
    if(root_ == NULL){
        root_ = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, NULL);
        root_->setLeft(NULL);
        root_->setRight(NULL);
        return;
    }
    else{
    //traverse the tree until we find the right parent to insert under.
        Node<Key,Value>* foundParent = root_;
        Node<Key, Value>* currChild = root_;
        Key workingKey = keyValuePair.first;

        while(currChild != NULL){
            foundParent = currChild;
            if(workingKey == foundParent->getKey()){
                //update value
                currChild->setValue(keyValuePair.second);
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
        Node<Key, Value>* insertNode = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, NULL);   
        if(workingKey > foundParent->getKey()){
            insertNode->setParent(foundParent);
            foundParent->setRight(insertNode);
        }
        else{
            insertNode->setParent(foundParent);
            foundParent->setLeft(insertNode);
        }
    }

 return;
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* delNode = root_;

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

    
    if(delNode != NULL){
        Node<Key, Value>* parentdelNode = NULL;
        Node<Key, Value>* childdelNode = NULL;
        //if delNode isn't NULL, implies we broke out the loop bc we found the right node
        /*
        now that i've done, the traversal, if delNode isn't a nullptr, it must mean that delNode points to a valid Node. Now we need to find out how many children exist to do the right operations. 
            If both children exist, we need to swap with the predecessor and so on. 
            If one of them exist, then we need to find out which of them exists and swap with them. 
            If neither exist, delete
        */
        if(delNode->getRight() != NULL && delNode->getLeft() != NULL){
            Node<Key,Value>* predecessorNode = predecessor(delNode);
            nodeSwap(delNode, predecessorNode); //swap positions
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
        
    }


    //delete, if the to be deleted node does not have any children, it's safe to delete and skip above if-condition block
    delete delNode;
    return;
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    /*
    The predecessor at a given node is the right most node in the left subtree
        If the left subtree does not exist
            walk up parents until you find a node that is the right child to it's parent, the parent is the predecessor
    */
    if (current == NULL) {
        return NULL;
    }
    Node<Key, Value>* parent = current->getParent();
    if(current->getLeft() != NULL){
        current = current->getLeft();
        while(current->getRight() != NULL){
            current = current->getRight();
        }
        return current;
    }
    while((parent != NULL) && (current == parent->getLeft())){
        current = parent;
        parent = parent->getParent();
    }
        return parent;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearWithArg(root_);
    root_ = NULL;
    return;
}

template<typename Key, typename Value>
void BinarySearchTree<Key,Value>::clearWithArg(Node<Key,Value>* current_){
    if(current_ == NULL){
        return;
    }

    //traverse downward thru the tree 
    clearWithArg(current_->getLeft());
    clearWithArg(current_->getRight());

    
    delete current_;
    return;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    /*
    To retrieve smallest node
    the left child will always be the smallest of the children
    Keep traversing into the left child until you reach a left child with no more children
        - This must be the smallest value, and also the "left-most" leaf
    */
   Node<Key, Value>* current_ = root_;
    if (current_ == NULL){
      return NULL;
    }
   while(current_->getLeft() != NULL){
    current_ = current_->getLeft();
   }
   return current_;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    /*
    To find a node with a given key, traverse using the node.
        - Is the key the same as the current node? 
            - True?  i'm done
            - False? need to traverse children
        - Is the key larger than the current node?
            - True? traverse rightward
            - Else? Traverse leftward 
                - (the key is smaller than the current node)
                - All smaller children are left children 
    
    */

    Node<Key, Value>* current_ = root_;
    while(current_ != NULL){
        if(current_->getKey() == key){
            return current_;
        }
        else if(current_->getKey() < key){
            current_= current_->getRight();
        }
        else if(current_->getKey() > key){
            current_ = current_->getLeft();
        }
    }

    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    /*
    A BST is balanced IF at EVERY node in the tree
        - The height difference between the left and right subtrees are no MORE than 1
        - USED IN AVL AS WELL 
            - Balance: Define b(n) as the balance of a node = Right – Left Subtree Height
            - In this way, 
            - If balance > -1, left height > right height, tree at node is left-heavy
            - If balance > 1, right height > left height, tree at node is roght-heavy

            Implementation
            Recurse down to all leaf nodes, and at each recursive call, call helper to check the heights of subtrees. 
                - leaf nodes have no subtrees, therefore their heights = 1

    */
       // Add your code below
       
    //calc depth only returns -1 IF unbalanced.
    if(calcDepth(root_) == -1){
      return false;
    }
    return true;
}




template<typename Key, typename Value>
int BinarySearchTree<Key,Value>::calcDepth(Node<Key,Value>* current_) const{
    //check the subtrees of the given node
    int leftSubTree = 0;
    int rightSubTree = 0;

    if(current_ == NULL){
        //no node given
        return 0;
    }

    //check if one of the subtrees came back as BAD.
    leftSubTree = calcDepth(current_->getLeft());
    if(leftSubTree == -1){
        return -1;
    }
    rightSubTree = calcDepth(current_->getRight());
    if( rightSubTree == -1){
       
        return -1;
    }

    if(abs(rightSubTree - leftSubTree) > 1){
        //calculate the difference, if exceed a difference of 1, return -1 to signal BAD(unbalanced) subtree.
        return -1;
    }

    //by default, we want to return the greater of two subheights + 1 
    //we calculate the difference earlier which if BALANCED shold always be less than 1
    //we add one to include the node we are counting from 
    if(leftSubTree > rightSubTree){
      return leftSubTree + 1;
    }
    return 1 + rightSubTree;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}



/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
