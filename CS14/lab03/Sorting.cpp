#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
using namespace std;


template <typename T> void insertRight(vector<T> &v, int current, int last) {
    // vector<T>::iterator it;
    // vector<T>::iterator j;
    while(current < last && (v.at(current) > v.at(current + 1))) {
        T temp = v.at(current);
        v.at(current) = v.at(current + 1);
        v.at(current + 1) = temp;
        current++;
    }
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << ' ';
    }
    cout << endl;
}

template <typename T> void insertionSort(vector<T> &v, int begin, int end) {
    for(int i = end; i >= begin; --i) {
        insertRight(v, i, end);
    }
}

template <typename T> void SelectionSort(vector<T> &v) {
    for(int i = 0; i < v.size(); ++i) {
        for (int j = i + 1; j < v.size(); ++j) {
            if (v.at(j) < v.at(i)) {
                T temp = v.at(i);
                v.at(i) = v.at(j);
                v.at(j) = temp;
            }
        }
    }
}

template <typename T> void blockInsertionSort(vector<T> &v, const int& rem, const int &blockSize) {
    for(unsigned i = 0; i < v.size()- blockSize - rem; i+=blockSize) { // doesn't sort last block
        int left = i;
        int right = blockSize + i - 1; 
        insertionSort(v, left, right);
    }
    insertionSort(v,v.size()- blockSize - rem, v.size()-1);
}

template <typename T> void entireVectorSort(vector<T> &v) {
    int numberOfBlocks = sqrt(v.size()); 
    int rem = v.size() % numberOfBlocks;
    int blockSize = v.size() / numberOfBlocks; 
    
    for(int i = 0; i < v.size() - rem; i++) {
        int min = i;                      
        for(int j = i; j < v.size(); j = (j / blockSize) * blockSize + blockSize) { 
            if(v.at(j) < v.at(min)) min = j;
        }

        if(i != min) {                       
          T temp = v.at(i);              
          v.at(i) = v.at(min);       
    
          int b = min / blockSize; // block where the min came from             
          int blockIndex = b * blockSize;                
          if(rem != 0 && b == numberOfBlocks - 1) blockSize = rem;                   
    
          for(int j = blockIndex + 1; j < blockIndex + blockSize; j++) v.at(j - 1) = v.at(j);             
          v.at(blockIndex + blockSize - 1) = temp;             
    
          int j = blockIndex + blockSize - 2;                  
          while(j >= blockIndex && v.at(j) > temp) {     
            v.at(j+1) = v.at(j);               
            v.at(j) = temp;
            j--;                               
          }                              
        }                       
    }                                       
}

