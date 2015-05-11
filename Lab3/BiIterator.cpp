/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 {

 }


//Dereferencing operator

ELEMENT& BiIterator::operator*() const
{
    return this->current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    ELEMENT* e = &this->current->value;

    return e;
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
    return this->current->value == it.current->value;
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
    return this->current->value != it.current->value;
}

//Pre increment operator
BiIterator& BiIterator::operator++()
{
    // If no right subtree, proceed to next inorder node
    if(this->current->r_thread)
        this->current = this->current->right;

    // Find minimum value in the right subtree
    else
        this->current = this->current->right->findMin();

    return *this;

}

//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
    BiIterator tempIterator(*this); // Make a copy for the result

    ++(*this); // Let pre increment do the work

    return tempIterator; // Return the old value

}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
    // If node has no left subtree, just reverse to node before
    if(this->current->l_thread)
        this->current = this->current->left;

    // Find max value in left sub tree
    else
        this->current = this->current->left->findMax();

    return *this;

}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{

    BiIterator tempIterator(*this); // Make a copy for the result

    --(*this); // Let pre decrement do the work

    return tempIterator; // Return old value

}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
