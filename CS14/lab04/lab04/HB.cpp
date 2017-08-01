#ifndef HB_CPP
#define HB_CPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "Node.cpp"

template<typename Comparable> 
class HB_Tree {
  private: 
    void insert( Node<Comparable> *&x, Node<Comparable> *&t) {
        
        if( t == NULL ) {
            t = new Node<Comparable>( x->element, NULL, NULL, 0, 0, 0 );
        }
        else if( x->element < t->element ) {
            insert( x, t->left );
            (t->lsize)++;
        }
        else if( t->element < x->element ) {
            insert( x, t->right );
            (t->rsize)++;
        }
        else if( t->element == x->element) {
            insert(x, t->left);
            (t->lsize)++;
        }
        // cout << t->lsize << " " << t->rsize << endl;
        
        if(t->lsize == t->rsize + 2 || t->lsize == t->rsize - 2) {
            rebalance(t);
        
        }
    }
    
    Node<Comparable> * findMin( Node<Comparable> *t ) const {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    
    Node<Comparable> * findMax( Node<Comparable> *t ) const {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }
    
    Node<Comparable> *removeNode( Node<Comparable> *&x, Node<Comparable> *&t) {
        // Node<Comparable> *temp = new Node<Comparable>;
        if( t == NULL ) {
            return 0; // Item not found; do nothing
        }
        else if( x->element < t->element ) {
            removeNode( x, t->left );
            --t->lsize;
        }
        else if( t->element < x->element ) {
            removeNode( x, t->right );
            --t->rsize;

        }
        else if( t->left != NULL && t->right != NULL ) {
            t->element = findMin( t->right )->element;
            removeNode( t, t->right );
            --t->rsize;
        }
        else {
            Node<Comparable> *oldNode = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            return oldNode;
        }
        
    }
    
    Node<Comparable> *removeMax(Node<Comparable> *&t) { 
        Node<Comparable>* x = findMax(t);
        removeNode(x, t);
        
        rebalance(t);
        return x;
    }

    Node<Comparable> *removeMin(Node<Comparable> *&t) { 
        Node<Comparable>* x = findMin(t);
        removeNode(x, t);
        
        rebalance(t);
        return x;
    }

    
    void rebalance(Node<Comparable> *&t) {
        if(t == NULL) {
            return;
        }
        
        if(t->left == 0) {
            t->lsize = 0;
        }
        else {
            t->lsize = t->left->lsize + t->left->rsize + 1;
        }
        
        if(t->right == 0) {
            t->rsize = 0;
        }
        
        else {
            t->rsize = t->right->rsize + t->right->lsize + 1;
        }
        
        if(t->lsize == t->rsize + 2) { 
            Node<Comparable> *maxNode = removeMax(t->left);
            --(t->lsize);
            swap(maxNode->element, t->element);
            
            // Node<Comparable> *temp = new Node<Comparable>(t->element, NULL, NULL, 0, 0, 0);
            // t->element = max->element;
            
            insert(maxNode, t->right);
            ++(t->rsize);
        }
        if(t->lsize == t->rsize - 2) {
            Node<Comparable> *minNode = removeMin(t->right);
            --(t->rsize);
            swap(minNode->element, t->element);
            // Node<Comparable> *temp = new Node<Comparable>(t->element, NULL, NULL, 0, 0, 0);
            // t->element = min->element;
            insert(minNode, t->left);
            ++(t->lsize);
        }
        
    }
    
  public:
    Node<Comparable> *root;
    HB_Tree() : root( NULL ) { }

    void insert( const Comparable & x ) { 
        Node<Comparable> *t = new Node<Comparable>( x, NULL, NULL, 0, 0, 0 );
        insert( t, root );
    }

};

#endif