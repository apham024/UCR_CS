#include <iostream>
#include <fstream>
#include <cstdlib> // for exit(1)
using namespace std;

double FibLoop(int n);
double FibRec(int n);
double FibRec1(int n);
void FibRec2 ( int n, double &oneBack, double &twoBack);
double GenLoop ( int n, int k, double initial[], double weight[] );
double GenRec ( int n, int k, double initial[], double weight[] );
void GenRec2 ( int n, int k, double initial[], double weight[], double back[] );

int totalCalls = 1;
int totalAdds = 0;
int totalMoves = 0;

int main() {
    int n;
    double oneBack = 1.0;
    double twoBack = 0.0;
    
    // test2
    ofstream outFS;
    string filename = "test1.csv";
    
    outFS.open(filename.c_str());
    
    if(outFS.fail()) {
        cout << "Error opening file." << endl;
        exit(1);
    }
    
    for(unsigned i = 0; i < 30; i++) {
        FibLoop(i);
        
        outFS << i << ", ";    
        outFS << totalAdds << ", ";
        outFS << totalCalls << ", ";
        
        totalCalls = 1;
        totalAdds = 0;
        
        FibRec(i);

        outFS << totalAdds << ", ";
        outFS << totalCalls;

        outFS << endl;
    }
    
    outFS.close();
    
    totalAdds = 0;
    totalCalls = 1;
    
    // test2
    
    outFS.open("test2.csv");
    
    if(outFS.fail()) {
        cout << "Error opening file." << endl;
        exit(1);
    }
    
    for(unsigned i = 0; i < 30; i++) {
        FibRec1(i);
        
        outFS << i << ", ";    
        outFS << totalAdds << ", ";
        outFS << totalCalls << ", ";
        outFS << totalMoves << endl;
        
        totalCalls = 1;
        totalAdds = 0;
        totalMoves = 0;
    
    }
    
    outFS.close();
    
    // test3
    cout << "Enter number of terms: " << endl;
    cin >> n;
    
    int k = 0;
    
    cout << "Input k: " << endl;
    cin >> k;
    
    double weight[k];
    double initial[k];
    
    for(unsigned i = 0; i < k; i++) {
        cout << "Input weight: " << endl;
        cin >> weight[i];
        cout << "Input initial values: " << endl;
        cin >> initial[i];
    }
    
    cout << "GenLoop: " << GenLoop(n, k, initial, weight) << endl;
    cout << "GenRec: " << GenRec(n, k, initial, weight) << endl;
    
    outFS.open("test3.csv");
    
    if(outFS.fail()) {
        cout << "Error opening file." << endl;
        exit(1);
    }
    
    for(unsigned i = 0; i < 30; i++) {
        
        GenLoop(i, k, initial, weight);
        
        outFS << i << ", ";    
        outFS << totalAdds << ", ";
        outFS << totalCalls << ", ";
        outFS << totalMoves << ", ";
        
        totalCalls = 1;
        totalAdds = 0;
        totalMoves = 0;
        
        GenRec(i, k, initial, weight);
    
        outFS << totalAdds << ", ";
        outFS << totalCalls << ", ";
        outFS << totalMoves << endl;
        
    }
    
    outFS.close();

    // test4
    outFS.open("test4.csv");
    
    if(outFS.fail()) {
        cout << "Error opening file." << endl;
        exit(1);
    }
    
    GenLoop(n, k, initial, weight);
    if(k == 2) {
    outFS << "k value: " << k << " | Initial values: " << initial[0] << ", " 
        << initial[1] << "| Weights: " << weight[0] << ", " << weight[1] << endl;
    outFS << "Values in the sequence: ";
    GenRec(n, k, initial, weight);
    }
    if(k == 3) {
    outFS << "k value: " << k << " | Initial values: " << initial[0] << ", " << initial[1]  
        << ", " << initial[2] << "| Weights: " << weight[0] << ", " << weight[1] << ", " << weight[2] << endl;
        outFS << "Values in the sequence: ";
        GenRec(n, k, initial, weight);
    }
    if(k == 4) {
    outFS << "k value: " << k << " | Initial values: " << initial[0] << ", " << initial[1]  
        << initial[2] << ", " << initial[3] << "| Weights: " << weight[0] << ", " << weight[1] << ", " << weight[2] << ", " << weight[3] << endl;
        outFS << "Values in the sequence: ";
        GenRec(n, k, initial, weight);
    }

    outFS.close();
    
    // test5
    
    outFS.open("test5.csv");
    
    if(outFS.fail()) {
        cout << "Error opening file." << endl;
        exit(1);
    }
    
    for(unsigned i = 0; i < 30; i++) {
        
        GenLoop(i, k, initial, weight);
        
        outFS << i << ", ";    
        outFS << totalAdds << ", ";
        outFS << totalCalls << ", ";
        outFS << totalMoves << endl;
        
    }
    
    outFS.close();
    
    cout << endl << "Calling FibRec: " << endl;
    for(unsigned i = 0; i <= n; i++) {
        totalAdds = 0;
        totalCalls = 1;
        totalMoves = 0;
        
        FibLoop(i);
        cout << i << ", ";
        cout << totalAdds << ", ";
        cout << totalCalls << ", ";

        totalAdds = 0;
        totalCalls = 1;
        totalMoves = 0;
        
        FibRec(i);
        cout << totalAdds << ", ";
        cout << totalCalls << endl;
        
    }
    
    cout << endl << "Calling FibRec1: " << endl;
    for(unsigned i = 0; i <= n; i++) {
        totalAdds = 0;
        totalCalls = 1;
        totalMoves = 0;
        
        FibRec1(i);
        cout << i << ", ";
        cout << totalAdds << ", ";
        cout << totalCalls << ", ";
        cout << totalMoves << endl;
    }

    return 0;   
}

