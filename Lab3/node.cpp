/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    std::cout << "** In node destructor" << std::endl;

    if(!l_thread)
        delete left;

    if(!r_thread)
        delete right;
}

// Traverses towards the value of the key, returns true if key was found.
bool Node::traverseToKey(Node*& tempRoot, const string key) const{

    // Loop through tree
    while(tempRoot){

        // Value is bigger than root, iterate right
        if(key > tempRoot->value.first){

            if(tempRoot->r_thread)
                break;

            tempRoot = tempRoot->right;
        }

        // Value is less than root, iterate left
        else if(key < tempRoot->value.first){

            if(tempRoot->l_thread)
                break;

            tempRoot = tempRoot->left;

        }

        // Same value
        else
            return true;

    }

    return false;

}

// Traverses the binary tree and returns the value corresponding to the node,
Node* Node::findParentNode(const string key){

    Node* traverseNode = this;

    // Loop through tree
    while(traverseNode){

    //    std::cout << "TRAVERSENODE VALUE FIRST" << traverseNode->value.first << std::endl;

        // Value is bigger than node, iterate right
        if(key > traverseNode->value.first){

            if(key == traverseNode->right->value.first)
                break;

            else
                traverseNode = traverseNode->right;

        }

        // Value is less than root, iterate left
        else if (key < traverseNode->value.first){

            if(key == traverseNode->left->value.first)
                break;

            else
                traverseNode = traverseNode->left;

        }

        //else
        //    std::cout << "Something is wrong in the findParentNode function" << std::endl;

    }

    return traverseNode;

}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    //Node* tempRoot = this;
    //findParentNode(tempRoot, v.first);

    // Finds the parent node of the node containing key in element.
    Node* temp = this;

    // If key was value was found, updating..
    if(traverseToKey(temp, v.first)){
        temp->value.second++;
        return false;
    }

    // Else insert last in the list
    else if(v.first > temp->value.first){

        Node* newNode = new Node(v, temp, temp->right);
        temp->right = newNode;
        temp->r_thread = false;
        newNode->r_thread = newNode->l_thread = true;

    }

    else{

        Node* newNode = new Node(v, temp->left, temp);
        temp->left = newNode;
        temp->l_thread = false;
        newNode->r_thread = newNode->l_thread = true;

    }

    // If no parent node, same value was found. updating..
    /*if ( !findParentNode(tempRoot, v.first) ){
        tempRoot->value.second++;
        return false;
    }

    // Insert node right of the parent node
    if(v.first > tempRoot->value.first){

        Node *newNode = new Node(v, tempRoot, tempRoot->right);
        tempRoot->right = newNode;
        tempRoot->r_thread = false;
        newNode->r_thread = newNode->l_thread = true;

    }

    // Insert node left of the parent node
    else{

        Node * newNode = new Node(v, tempRoot->left, tempRoot);
        tempRoot->left = newNode;
        tempRoot->l_thread = false;
        newNode->r_thread = newNode->l_thread = true;
    }*/

    return true;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{

    Node* nodeToRemove = find(key);

    if(!nodeToRemove)
        return false;

    isRight ? parent = parent->right : parent = parent->left;

    std::cout << "Trying to remove node with value: " << nodeToRemove->value.first << std::endl;
    std::cout << "Root is right now " << parent->value.first << std::endl;

    // We now have two cases
    // First case: if node has two children
    if(!nodeToRemove->l_thread && !nodeToRemove->r_thread){

        // Find the node that is next biggest (exists in the right subtree)
        Node* nextBiggest = nodeToRemove->right->findMin();

        //Update value of the old node
        nodeToRemove->value = nextBiggest->value;

        std::cout << "trying to find parent of " << nextBiggest->value.first << std::endl;
        std::cout << "root VAL" << tempRoot->value.first << std::endl;

        // Find parent of the next biggest node
        Node* parentOfNextBiggest = tempRoot->findParentNode(nextBiggest->value.first);

        if(nextBiggest->value.first < parentOfNextBiggest->value.first)
            nextBiggest->removeMe(parentOfNextBiggest, false);

        else
            nextBiggest->removeMe(parentOfNextBiggest, true);

    }

    // Second case: node has at most one child
    else{

        return true;

        if(nodeToRemove->value.first < parent->value.first)
            nodeToRemove->removeMe(parent, false);

        else
            nodeToRemove->removeMe(parent, true);

    }

    return true;


}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
    // If node is a leaf (no children)
    if(l_thread && r_thread){

        // Right of parent
        if(isRight){
            // Point where leaf is pointing
            parent->right = this->right;
            parent->r_thread = true;
            delete this;
        }

        else{

            parent->left = this->left;
            parent->l_thread = true;
            delete this;

        }

    }

    // If node has one child
    else{

        if(isRight && r_thread){

            parent->right = this->right;
            delete this;

        }

        else if (isRight && l_thread){

            parent->right = this->left;
            delete this;

        }

        else if(!isRight && r_thread){

            parent->left = this->left;
            delete this;
        }

        else if (!isRight && l_thread){

            parent->left = this->right;
            delete this;
        }

        else{

            std::cout << "Something is wrong in the removeMe function" << std::endl;

        }

    }

}


//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    Node* tempRoot(this);

    // If key was found return the value
    if (traverseToKey(tempRoot, key))
        return tempRoot;

    return nullptr;
}


//Return a pointer to the node storing the smallest value
//of the tree whose root is this node
Node* Node::findMin()
{

    Node* minNode = this;

    while(minNode){

        string value = minNode->value.first;

        if(minNode->l_thread)
            break;

        minNode = minNode->left;

        if(minNode->value.first < value)
            value = minNode->value.first;

    }

    return minNode;

}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    Node* maxNode = this;

    while(maxNode){

        string value = maxNode->value.first;

        if(maxNode->r_thread)
            break;

        maxNode = maxNode->right;

        if(maxNode->value.first > value)
            value = maxNode->value.first;

    }

    return maxNode;

}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
