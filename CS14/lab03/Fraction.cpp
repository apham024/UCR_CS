#include <iostream>
 
class Fraction
{
    int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
    int n, d;
 public:
    Fraction(int n, int d = 1) : n(n/gcd(n,d)), d(d/gcd(n,d)) {}
    int num() const { return n; }
    int den() const { return d; }
    Fraction& operator*=(const Fraction& rhs) {
        int new_n = n*rhs.n / gcd(n*rhs.n, d*rhs.d);
        d = d*rhs.d / gcd(n*rhs.n, d*rhs.d);
        n = new_n;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const Fraction& f){
   return out << f.num() << '/' << f.den() ;
}
bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return ((lhs.num() * rhs.den()) == (rhs.num() * lhs.den()));
}
bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() < rhs.num() * lhs.den());
}
bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() > rhs.num() * lhs.den());
}
Fraction operator*(Fraction lhs, const Fraction& rhs)
{
    return lhs *= rhs;
}
 
string replaceExtension(string str, string ext) {
    string newStr = str;
    int idx = str.rfind('.', str.length());
    if (idx>0) {
      newStr.replace(idx, ext.length(), "");
    }
    newStr += ext;
    return newStr;
}

// int main()
// {
//   Fraction f1(3,8), f2(1,2), f3(10,2), f4(6,16);
//   std::cout << f1 << '*' << f2 << '=' << f1*f2 << '\n'
//              << f2 << '*' << f3 << '=' << f2*f3 << '\n'
//              << 2  << '*' << f1 << '=' << 2 *f1 << '\n';
//   std::cout << f1 << '<' << f2 << '=' << (f1<f2) << '\n'
//              << f1 << '=' << '=' << f2 << '=' << (f1==f2) << '\n'
//              << f1 << '>' << f2 << '=' << (f1>f2) << '\n';
//   std::cout << f1 << '<' << f3 << '=' << (f1<f3) << '\n'
//              << f1 << '=' << '=' << f3 << '=' << (f1==f3) << '\n'
//              << f1 << '>' << f3 << '=' << (f1>f3) << '\n';
//   std::cout << f2 << '<' << f3 << '=' << (f2<f3) << '\n'
//              << f2 << '=' << '=' << f3 << '=' << (f2==f3) << '\n'
//              << f2 << '>' << f3 << '=' << (f2>f3) << '\n';
//   std::cout << f1 << '<' << f4 << '=' << (f1<f4) << '\n'
//              << f1 << '=' << '=' << f4 << '=' << (f1==f4) << '\n'
//              << f1 << '>' << f4 << '=' << (f1>f4) << '\n';
// }