double FibLoop(int n) {
    int arr[n + 1];
    int prev = 0.0;
    int next = 1.0;
    int curr = 0.0;
    
    arr[0] = 0.0;
    arr[1] = 1.0;
    
    totalCalls = 1.0;
    totalAdds = 0.0;
    for(unsigned i = 2; i <= n; i++) {
        curr = prev + next;
        arr[i] = curr;
        prev = next;
        next = curr;
        
        totalAdds++;
    }

}

double FibRec(int n) { // inefficient 
    if(n == 0) {
        return 0;
    }
    if(n == 1) {
        return 1;
    }
    totalCalls += 2;
    totalAdds++;

    return FibRec(n - 2) + FibRec(n - 1);
}

double FibRec1(int n) { 
    double oneBack = 1.0;
    double twoBack = 0.0;
    
    FibRec2(n, oneBack, twoBack);
    return oneBack;
}
    
void FibRec2 (int n, double &oneBack, double &twoBack) { // helper function for FibRec1
    double tempOneBack = 1.0;
    double tempTwoBack = 0.0;
    if(n == 0 || n == 1) {
        oneBack = tempTwoBack;
        return;
    }
    
    if(n == 2) {
        tempOneBack = oneBack;
        oneBack = tempOneBack + twoBack;
        totalMoves++;
        totalAdds++;
        twoBack = tempOneBack;
        
        if(n > 1) {
            totalCalls++;
        }
        return;
    }
   
    tempOneBack = oneBack;
    oneBack = tempOneBack + twoBack;
    totalMoves++;
    totalAdds++;
    twoBack = tempOneBack;
    
    FibRec2(n - 1, oneBack, twoBack);
    totalCalls++;

}

double GenLoop(int n, int k, double initial[], double weight[]) {
    double values[n];
    totalAdds = 0.0;
    totalCalls = 1.0;
    totalMoves = 0.0; 
    
    for(int i = 0; i <= n; ++i) {
        if(i < k) { // values before k
            values[i] = weight[i] * initial[i];
        }

        if(k == 2 && i >= k) {
            values[i] = values[i - 2] + values[i - 1];
            totalAdds++;
            totalMoves++;
        }
        
        if(k == 3 && i >= k) {
            values[i] = values[i - 1] + values[i - 2] + values[i - 3];
            totalAdds+=2;
            totalMoves++;

        }

        if(k == 4 && i >= k) { 
            values[i] = values[i - 1] + values[i - 2] + values[i - 3] + values[i - 4];
            totalAdds+=3;
            totalMoves++;

        }
    }
    return values[n];
}


double GenRec ( int n, int k, double initial[], double weight[] ) {
    double back[ k + 1 ];

    if(n < k + 1) {
        return initial[n];
    }
    else {
        for(int i = 0; i < k; ++i) {
            ++totalMoves;
            back[i] = initial[i];
        }
        GenRec2(n, k, initial, weight, back);
        return back[n % k]; //returning passed in value in back array
    }
}

void GenRec2 (int n, int k, double initial[], double weight[], double back[] ) {
    double sum = 0.0;
    totalCalls = 1.0;
    totalAdds = 0.0;
    totalMoves = 0.0;

    if(n == 0) {
        return;
    }
    for(int i = 0; i < k; ++i) {
        sum += weight[i] * back[i];
        totalAdds++;
    }
    back[n % k] = sum;
   
    ++totalCalls;

    GenRec2(n - 1, k, initial, weight, back);
}