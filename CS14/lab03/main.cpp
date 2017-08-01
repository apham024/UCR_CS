#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "Fraction.cpp"
#include "Sorting.cpp"

int main( int argc, char *argv[] ) {
    if(argc == 2) {
        string firstLine, secondLine, thirdLine, fourthLine; 
             
        vector<int> v1; // vector of integers from file
        vector<Fraction> v2; // vector of fractions from file

        string filename = argv[1];
        ifstream inFS;
        
        inFS.open(filename.c_str() );
        if(inFS.fail()) {
            cout << "Error opening file." << endl;
            exit(1);
        }
        
        while(inFS.good()) {
    
            getline(inFS, firstLine);
            if(firstLine.at(0) == 'i') { // if the first char is an i, then go to the next line and output all elements
                getline(inFS, secondLine);
                string s(secondLine);
                istringstream inSS(s);
                int num; // numbers on the line
                while(inSS >> num) {
                v1.push_back(num);
                }
            }
            
            for(unsigned i = 0; i < v1.size(); i++) {
                cout << v1.at(i) << " ";
            }
            
            cout << endl;
            getline(inFS, thirdLine);
            if(thirdLine.at(0) == 'f') { 
                getline(inFS, fourthLine);
                string s(fourthLine);
                istringstream inSS(s);
                int num, denom;

                while(inSS >> num) {
                    inSS >> denom;
                    v2.push_back(Fraction(num, denom));
                }
                
                for(unsigned i = 0; i < v2.size(); i++) {
                    cout << v2.at(i) << " ";
                }
            }
            
        }
        cout << endl;
        inFS.close();
        
        ofstream outFS;
        string filename2 = argv[1];
        string outputFilename = replaceExtension(filename2, ".out");

        outFS.open(outputFilename.c_str() );
        if(outFS.fail()) {
            cout << "Error opening file." << endl;
            exit(1);
        }
        
        else {
            vector<int> v3 = v1;
            vector<Fraction> v4 = v2;
            outFS << "i";
            outFS << endl;
            outFS << "Sorted integers with square sort: ";
            squareSort(v1);
            for(unsigned i = 0; i < v1.size(); i++) {
                outFS << v1.at(i) << " ";
            }
            outFS << endl;
            outFS << "Sorted integers with cubic sort: ";
            cubicSort(v3);
            for(unsigned i = 0; i < v1.size(); i++) {
                outFS << v3.at(i) << " ";
            }
            
            outFS << endl;
            outFS << "f";
            outFS << endl;
            outFS << "Sorted fractions with square sort: ";
            squareSort(v2);
            for(unsigned i = 0; i < v2.size(); i++) {
                outFS << v2.at(i) << " ";
            }
            outFS << endl;
            outFS << "Sorted fractions with cubic sort: ";
            cubicSort(v4);
            for(unsigned i = 0; i < v2.size(); i++) {
                outFS << v4.at(i) << " ";
            }

            
        }
        outFS.close();
    }
    else { 
        cout << "Error, please input a filename" << endl;
    }
    return 0;
    
}