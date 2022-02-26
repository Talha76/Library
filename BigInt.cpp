#include <bits/stdc++.h>

using namespace std;

class BigInt {
    string s;

public:
    // Constructor
    BigInt() {} // Default
    BigInt(const string &a) { s = a; }

    // Length 
    unsigned int size() const { return s.size(); }

    // IO Operator
    friend istream& operator >> (istream&, BigInt&);
    friend ostream& operator << (ostream&, BigInt&);

    // Assignment Operator
    void operator = (const string& a) { s = a; }

    // Equality Operator
    bool operator == (const BigInt &a) { return a.s == s; }
    bool operator != (const BigInt &a) { return a.s != s; }

    // Relational Operator
    bool operator > (const BigInt&);
    bool operator >= (const BigInt&);
    bool operator < (const BigInt&);
    bool operator <= (const BigInt&);

    // Unary Operator
    BigInt operator - ();

    // Binary Operator
    BigInt operator + (const BigInt&);
    BigInt operator - (const BigInt&);
    BigInt operator * (const BigInt&);
    BigInt operator / (const BigInt&);
};

// IO Operator
istream& operator >> (istream &in, BigInt &a) {
    in >> a.s;
    reverse(a.s.begin(), a.s.end());
    return in;
}

ostream& operator << (ostream &out, BigInt &a) {
    reverse(a.s.begin(), a.s.end());
    out << a.s;
    return out;
}

// Relational Operator
bool BigInt::operator > (const BigInt &a) {
    if(a.size() != s.size())
        return s.size() > a.size();

    return true;
}

int main() {
    BigInt a, b;
    cin >> a >> b;
    cout << (a > b) << '\n';

    return 0;
}