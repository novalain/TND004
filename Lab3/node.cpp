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
    //std::cout << "** In node destructor" << std::endl;

    if(!l_thread)
        delete left;

    if(!r_thread)
        delete right;
}

//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    // Recursive model

    // Value bigger then value of node, check in the right subtree
    if(v.first > value.first){

        // If no more nodes in right thread, insert
        if(r_thread){

            Node* newChild = new Node(v, this, this->right);
            this->right = newChild;
            this->r_thread = false;
            newChild->r_thread = newChild->l_thread = true;

        }

        // Keep going right
        else
            return this->right->insert(v);
    }

    // Value smaller then value of node, check in the left subtree
    else if (v < value){

        // If no more nodes to the left, insert
        if(l_thread){

            Node* newChild = new Node(v, this->left, this);
            this->left = newChild;
            this->l_thread = false;
            newChild->r_thread = newChild->l_thread = true;

        }

        // Keep going left
        else
            return this->left->insert(v);
    }

    // Same value
    else {
        return false;
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

    // https://www.youtube.com/watch?v=wcIRPqTR3Kc for help about this

    // If key is smaller than our value keep looking in the left subtree
    if(key < value.first){

        if(!l_thread)
             left->remove(key, this, false);

    }

    // If key is bigger than our value keep looking in the right subtree
    else if(key > value.first){

        if(!r_thread)
             right->remove(key, this, true);

    }

    // We arrived at the value
    else if (key == value.first){

        // We now have two cases !
        // FIRST CASE: if node has two children
        if(!r_thread && !l_thread){

            //std::cout << "** Node appears to have two children" << std::endl;

            // Find the node that is next biggest (exists in the right subtree)
            // Update value of the old node and remove the node with next biggest value
            value = right->findMin()->value;
            return right->remove(value.first, this, true);

        }

        // SECOND CASE: node has one, or no child
        else{

            removeMe(parent, isRight);
            return true;

        }

    }

    // Didnt find any value to remove
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
    // If node is a leaf (no children)
    if(l_thread && r_thread){

        //2c: a right child with no children
        if(isRight){

        //    std::cout << "Removing a right child with NO children" << std::endl;
            parent->r_thread = true;
            parent->right = this->right;
        }

        //1c: a left child with no children
        else{
        //    std::cout << "Removing a left child with  NO children" << std::endl;
            parent->l_thread = true;
            parent->left = this->left;
        }

    }

    // Node has one child
    else{
        // Right child with only a left child
        if(isRight && r_thread){

            //std::cout << "Removing a right child with a left child";
            parent->right = this->left;

            // redirect the last "dummy thread" that were pointing at the node to remove, to point where the removed node was pointing
            // I.e point at the removed nodes inorder successor
            this->left->findMax()->right = this->right;

        }
        // Right child with only a right child
        else if (isRight && l_thread){

            //std::cout << "Removing a right child with a right child";
            parent->right = this->right;
            this->right->findMin()->left = this->left;

        }

        // Left child with only a left child
        else if(!isRight && r_thread){

            //std::cout << "Removing a left child with a left child";
            parent->left = this->left;
            this->left->findMax()->right = this->right;

        }

        // Left child with only a right child
        else if (!isRight && l_thread){

            //std::cout << "Removing a left child with a right child";
            parent->left = this->right;
            this->right->findMin()->left = this->left;

        }

        else{

            std::cout << "Something is wrong in the removeMe function" << std::endl;

        }

        // Set flags to true to prevent recursive delete of the whole tree
        l_thread = r_thread = true;
        delete this;

    }

}


//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    Node* tempRoot(this);

    // If key smaller and elements in left tree exists, keep going
    if(key < tempRoot->value.first){

        if(l_thread)
            return nullptr;

        else
            return tempRoot->left->find(key);

    }
    // If key larger and elements in right tree exists, keep going
    else if(key > tempRoot->value.first){

        if(r_thread)
            return nullptr;

        else
            return tempRoot->right->find(key);

    }

    // Else the elements is the same => FOUND!
    else if(key == tempRoot->value.first)
        return tempRoot;

    // Not found
    return nullptr;
}


//Return a pointer to the node storing the smallest value
//of the tree whose root is this node
Node* Node::findMin()
{

    if(!l_thread)
        return this->left->findMin();

    return this;

}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    if(!r_thread)
        return this->right->findMax();

    return this;

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
