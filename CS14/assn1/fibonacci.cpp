#include <iostream>
#include <fstream>
#include <sstream>
#include "Series.h"

using namespace std;

double FibLoop(int);
double FibRec(int);
double FibRec1(int);
void FibRec2(int, double&, double&);
double GenLoop(int n, int k, double initial[], double weight[]);
double GenRec(int n, int k, double initial[], double weight[]);
double GenRec1(int n, int k, double initial[], double weight[]);
void GenRec2(int n, int k, double initial[], double weight[], double back[]);
string replaceExtension(string, string);

int totalAdds, totalCalls, totalMoves;
const int TOTAL_CALLS_SAFETY_LIMIT = 100000;

int main(int argc, char* argv[]){
    
    if(argc == 1){//input filename is not present
        ofstream fout;
        string filename;
        //Part 2 - Naive Implementation
        cout<<"Iterative\tRecursive"<<endl;
        for(int i = 0; i <= 20; ++i){
            cout<<FibLoop(i)<<"\t\t"<<FibRec(i)<<endl;
        }
        
        //Part 3 - Efficiancy of the Naive Functions
        filename = "test1.csv";
        fout.open(filename.c_str());
        if(!fout.is_open()){
            cout<<"Error opening "<<filename<<endl;
            return 1;
        }
        
        for(int i = 0; i <= 30; ++i){
            totalAdds = 0;
            totalCalls = 1;
            totalMoves = 0;
            FibLoop(i);
            fout<<i<<","<<totalAdds<<","<<totalCalls<<",";
            
            totalAdds = 0;
            totalCalls = 1;
            totalMoves = 0;
            FibRec(i);
            fout<<totalAdds<<","<<totalCalls<<endl;
            if(totalCalls > TOTAL_CALLS_SAFETY_LIMIT)
                break;
        }
        fout.close();
        
        //Part 4 - Fast Recursive Fibonacci and its Efficiency
        filename = "test2.csv";
        fout.open(filename.c_str());
        if(!fout.is_open()){
            cout<<"Error opening "<<filename<<endl;
            return 1;
        }
        
        for(int i = 0; i <= 30; ++i){
            totalAdds = 0;
            totalCalls = 1;
            totalMoves = 0;
            FibRec1(i);
            fout<<i<<","<<totalAdds<<","<<totalCalls<<","<<totalMoves<<endl;
        }
        fout.close();
        
        //Part 5 - Evaluating More General Recurrence Relations
        filename = "test3.csv";
        fout.open(filename.c_str());
        if(!fout.is_open()){
            cout<<"Error opening "<<filename<<endl;
            return 1;
        }
        
        int k = 2;
        double initial[k];
        double weight[k];
        
        initial[0] = 0;
        initial[1] = 1;
        weight[0] = 1;
        weight[1] = 1;
        
        for(int i = 0; i <= 30; ++i){
            totalAdds = 0;
            totalCalls = 1;
            totalMoves = 0;
            GenLoop(i,k,initial,weight);
            fout<<i<<","<<totalAdds<<","<<totalCalls<<","<<totalMoves<<",";
            totalAdds = 0;
            totalCalls = 1;
            totalMoves = 0;
            GenRec(i,k,initial,weight);
            fout<<totalAdds<<","<<totalCalls<<","<<totalMoves<<endl;
        }
        fout.close();
        
        filename = "test4.csv";
        fout.open(filename.c_str());
        if(!fout.is_open()){
            cout<<"Error opening "<<filename<<endl;
            return 1;
        }
        
        //case 1
        k = 3;
        double initial1[k];
        double weight1[k];
        
        initial1[0] = 2;
        initial1[1] = -3;
        initial1[2] = 1;
        weight1[0] = 1.1;
        weight1[1] = -0.15;
        weight1[2] = -0.9;
        
        fout<<k;
        for(int i = 0; i < k; ++i){
            fout<<","<<initial1[i];
        }
        for(int i = 0; i < k; ++i){
            fout<<","<<weight1[i];
        }
        fout<<endl;
        for(int i = 0; i < 30; ++i){
            fout<<GenLoop(i, k, initial1, weight1)<<",";
        }
        fout<<GenLoop(30, k, initial1, weight1)<<endl;
        
        //case 2
        k = 3;
        double initial2[k];
        double weight2[k];
        
        initial2[0] = 0;
        initial2[1] = 0;
        initial2[2] = 1;
        weight2[0] = 1;
        weight2[1] = 1;
        weight2[2] = 1;
        
        fout<<k;
        for(int i = 0; i < k; ++i){
            fout<<","<<initial2[i];
        }
        for(int i = 0; i < k; ++i){
            fout<<","<<weight2[i];
        }
        fout<<endl;
        for(int i = 0; i < 30; ++i){
            fout<<GenLoop(i, k, initial2, weight2)<<",";
        }
        fout<<GenLoop(30, k, initial2, weight2)<<endl;
        fout.close();
        
        //Part 6 - A Series Class For Recurrence Relation Objects
        filename = "test5.csv";
        fout.open(filename.c_str());
        if(!fout.is_open()){
            cout<<"Error opening "<<filename<<endl;
            return 1;
        }
        
        k = 2;
        initial[0] = 0;
        initial[1] = 1;
        weight[0] = 1;
        weight[1] = 1;
        
        Series s;
        s.set_k(k);
        s.set_initial(initial);
        s.set_weights(weight);
        
        for(int i = 0; i <= 30; ++i){
            totalAdds = 0;
            totalCalls = 1;
            totalMoves = 0;
            s.GenLoop(i);
            fout<<i<<","<<totalAdds<<","<<totalCalls<<","<<totalMoves<<",";
            totalAdds = 0;
            totalCalls = 1;
            totalMoves = 0;
            s.GenRec(i);
            fout<<totalAdds<<","<<totalCalls<<","<<totalMoves<<endl;
        }
        fout.close();
    }
    else{//input filename is present e.g. ./a.out "input.txt"
        //Part 7 - Final Testing
        string filename = argv[1];
        ifstream fin(filename.c_str()); // Assuming the values in the file are separated by space
        if(!fin.is_open()){
            cout<<"Error opening "<<filename<<endl;
            return 1;
        }
    
        string outputFilename = replaceExtension(filename,".out");
        ofstream fout;
        fout.open(outputFilename.c_str());
        //fout.open(outputFilename.c_str());
        if(!fout.is_open()){
            cout<<"Error opening "<<outputFilename<<endl;
            return 1;
        }
        
        int k;
        string firstRow,secondRow;
        while(fin>>k){
            getline(fin, firstRow);
            istringstream iss(firstRow);
            int wordCount = 1; //WordCount for the first row must be 2 * k + 1
            double initial[k];
            double weight[k];
            double num;
            
            int i = 0;//index of weight
            int j = 0;//index of initial
            while(iss >> num){
                wordCount++;
                if(i < k){
                    weight[i++] = num;
                }
                else if(wordCount > 2*k+1){//error
                    cout<<"Error in the input file"<<endl;
                    return 1;
                }
                else{
                    initial[j++] = num;
                }
            }
            if(wordCount < 2*k+1){//error
                cout<<"Error in the input file"<<endl;
                return 1;
            }
            Series s;
            s.set_k(k);
            s.set_initial(initial);
            s.set_weights(weight);
            
            getline(fin, secondRow);
            iss.clear();
            iss.str(secondRow);
            int n;
            while(iss>>n){
                if(n < 0){//error
                    cout<<"Error in the input file"<<endl;
                    return 1;
                }
                fout<<s.get_val(n)<<" ";
            }
            fout<<endl;
        }
        fout.close();
    }
    return 0;
}

