#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()

using namespace std;

typedef long long ll;

class BigInt {
  BigInt multiply(const char c, int n) {
    BigInt a; int carry = 0;
    while(n--) a.s += "0";
    for(int i = 0; i < s.size(); i++) {
      int x = (s[i] - 48)*(c - 48) + carry;
      carry = x / 10;
      a.s += x % 10 + 48;
    }
    a.s += carry + 48;
    a.normalize();
    return a;
  }

public:
  string s;

  // Constructor
  BigInt() {} // Default
  BigInt(const string &a) { s = a; reverse(all(s)); normalize(); }
  BigInt(const int &a) { s = to_string(a); reverse(all(s)); normalize(); }
  BigInt(const ll &a) { s = to_string(a); reverse(all(s)); normalize(); }

  // Normalization
  void normalize() { while(!s.empty() && s.back() == 48) s.pop_back(); }

  // Length 
  unsigned int size() const { return s.size(); }

  // IO Operator
  friend istream& operator >> (istream &i, BigInt &a)
  { i >> a; reverse(all(a.s)); a.normalize(); return i;}
  friend ostream& operator << (ostream &o, BigInt a)
  { reverse(all(a.s)); o << a.s; return o; }

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
  BigInt operator + (BigInt a) {
    BigInt c; bool carry = false;
    while(s.size() != a.s.size()) (s.size() < a.s.size() ? s : a.s) += "0";
    for(int i = 0; i < s.size(); i++) {
      int x = carry + s[i] + a.s[i] - 96;
      c.s += x % 10 + 48;
      carry = x / 10;
    }
    c.s += carry + 48; c.normalize(); this->normalize();
    return c;
  }
  BigInt operator - (BigInt);
  BigInt operator * (BigInt a) {
    BigInt c; int pow = 0;
    for(int i = 0; i < a.s.size(); i++) {
      BigInt prod = multiply(a.s[i], pow++);
      c += prod;
    }
    c.normalize();
    return c;
  }
  BigInt operator / (BigInt);

  // Some extra operators
  BigInt operator += (BigInt a) {
    *this = *this + a;
    return *this;
  }
  BigInt operator -= (BigInt a) {}
  BigInt operator *= (BigInt a) {
    *this = *this * a;
    return *this;
  }
  BigInt operator /= (BigInt a) {}
};

int main() {
    BigInt a, b;
    cin >> a >> b;
    cout << (a > b) << '\n';

    return 0;
}
