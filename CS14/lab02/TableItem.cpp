#include "TableItem.h"
#include <list>
#include <iostream>
using namespace std;

TableItem::TableItem(string word, unsigned x) {
    w = word;
    v.push_back(x);
}

void TableItem::setWord( string newWord ) {
    w = newWord;
}

string TableItem::word() {
    return w;
}

void TableItem::newPos( int p ) {
    // v.insert(v.end(), p);
    v.push_back(p);
}

int TableItem::atPos( int p ) {
    if(p < v.size()) {
        return v.at(p);
    }
    else {
        cout << "Out of range" << endl;
    }
}

int TableItem::posSize() {
    return v.size();
}

