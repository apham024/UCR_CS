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
#include "BST.cpp"
#include "AVL.cpp"
#include "HB.cpp"

ofstream outFS;

template<typename T> void prettyPrint(Node<T> *curr, string linePrefix, string nodeTag) {
    if(curr == NULL) {
      return;
    }

    string leftLinePrefix = "  ";
    string rightLinePrefix = "  ";
    string rightNodeTag = " /";
    string leftNodeTag = " \\";
  
    if(nodeTag == " /") {
      rightLinePrefix = "| ";
    }
    else if(nodeTag == " \\") {
      leftLinePrefix = "| ";
    }
  
    if(nodeTag.size() == 0) {
      nodeTag = " <";
    }
  
    prettyPrint(curr->right, linePrefix + leftLinePrefix, rightNodeTag);
    outFS << linePrefix << nodeTag << curr->element << endl;
    prettyPrint(curr->left, linePrefix + rightLinePrefix, leftNodeTag);
}


int main( int argc, char *argv[] ) {
    if(argc == 2) {
      string filename = argv[1];
  	  string outputfilename = filename.substr(0, filename.size() - 4) + ".out";
  	   
  	  outFS.open(outputfilename.c_str());
  
      ifstream inFS;
      inFS.open(filename.c_str());
      
      if(!inFS.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
      }

  	  string temp; // string of integers
      int i = 1;

      while(getline(inFS, temp)) {
        
          BS_Tree<double> *BST = new BS_Tree<double>(); 
        	HB_Tree<double> *HB = new HB_Tree<double>(); 
        	AVL_Tree<double> *AVL = new AVL_Tree<double>(); 
    
          double number;
          
        	istringstream inSS(temp);
        	while(inSS >> number) {
        		BST->insert(number);
        		HB->insert(number);
        		AVL->insert(number);
        	}
         
          outFS << "TEST CASE " << i << ": " << endl;
          prettyPrint(BST->root, "", "");
          outFS << endl;
          prettyPrint(AVL->root, "", "");
          outFS << endl;
          prettyPrint(HB->root, "", "");
          outFS << endl;
          i++;
      }
    
    inFS.close();
    outFS.close();
    }
    else {
      cout << "INVALD NUMBER OF PARAMETERS. TRY AGAIN." << endl;
    }
    return 0;
}