double FibLoop(int n){
    int fib[n+1];
    fib[0] = 0;
    fib[1] = 1;
    for(int i = 2; i <= n; ++i){
        fib[i] = fib[i-1] + fib[i-2];
        totalAdds++;
    }
    return fib[n];
}

double FibRec(int n){
    if(n == 0 || n == 1){
        return n;
    }
    totalAdds++;
    totalCalls+=2;
    return FibRec(n-1) + FibRec(n-2);
}

double FibRec1(int n){
    if(n <= 1) return n;
    double oneBack = 1, twoBack = 0;
    FibRec2(n, oneBack, twoBack);
    return oneBack;
}

void FibRec2(int n, double &oneBack, double &twoBack){
    
    if(n <= 1){
        return;
    }
    else{
        totalCalls++;
        totalAdds++;
        FibRec2(n-1,oneBack,twoBack); 
        double tmp = oneBack;
        oneBack += twoBack;
        twoBack = tmp;
        totalMoves++;
        return;
    }
}

double GenLoop(int n, int k, double initial[], double weight[]){
    double fib[k];
    for(int i = 0; i < k; ++i)
        fib[i] = initial[i];
        
    for(int i = k;i<=n;++i){
        double tmp = 0;
        for(int j = 0; j < k ; ++j){
            tmp  += fib[(i - k + j)%k] * weight[j];
        }
        
        fib[i%k] = tmp;
        totalAdds += k - 1;
    }
    return fib[n%k];
}

double GenRec(int n, int k, double initial[], double weight[]){
    if(n < k){
        return initial[n];
    }
    totalAdds+=k - 1;
    totalCalls+=k;
    double fib = 0;
    for(int i = 1; i<= k; ++i)
        fib += GenRec(n-i, k, initial, weight)*weight[k-i];
        
    return fib;
}

double GenRec1(int n, int k, double initial[], double weight[]){
    if(n<k)
        return initial[n];
    double back[k];
    GenRec2(n,k,initial,weight,back);
    return back[n%k];
}

void GenRec2(int n, int k, double initial[], double weight[], double back[]){
    
    if(n < k){
        for(int i = 0; i < k; ++i)
            back[i] = initial[i];
        
    }
    else{
        totalCalls++;
        totalAdds+=k-1;
        
        GenRec2(n-1,k,initial,weight,back);
        double fib = 0;
        for(int i = 1; i<= k; ++i)
            fib += back[(n-i)%k]*weight[k-i];
        back[n%k] = fib;
        
        totalMoves+=1;
    }
}

string replaceExtension(string str, string ext){
    string newStr = str;
    int idx = str.rfind('.', str.length());
    if (idx>0) {
      newStr.replace(idx, ext.length(), "");
    }
    newStr += ext;
    return newStr;
}