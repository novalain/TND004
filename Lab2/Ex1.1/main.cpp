/*
  Name: hashTable.h
  Author: Aida Nordman
  Course: TND004, Lab 2
  Description: test program for class HashTable
*/

#include <iostream>
#include <string>
#include <fstream>
#include "hashTable.h"

using namespace std;

string CHARS_TO_REMOVE = "(.,!?:\"();\\)";

unsigned int hashFunction(string key, int tableSize){

    unsigned int hashVal = 0;

    for(char ch : key)
        hashVal = 37 * hashVal + ch;


    return hashVal % tableSize;

}

void removeCharsFromString( string &str ) {

   for ( int i = 0; i < CHARS_TO_REMOVE.length(); i++ ) {
      str.erase( remove(str.begin(), str.end(), CHARS_TO_REMOVE[i]), str.end() );
   }

}

int main()
{
    const int TABLE_SIZE = 7;
    unsigned int numberOfWords, numberOfUniqueWords;

    HashTable freq_table(TABLE_SIZE, hashFunction);

    string word;
    ifstream infile("test_files/test_file2.txt");

    if (infile.is_open()){

        while ( infile >> word ){

            removeCharsFromString(word);
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            freq_table[word]++;
            numberOfWords++;

            if(freq_table[word] == 1)
              numberOfUniqueWords++;

        }

        infile.close();
    }

    std::cout << "\nNumber of words in the file = " << numberOfWords << std::endl
              << "Number unique words in the file = " << numberOfUniqueWords << std::endl << std::endl;

    std::cout << "Frequency table ... " << std::endl << std::endl;


    std::cout << freq_table;


    return 0;
}
