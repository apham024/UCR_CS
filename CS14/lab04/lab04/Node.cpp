#ifndef NODE_CPP
#define NODE_CPP
#include <iostream>
using namespace std;

template<typename Comparable>
struct Node {
    Node<Comparable> *root;
    Comparable element;
    Node *left;
    Node *right;
    int height;
    int lsize;
    int rsize;
    Node( const Comparable& theElement, Node *lt, Node *rt, int h = 0, int ls = 0, int rs = 0 ) : 
                element( theElement ), left( lt ), right( rt ), height ( h ), lsize( ls ), rsize( rs ) { }
};

#endif