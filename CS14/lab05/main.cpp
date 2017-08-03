#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <sstream>
#include <string>

using namespace std;

struct room {
    vector<string> longStory;
    string shortStory;
    vector<int> Next;
    int Previous;
};
    
struct edge {
    int start; 
    int end;
    double W;
};

// global vectors 
vector<room> V; 
vector<edge> E;

vector<vector<pair<int,double> > > adj;
// now store target node and weight
vector<double> shortestpaths(int v) {
    vector<double> ret(adj.size(), -1);
    priority_queue<pair<int,double> > q;
    q.push(make_pair(v, 0));
    while(!q.empty()) {
        pair<int,double> s = q.top();
        q.pop();
        if (ret[s.first] == -1) {
            ret[s.first] = s.second;
            vector<int> Next = V.at(s.first).Next;
            // for(int j = 0; j < Next.size(); j++)
            // q.push(make_pair(j.first, s.second + j.second));
        }
    }
    return ret;
}

int main( int argc, char *argv[] ) {
    if(argc == 2) {
        ifstream inFS; 
        string filename = argv[1];
        
        string line; 

        vector<string> temp; // used to append current line with previous line if the same
        int sectionNum = 1;
        char deleteComma;
        int currentLine; 
        int previousLine; 

        int inc = 1; // increments to see if line matches with shortStory
        
        inFS.open(filename.c_str());
        
        if(!inFS.is_open()) {
            cout << "Error opening file." << endl;
            exit(1);
        }
        
        while(inFS.good() ) {
            getline(inFS, line);
            istringstream inSS(line);
            inSS >> currentLine;
            if(sectionNum == 1) {
                room bathroom;
                if(line == "-1,END") {
                    sectionNum++;
                    previousLine = 1;
                }
                else if(line == "1") {
                    // do nothing
                }
                else {
                    if(previousLine == currentLine) {
                        previousLine = currentLine;
                        line = line.substr(line.find(",") + 1);
                        temp.push_back(line); // appends it to previous line if the same number
                    }
                    else {
                        previousLine = currentLine;
                        bathroom.longStory = temp; 
                        temp.clear();
                        V.push_back(bathroom);
                        line = line.substr(line.find(",") + 1);
                        temp.push_back(line);
                    }
                }
            }
            else if(sectionNum == 2) {
                if(line == "-1") { 
                    sectionNum++;
                }
                else if(line == "2") { 
                    currentLine = 1; 
                }
                else {
                    if(currentLine == inc) { 
                        line = line.substr(line.find(",") + 1);
                        V.at(currentLine).shortStory = line;
                        ++inc;
                    }
                    else {
                        inc = currentLine;
                        line = line.substr(line.find(",") + 1);
                        V.at(currentLine).shortStory = line;
                    }
                }
            }
            else if(sectionNum == 3) {
                int num = 0; // compares with other numbers to find the max (edge weight) 
                int max = 0;
                if(line == "3") {
                    // do nothing;
                }
                else {
                    edge e;
                    int temp;
                    
                    string tempString = line.substr(0, line.find(","));
                    
                    line = line.substr(line.find(",") + 1);
                    
                    tempString = line.substr(0, line.find(","));
                    stringstream read(tempString);
                    read >> temp;
                    
                    line = line.substr(line.find(",") + 1);
                    
                    V.at(num).Next.push_back(temp);
                    e.start = num;
                    e.end = temp;
                    while(line.at(0) != '0') {
                        string weight = line.substr(0, line.find(","));
                        if(weight == "-1") {
                            break;
                        }
                        stringstream convert(weight);
                        convert >> num;
                        if(num > max) {
                            max = num;
                        }
                        line = line.substr(line.find(",") + 1);
                    }
                    
                    if(line == "-1") {
                        break;
                    }
                    // cout << "MAX WEIGHT: " << max << endl;
                    e.W = max;
                    E.push_back(e);
                    
                }
            }
        }
        inFS.close();
        
        // *************************USER INPUT******************************** //
        
        int vertexNumber;
        string answer;
        int i = 1;
            
        cout << "Enter three vertex numbers, starting from 1 " << endl;
            
        while(i <= 3) {
            cout << endl << "Enter vertex number " << i << ": " << endl;
            cin >> vertexNumber;
                
            if(vertexNumber >= 1 && vertexNumber <= 140) {
                for(int j = 0; j < V.at(vertexNumber).longStory.size(); ++j) {
                    cout << V.at(vertexNumber).longStory.at(j) << endl;
                }
                cout << endl << "For next vertex, type 'Y'. To enter for same vertex, type anything else. " << endl;
                cin >> answer;
                cout << endl;
                            
                cout << "START: " << E.at(vertexNumber).start << endl;
                cout << "END: " << E.at(vertexNumber).end << endl;
                cout << "MAX WEIGHT: " << E.at(vertexNumber).W << endl;
                
                if(answer == "Y" || answer == "y") {
                    ++i;
                }
                    
                else {
                    continue;
                }
            }
            else {
                cout << "Please enter a valid vertex. " << endl; 
            }
        }
    }
    else {
        cout << "INVALID NUMBER OF PARAMETERS." << endl;
    }
    return 0;    
}