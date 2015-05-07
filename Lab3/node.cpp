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
    //ADD CODE
}

bool Node::findParentNode(Node*& tempRoot, const string key){

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
            return false;

    }

    return true;

}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    Node* tempRoot = this;

    // If no parent node, same value was found. updating..
    if ( !findParentNode(tempRoot, v.first) ){
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
    }

    return true;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //ADD CODE
    return false;
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
   //ADD CODE
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    Node* tempRoot = this;

    if (!findParentNode(tempRoot, key))
        return tempRoot;

    return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    //ADD CODE
    return nullptr;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    //ADD CODE
    return nullptr;
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
