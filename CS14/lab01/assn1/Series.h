#ifndef SERIES_H
#define SEREIS_H

#include <iostream>
using namespace std;

extern int totalAdds, totalCalls, totalMoves;

class Series{
  private:
    int k;
    double* weight;
    double sequence[100];
    int biggest_known;
    void GenRec2(int n, double[]);
    
  public:
    Series();
    Series(int, double[], double[]);
    ~Series();
    void set_k(int k);
    void set_weights(double[]);
    void set_initial(double[]);
    double get_val(int n);
    double GenLoop(int n);
    double GenRec(int n);
    double GenRec1(int n);
};
#endif