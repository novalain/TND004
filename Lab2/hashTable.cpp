#include <assert.h>
#include <iomanip>

#include "hashTable.h"

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0)
{

    std::cout << "** HashTable Constructor " << std::endl;

    hTable = new Item*[size];

    for(int i = 0; i < size; i++){
       hTable[i] = nullptr;
    }

   /* cout << size << endl;
    cout << table_size << endl;
    cout << nItems << endl;
    cout << h << endl;*/
    //cout << f[0] << endl ;

    //hTable = nullptr; //to be deleted

    //cout << hTable[0]->value << endl;
    //cout << hTable[1]->key << endl;

}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    std::cout << "** HashTable Destructor" << std::endl;

    delete[] hTable; 
    size = 0;
    nItems = 0;

}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{

    int hKey = h(key, size);

    // Start search from the original hashKey position
    while(hTable[hKey] != nullptr){

        if(hTable[hKey]->key == key)
            return hTable[hKey]->value;

        hKeyIterate(hKey);

    }

    std::cout << "** NOT FOUND " << std::endl;

    return NOT_FOUND;

}


void HashTable::hKeyIterate(int& hashKey) const{

    hashKey++;

    if(hashKey == size){

        std::cout << "** LAST POS IN HASH TABLE, START FROM TOP";
        hashKey = 0;

    }

}

//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
// Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{

    int hKey = h(key, size);

    if(find(key) == NOT_FOUND){

        // Memory leaks ? no destructor to call in class Item

        Item* itemToAdd = new Item(key, v);

        while(hTable[hKey] != nullptr){

            // If any deleted items, insert value at deleted items position
            if(hTable[hKey] == Deleted_Item::get_Item())
                break;

            hKeyIterate(hKey);

        }

        hTable[hKey] = itemToAdd;

        nItems++;

        std::cout << "** Load factor is currently " << loadFactor() << std::endl;

        if(loadFactor() > 0.5)
            reHash();

    }

    // Found value in table, changing the old value.
    else{

        while(hTable[hKey]->key != key){

            hKeyIterate(hKey);

        }

        hTable[hKey]->value = v;

    }

}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{

    int hKey = h(key, size);

    // Not found
    if(find(key) == NOT_FOUND)
        return false;

    while(hTable[hKey]->key != key){

        hKeyIterate(hKey);

    }

    Deleted_Item* delItem = Deleted_Item::get_Item();
    hTable[hKey] = delItem;
    nItems--;

    return true;

}

int HashTable::operator[](const string key){

    int hKey = h(key, size);

    if(find(key) == NOT_FOUND){

        insert(key, 0);

    }

    return find(key);

}


void HashTable::display(ostream& os)
{
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }

        else
        {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }

    os << endl;

}


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{

    for(int i = 0; i < T.size; i++)
    {
        if(T.hTable[i] != nullptr)
            os << "key = " <<  T.hTable[i]->key << setw(15) << fixed << right
               << "value = " << T.hTable[i]->value << endl;
    }

    return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{   
    int oldSize = size;
    Item** hTableOld = new Item*[oldSize];

    // Map old values to a new array with pointers to items allocated on the heap
    for(int i = 0; i < oldSize; i++){

        hTableOld[i] = hTable[i];

    }

    size = nextPrime(2*size);
    nItems = 0;
    std::cout << "** Rehashing, new size is " << size << std::endl;

    // Reset all values in table
    for(int i = 0; i < size; i++){

        hTable[i] = nullptr;

    }

    // Map over the old stored values to our table
    for(int i = 0; i < oldSize; i++){

        if(hTableOld[i] != nullptr){

            insert(hTableOld[i]->key, hTableOld[i]->value);

        }

    }

    // Clear allocated memory
    delete[] hTableOld;

}
