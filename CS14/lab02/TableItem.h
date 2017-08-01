#ifndef TableItem_H
#define TableItem_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class TableItem {
  private:
    string w; // holds the “word” associated with this object, whose value is initialized by the constructor
    vector<unsigned> v; // holds the sequence of positions at which this “word” was found within the input file
  public:
    TableItem(string, unsigned); // default c'tor
    void setWord( string newWord ); // which sets the value of string w to newWord, if it was not already initialized in the constructor
    string word(); // which returns the value of string w
    void newPos( int p ); // which appends a new position p to the end of the vector v
    int atPos( int p ); // which returns the value stored in v.at(p)
    int posSize(); // which returns the value of v.size()
};

#endif