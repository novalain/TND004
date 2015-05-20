/********************************************************
* File: threaded_BST.cpp                                *
* Author: Aida Nordman                                  *
* Course: TND004, Lab 3                                 *
* Date: VT2, 2014                                       *
* Description: class BST_threaded representing          *
*              a threaded binary search tree            *
*********************************************************/

#include "threaded_BST.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;


//Default Constructor: create an empty tree
//Empty tree has a dummy node as root
//The real tree is stored as left child of the dummy root
BST_threaded::BST_threaded()
 : counter(0)
{
    root = new Node(std::make_pair("",0), nullptr, nullptr);
}


//destructor
BST_threaded::~BST_threaded()
{
    // Recursevily delete the whole tree in class node
    delete root;

}


//Test if the tree is empty
bool BST_threaded::empty() const
{

    // If no left or right threads on root then empty
    if(!root->left && !root->right)
        return true;

    return false;
}

//Return mumber of keys (elements) stored in the tree
int BST_threaded::size() const
{
    return counter;
}


//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST has a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;

        root->l_thread = false; // Already false from the constructor?
        counter = 1;
    }
    else
        counter += root->left->insert(v); //call NODE::insert()
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
    if(empty())
        return;

    if(root->left->remove(key, root, false))
        counter--;

}



//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then an ELEMENT (key,0) is inserted and a reference to it is returned
ELEMENT& BST_threaded::operator[](string key)
{

    if(empty())
        insert(std::make_pair(key,0));

    Node* foundNode = root->left->find(key);

    //std::cout << "value of found node " << foundNode->value.first << std::endl;

    // If not found, inserting new value
    if(!foundNode){
        insert(std::make_pair(key, 0));
        return root->left->find(key)->value;
    }

    // Else, returns a reference to the value
    else{
        return foundNode->value;
    }

}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().
BiIterator BST_threaded::find(string key) const
{
    if(empty())
        return BiIterator(root);

    Node* foundNode = root->left->find(key);

    if(foundNode)
        return BiIterator(foundNode);

    return end();

}


//Return an iterator referring to the first node in the inorder traversal of the BST
BiIterator BST_threaded::begin() const
{
    if(empty())
        return BiIterator(root);

    Node* firstNode = root->left->findMin();
    BiIterator it(firstNode);

    return it;

}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);

    return it;
}


//Display all keys increasingly
//To be used for debugging -- ONLY
void BST_threaded::display() const
{
    if (!empty())
        root->left->display();
     else
        cout << "The container is empty!!" << endl;

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
