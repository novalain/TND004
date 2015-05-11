/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string CHARS_TO_REMOVE = "(.,!?:\"();\\)";


/*******************************
* 2. Main function             *
********************************/

bool isNotAlnum(char c){

    for(int i = 0; i < CHARS_TO_REMOVE.size(); i++){
        if(c == CHARS_TO_REMOVE[i])
            return true;
    }

    return false;

}

void displayTable(MAP& table){

    std::cout << "Frequency table sorted alphabetically..." << std::endl << std::endl
              << setw(15) << "KEY" << setw(10) << "" << "COUNTER" << std::endl
              << "=================================" << std::endl;

    BiIterator it = table.begin();

    while(it != table.end())
    {
        cout << setw(15) << right << it->first
             << setw(15) << it->second << endl;

        it++;

    }

}


int main()
{
    MAP table;

    string name, s;
    int count = 0;

    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    cout << "File name? ";
    getline(cin, name);

    ifstream textFile(name);

    if (!textFile)
    {
        cerr << "Text file could not be opened!!" << endl;
        exit(1);
    }

    cout << "Loading the words from " << name << " ...\n";

    //Read words and load them in the table
    while (textFile >> s)
    {
        //remove non-alphanumeric chars
        s.erase(remove_if(s.begin(), s.end(), isNotAlnum), s.end());

        //convert to lower-case letters
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        if (!s.size()) continue; //skip numbers and punctuation signs

        //std::cout << "s" << s << std::endl;

        table[s].second++;  //if s is not in the table then it is inserted

        count++;
    }


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    std::cout << "\nNumber of words in the file = " << count << std::endl
              << "Number unique words in the file = " << table.size() << std::endl << std::endl;




    displayTable(table);

    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    string wait;
    getline(cin, wait);

    /*std::cout << "** Removing values with counter 1 ..." << std::endl;

    BiIterator it = table.begin();

    while(it != table.end())
    {
        if(it -> second == 1){
            table.remove(it->first);
            count--;
        }

        it++;

    }

    std::cout << "Number of words after remove" << count;

    displayTable();*/





    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/

    //ADD CODE



    return 0;
}
