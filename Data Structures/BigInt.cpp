#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()

using namespace std;

typedef long long ll;

class big_int {
  big_int multiply(const char c, int n) {
    big_int a; int carry = 0;
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
  big_int() {} // Default
  big_int(const string &a) { s = a; reverse(all(s)); normalize(); }
  big_int(const int &a) { s = to_string(a); reverse(all(s)); normalize(); }
  big_int(const ll &a) { s = to_string(a); reverse(all(s)); normalize(); }

  // Normalization
  void normalize() { while(!s.empty() && s.back() == 48) s.pop_back(); }

  // Length 
  unsigned int size() const { return s.size(); }

  // IO Operator
  friend istream& operator >> (istream &i, big_int &a)
  { i >> a.s; reverse(all(a.s)); a.normalize(); return i;}
  friend ostream& operator << (ostream &o, big_int a)
  { reverse(all(a.s)); o << a.s; return o; }

  // Assignment Operator
  void operator = (const string& a) { s = a; }

  // Equality Operator
  bool operator == (const big_int &a) { return a.s == s; }
  bool operator != (const big_int &a) { return a.s != s; }

  // Relational Operator
  bool operator > (const big_int& a) {
    if (this->s.size() != a.s.size()) return this->s.size() > a.s.size();
    return this->s > a.s;
  }
  bool operator >= (const big_int& a) {
    return *this > a or *this == a;
  }
  bool operator < (const big_int& a) {
    if (this->s.size() != a.s.size()) return this->s.size() < a.s.size();
    return this->s < a.s;
  }
  bool operator <= (const big_int& ) {
    return *this < a or *this == a;
  }

  // Unary Operator
  big_int operator - ();

  // Binary Operator
  big_int operator + (big_int a) {
    big_int c; bool carry = false;
    while(s.size() != a.s.size()) (s.size() < a.s.size() ? s : a.s) += "0";
    for(int i = 0; i < s.size(); i++) {
      int x = carry + s[i] + a.s[i] - 96;
      c.s += x % 10 + 48;
      carry = x / 10;
    }
    c.s += carry + 48; c.normalize(); this->normalize();
    return c;
  }
  big_int operator - (big_int);
  big_int operator * (big_int a) {
    big_int c; int pow = 0;
    for(int i = 0; i < a.s.size(); i++) {
      big_int prod = multiply(a.s[i], pow++);
      c += prod;
    }
    c.normalize();
    return c;
  }
  big_int operator / (big_int);

  // Some extra operators
  big_int operator += (big_int a) {
    *this = *this + a;
    return *this;
  }
  big_int operator -= (big_int a);
  big_int operator *= (big_int a) {
    *this = *this * a;
    return *this;
  }
  big_int operator /= (big_int a);
};

int main() {
    BigInt a, b;
    cin >> a >> b;
    cout << (a > b) << '\n';

    return 0;
}
