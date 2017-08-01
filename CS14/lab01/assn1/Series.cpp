#include "Series.h"

Series::Series(){
    biggest_known = -1;
    weight = 0;
}

Series::Series(int _k, double _initial[], double _weight[]){
    set_k(_k);
    set_initial(_initial);
    set_weights(_weight);
}

void Series::set_k(int _k){
    k = _k;
    delete[] weight;
    weight = new double[k];
}

void Series::set_initial(double initial[]){
    for(int i = 0 ; i < k ; ++i){
        sequence[i] = initial[i];
    }
    biggest_known = k - 1;
}

void Series::set_weights(double _weight[]){
    for(int i = 0 ; i < k ; ++i){
        weight[i] = _weight[i];
    }
}

double Series::get_val(int n){
    return GenLoop(n);
}

double Series::GenLoop(int n){
    if( n <= biggest_known){
        return sequence[n];
    }
    
    for(int i = biggest_known + 1; i <= n; ++i){
        double tmp = 0;
        for(int j = 0; j < k; ++j){
            tmp  += sequence[i - k + j] * weight[j];
        }
        sequence[i] = tmp;
        biggest_known = i;
        totalAdds += k - 1;
    }
    return sequence[n];
}

double Series::GenRec(int n){
    if(n <= biggest_known){
        return sequence[n];
    }
    totalAdds += k - 1;
    totalCalls += k;
    double fib = 0;
    for(int i = 1; i<= k; ++i)
        fib += GenRec(n-i)*weight[k-i];
    
    sequence[n] = fib;
    biggest_known = n;
    return fib;
}

double Series::GenRec1(int n){
    if( n <= biggest_known){
        return sequence[n];
    }
    double back[k];
    GenRec2(n,back);
    return back[n%k];
}

void Series::GenRec2(int n, double back[]){
    
    if(n <= biggest_known){
        for(int i = 0; i < k; ++i)
            back[i] = sequence[biggest_known - k + i + 1];
    }
    else{
        totalCalls++;
        totalAdds += k-1;
        
        GenRec2(n-1,back);
        double fib = 0;
        for(int i = 1; i<= k; ++i)
            fib += back[(n-i)%k]*weight[k-i];
        back[n%k] = fib;
        totalMoves++;
        sequence[n] = fib;
        biggest_known = n;
    }
}

Series::~Series(){
    delete[] weight;
}