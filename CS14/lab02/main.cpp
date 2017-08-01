#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <cstdlib>
using namespace std;

#include "TableItem.h"

// outputting each word of the entire paragraph into the list and then putting them in ABC order 
// then outputs the position it is at

int main(int argc, char *argv[]) {
    if(argc == 1) { // not present
        list<TableItem> wordList; 
        list<TableItem>::iterator it = wordList.begin();
        list<TableItem>::iterator j;
        unsigned index = 0;
        string myWord; // word in the list
        string filename = "TableItem.txt";
    
        ifstream inFS;
        
        inFS.open(filename.c_str());
        if(inFS.fail()) {
            cout << "Error opening file." << endl;
            exit(1);
        }
        
        while(inFS.good() ) {
            char c;
            inFS.get(c);
    
            if(isalpha(c)) { // if it is a character, make it lowercase and append it to the word
                c = tolower(c);
                myWord = myWord + c;
            }
            
            while(!isalpha(c) && myWord.size() != 0) { // if it's not a character and it's not empty
                TableItem tempWord(myWord, ++index); // word that is going to be inserted into the list
                cout << myWord << " " << endl;
                wordList.push_back(tempWord); 
                myWord = "";
    
            }
        }
        
        inFS.close();
        
        cout << endl << "Unsorted word list: " << endl;
        for(it = wordList.begin(); it != wordList.end(); ++it) {
            cout << (*it).word() << " ";
        }
    
        cout << endl << endl << "Sorting word list.... " << endl;
        for(it = wordList.begin(); it != wordList.end(); ++it) {
            list<TableItem>::iterator min = wordList.begin();
                for(j = wordList.begin(); j != wordList.end(); ++j) {
                    if((*j).word() >= (*min).word()) {
                        min = j;
                }
                iter_swap(min, j);
            }
        }
    
        cout << endl << "Sorted word list: " << endl;
        for(it = wordList.begin(); it != wordList.end(); ++it) { // iterates through the list
            for(unsigned j = 0; j < (*it).posSize(); ++j) { 
              cout << (*it).atPos(j) << " ";
              cout << (*it).word() << endl;
            }
        }
    
        // freq part 1
        cout << endl << "Word Frequency Table: " << endl;
        string tempWord = (*it).word(); // first word in the list
        unsigned freq = 0;
        unsigned tempFreq = 0;
        unsigned mostFreq = 0;
        unsigned secMostFreq = 0;
        string temp;
        string mostFreqWord;
        string secMostFreqWord;
    
        for(it = wordList.begin(); it != wordList.end(); ++it) { // iterates through the list
            if((*it).word() != tempWord) {
                cout << (*it).word() << ": ";
                for(j = wordList.begin(); j != wordList.end(); ++j) { 
                    for(unsigned a = 0; a < (*it).posSize(); ++a) { // prints out vector position
                        if((*it).word() == (*j).word()) {
                            cout << (*j).atPos(a) << ", ";
                            freq++;
                        }
                    }
                }
                tempFreq = freq;
                cout << endl << "Frequency: " << freq << endl;
                if(mostFreq < tempFreq) {
                    mostFreq = tempFreq;
                    mostFreqWord = (*it).word();
                }
                if(secMostFreq < tempFreq && tempFreq != mostFreq) {
                    secMostFreq = tempFreq;
                    secMostFreqWord = (*it).word();
                }
                tempWord = (*it).word();
                freq = 0;
            }
        }
        cout << "This single most-frequent word appears " << mostFreq << " times: " << mostFreqWord << endl;
        cout << "These second most-frequent word(s) appears " << secMostFreq << " times: " << secMostFreqWord << endl;
    }
    else { // if present
        string filename = argv[1];
        list<TableItem> wordList; 
        list<TableItem>::iterator it = wordList.begin();
        list<TableItem>::iterator j;
        unsigned index = 0;
        string myWord; // word in the list
        filename = "TableItem.txt";
        
        ifstream inFS;
        
        inFS.open(filename.c_str());
        if(inFS.fail()) {
            cout << "Error opening file." << endl;
            exit(1);
        }
        
        while(inFS.good() ) {
            char c;
            inFS.get(c);
    
            if(isalpha(c)) { // if it is a character, make it lowercase and append it to the word
                c = tolower(c);
                myWord = myWord + c;
            }
            
            while(!isalpha(c) && myWord.size() != 0) { // if it's not a character and it's not empty
                TableItem tempWord(myWord, ++index); // word that is going to be inserted into the list
                // cout << myWord << " " << endl;
                wordList.push_back(tempWord); 
                myWord = "";
    
            }
        }
        
        inFS.close();
        
        // cout << endl << "Unsorted word list: " << endl;
        // for(it = wordList.begin(); it != wordList.end(); ++it) {
        //     cout << (*it).word() << " ";
        // }
        
        // cout << endl << endl << "Sorting word list.... " << endl;
        for(it = wordList.begin(); it != wordList.end(); ++it) {
            list<TableItem>::iterator min = wordList.begin();
                for(j = wordList.begin(); j != wordList.end(); ++j) {
                    if((*j).word() >= (*min).word()) {
                        min = j;
                }
                iter_swap(min, j);
            }
        }
    
        // cout << endl << "Sorted word list: " << endl;
        // for(it = wordList.begin(); it != wordList.end(); ++it) { // iterates through the list
        //     for(unsigned j = 0; j < (*it).posSize(); ++j) { 
        //       cout << (*it).atPos(j) << " ";
        //       cout << (*it).word() << endl;
        //     }
        // }
    
        ofstream outFS;
        
        string filename2 = "table_" + filename;
        outFS.open(filename2.c_str());
        
        outFS << "Word Frequency Table: " << endl;
        string tempWord = (*it).word(); // first word in the list
        unsigned freq = 0;
        unsigned tempFreq = 0;
        unsigned mostFreq = 0;
        unsigned secMostFreq = 0;
        string temp;
        string mostFreqWord;
        string secMostFreqWord;

        for(it = wordList.begin(); it != wordList.end(); ++it) { // iterates through the list
            if((*it).word() != tempWord) {
                outFS << (*it).word() << ": ";
                for(j = wordList.begin(); j != wordList.end(); ++j) { 
                    for(unsigned a = 0; a < (*it).posSize(); ++a) { // prints out vector position
                    
                        if((*it).word() == (*j).word()) {
                            if(a != (*it).posSize())
                            outFS << (*j).atPos(a) << ", ";
                            freq++;
                        }
                      
                        // if((*it).atPos(a) == (*j).atPos((*it).posSize() - 1)) {
                        //     outFS << (*j).atPos(a) << " "; // achieve: 130, 130 
                        // }
                        
                    }
                }
                tempFreq = freq;
                outFS << endl << "Frequency: " << freq << endl;
                if(mostFreq < tempFreq) {
                    mostFreq = tempFreq;
                    mostFreqWord = (*it).word();
                }
                if(secMostFreq < tempFreq && tempFreq != mostFreq) {
                    secMostFreq = tempFreq;
                    secMostFreqWord = (*it).word();
                }
                tempWord = (*it).word();
                freq = 0;
            }
        }
        outFS << endl;
        outFS << "This single most-frequent word appears " << mostFreq << " times: " << mostFreqWord << endl;
        outFS << "These second most-frequent word(s) appears " << secMostFreq << " times: " << secMostFreqWord;
    
        outFS.close();
    }
    
    return 0;
}