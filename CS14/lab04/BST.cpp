#ifndef BST_CPP
#define BST_CPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "Node.cpp"

/**************************************************************Start of Book Code********************************************************************/

template <typename Comparable>
class BS_Tree
{
  public:
    Node<Comparable> *root;
    BS_Tree( ) :root( NULL )
    {
    }

    BS_Tree( const BS_Tree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    bool isEmpty( ) const
    {
        return root == NULL;
    }

    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    void insert( Comparable &x ) 
    { 
        Node<Comparable> *y = new Node<Comparable> (x, NULL, NULL, 0, 0, 0);
        insert(y, root);
    }
  private:
     void insert( Node<Comparable> *& x, Node<Comparable> * & t )
    {
        if( t == NULL )
            t = new Node<Comparable>( x->element, NULL, NULL, 0, 0, 0 );
        else if( x->element < t->element )
            insert( x, t->left );
        else if( t->element < x->element)
            insert( x, t->right );
        else if( t->element == x->element) {
            insert(x, t->right);
        }
        else 
            ;  // Duplicate; do nothing
    }

    bool contains( const Comparable & x, Node<Comparable> *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    void printTree( Node<Comparable> *t, ostream & out ) const
    {
        if( t != NULL )
        {
            printTree( t->left, out );
            out << t->element << " ";
            printTree( t->right, out );
        }
    }
};


/**************************************************************End of Book Code********************************************************************/

#endif