template <typename T> void squareSort(vector<T> &v) {
    int numberOfBlocks = sqrt(v.size()); 
    int blockSize = v.size() / numberOfBlocks; // size of block
    int rem = v.size() % numberOfBlocks;
    vector<T> tempVec; // to put the first elements of each block 
            
    cout << "/// SQUARE SORT /// " << endl;
    cout << "Original vector: ";
    for(unsigned i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
            
    cout << "Sorted vector: "; 
    blockInsertionSort(v, rem, blockSize);
    for(unsigned i = 0; i < v.size(); i++) { 
        cout << v.at(i) << " ";
    }

    for(unsigned i = 0; i < v.size() - rem; i+=blockSize) { 
        tempVec.push_back(v.at(i));
    }
    cout << endl;
            
    cout << "Vector of first elements: ";
    for(unsigned i = 0; i < tempVec.size(); i++) {
        cout << tempVec.at(i) << " ";
    }
    cout << endl;
             
    SelectionSort(tempVec);
    int j = 0; // puts back into initial vector
    for(unsigned i = 0; i < v.size() - rem; i+=blockSize) { 
        v.at(i) = tempVec.at(j);
        ++j;
    }
            
    cout << "Sorted vector of first elements: "; 
    for(unsigned i = 0; i < tempVec.size(); i++) {
        cout << tempVec.at(i) << " ";
    }
    cout << endl;
  
    cout << "Original vector after insertion sort: ";
    blockInsertionSort(v, rem, blockSize);
    for(unsigned i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
            
    entireVectorSort(v);
    cout << "Square sorted original vector: ";
    for(unsigned i = 0; i < v.size(); i++) { 
        cout << v.at(i) << " ";
    }
    cout << endl;    
}

template <typename T> void updateTarget(vector<T> &v, vector<T> tempVec1, vector<T> tempVec2) {
    unsigned i = 0;
    unsigned j = 0; 
    unsigned k = 0; 
    while (i < tempVec1.size() && j < tempVec2.size()) {
        if(tempVec1.at(i) < tempVec2.at(j)) { //FIX
            v.at(k) = tempVec1.at(i);
            i++;
        }
        else {
            v.at(k) = tempVec2.at(j);
            j++;
        }
        k++;
    }
    
    while (i < tempVec1.size()) {
        v.at(k) = tempVec1.at(i);
        i++;
        k++;
    }
 
    while (j < tempVec2.size()) {
        v.at(k) = tempVec2.at(j);
        j++;
        k++;
    }
    
}

template <typename T> void cubicSort(vector<T> &v) {
    int numberOfSuperBlocks = cbrt(v.size()); // super blocks
    int superBlockSize = v.size() / numberOfSuperBlocks; // size of each super block
    int rem = v.size() % numberOfSuperBlocks;
    int numberOfBlocks = sqrt(superBlockSize); // number of small blocks in each super block
    int blockSize = superBlockSize / numberOfSuperBlocks; // size of each small block

    // vector<T> tempVec1; // first half of the vector
    // vector<T> tempVec2; // second half of the vector
    
    vector<T> tempVec;
    
    cout << "/// CUBIC SORT /// " << endl;
    
    cout << "Original vector: ";
    for(unsigned i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
            
    cout << "Sorted vector: "; 
    blockInsertionSort(v, rem, blockSize);
    for(unsigned i = 0; i < v.size(); i++) { 
        cout << v.at(i) << " ";
    }

    for(unsigned i = 0; i < v.size() - rem; i+=blockSize) { 
        tempVec.push_back(v.at(i));
    }
    cout << endl;
            
    cout << "Vector of first elements: ";
    for(unsigned i = 0; i < tempVec.size(); i++) {
        cout << tempVec.at(i) << " ";
    }
    cout << endl;
             
    SelectionSort(tempVec);
    int j = 0; // puts back into initial vector
    for(unsigned i = 0; i < v.size() - rem; i+=blockSize) { 
        v.at(i) = tempVec.at(j);
        ++j;
    }
            
    cout << "Sorted vector of first elements: "; 
    for(unsigned i = 0; i < tempVec.size(); i++) {
        cout << tempVec.at(i) << " ";
    }
    cout << endl;
  
    cout << "Original vector after insertion sort: ";
    blockInsertionSort(v, rem, blockSize);
    for(unsigned i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
            
    entireVectorSort(v);
    cout << "Square sorted original vector: ";
    for(unsigned i = 0; i < v.size(); i++) { 
        cout << v.at(i) << " ";
    }
    cout << endl;   
    
    
    // cout << "Original vector: ";
    // for(int i = 0; i < v.size(); i++) {
    //     cout << v.at(i) << " ";
    // }
    // cout << endl;

    // for(int i = 0; i < v.size(); i+=blockSize) { 
    //     insertionSort(v, i, blockSize - 1 + i);
    // }

    // for(int i = 0; i < v.size(); i++) {
    //     cout << v.at(i) << " ";
    // }
    // cout << endl;
    
    // for(int i = 0; i < superBlockSize; i++) { // half of vector size
    //     tempVec1.push_back(v.at(i));
    //     cout << v.at(i) << " ";
    // }
    // cout << endl;
    // SelectionSort(tempVec1);
    
    // for(int i = 0; i < superBlockSize; i++) {
    //     tempVec2.push_back(v.at(i));
    //     cout << v.at(i) << " ";
    // }
    // cout << endl;
    // SelectionSort(tempVec2);
    
    // for(int i = 0; i < v.size(); i++) {
    //     cout << v.at(i) << " ";
    // }
    // cout << endl;
    // updateTarget(v, tempVec1, tempVec2);
    
    // for(int i = 0; i < v.size(); i++) {
    //     cout << v.at(i) << " ";
    // }
    cout << endl;
    
}