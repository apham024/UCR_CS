#include <iostream>
using namespace std;

class Series {
  public:
    void set_k();
    void set_weights();
    void set_initial();
    double get_val(int n);
  private:
    int k;
    int n;
    int biggest_known;
    double weight[100];
    double initial[100];
    double arr[1000];
};

void Series::set_k() {
    cout << "What is the value of k? "<< endl;
    cin >> k;
}

void Series::set_weights() {
    cout << "Weights? " << endl;
    for(unsigned i = 0; i < k; i++) {
        cin >> weight[i];
    }
}

void Series::set_initial() {
    cout << "Initial values? " << endl;
    for(unsigned i = 0; i < k; i++) {
        cin >> initial[i];
    }
}   

double Series::get_val(int n) {
    double values[n + 1];
    double biggest_known = 0.0;
    double totalAdds = 0.0;
    double totalCalls = 1.0;
    double totalMoves = 0.0; 
    
    for(int i = 0; i <= n; ++i) {
        if(i < k) { // values before k
            values[i] = weight[i] * initial[i];
            if(biggest_known < values[i]) {
            biggest_known = values[i];
            }
        }

        if(i >= k && k == 2) {
            values[i] = values[i - 2] + values[i - 1];
            totalAdds++;
            totalMoves++;
            if(biggest_known < values[i]) {
            biggest_known = values[i];
            }
        }
        
        if(i >= k && k == 3) {
            values[i] = values[i - 1] + values[i - 2] + values[i - 3];
            totalAdds+=2;
            totalMoves++;
            if(biggest_known < values[i]) {
            biggest_known = values[i];
            }
        }

        if(i >= k && k == 4) { 
            values[i] = values[i - 1] + values[i - 2] + values[i - 3] + values[i - 4];
            totalAdds+=3;
            totalMoves++;
            if(biggest_known < values[i]) {
            biggest_known = values[i];
            }
        }
        arr[i] = values[i];
    }
    return values[n];
}

