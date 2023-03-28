#include <bits/stdc++.h>
using namespace std;

// Unfortunately big_int a = "100" -> statement doesn't work
struct big_int {
#define all(x) x.begin(), x.end()
private:
  string s;
  int sign;

  big_int normalize(int sign = 1) {
    this->sign = sign;
    for(int i = this->size() - 1; i > 0 && this->s[i] == '0'; i--) this->s.erase(this->s.begin() + i);
    if(this->size() == 1 && this->s[0] == '0') this->sign = 1;
    return (*this);
  }
  bool cmp(const big_int& a) const {
    if(this->size() != a.size()) return this->size() < a.size();
    for(int i = this->size() - 1; i >= 0; i-- ) if(this->s[i] != a[i] ) return this->s[i] < a[i];
    return false;
  }

public:
  // Constructor
  big_int() {}
  big_int(const string& a) { *this = a; }
  big_int(const long long& a) { *this = a; }

  // Length 
  size_t size() const { return s.size(); }

  // Sub-script operator
  char operator [] (const size_t& i) const { return this->s[i]; }
  char& operator[] (const size_t& i) { return this->s[i]; }

  // IO Operator
  friend istream& operator >> (istream &i, big_int &a) {
    i >> a.s;
    a.s = (a[0] == '-' ? a.s.substr(1) : a.s);
    reverse(all(a.s));
    a.normalize(isalnum(a.s[0]) ? 1 : -1);
    return i;
  }
  friend ostream& operator << (ostream &o, const big_int& a) {
    if (a.sign == -1) o << '-';
    for (int i = (int)a.size() - 1; ~i; i--) o << a[i];
    return o;
  }

  // Assignment Operator
  big_int operator = (const char* a) {
    this->s.assign(a);
    this->s = (this->s[0] == '-' ? this->s.substr(1) : this->s);
    reverse(all(this->s));
    this->normalize(strlen(a) and a[0] == '-' ? -1 : 1);
    return *this;
  }
  big_int operator = (const string& a) {
    this->s = (a[0] == '-' ? a.substr(1) : a);
    reverse(all(this->s));
    this->normalize(a.size() and a[0] == '-' ? -1 : 1);
    return *this;
  }
  big_int operator = (const long long& a) {
    this->s = to_string(abs(a));
    reverse(all(this->s));
    this->normalize(a < 0 ? -1 : 1);
    return *this;
  } 

  // Comparison Operator
  bool operator == (const big_int &a) const { return a.s == this->s and a.sign == this->sign; }
  bool operator != (const big_int &a) const { return not (*this == a); }
  bool operator > (const big_int& a) const {
    if (this->sign != a.sign) return a.sign == -1;
    bool ret;
    if (this->size() != a.size()) ret = this->size() > a.size();
    else ret = this->s > a.s;
    return *this != a and (a.sign == 1 ? ret : not ret);
  }
  bool operator >= (const big_int& a) const {
    if (this->sign != a.sign) return a.sign == -1;
    return *this > a or *this == a;
  }
  bool operator < (const big_int& a) const {
    if (this->sign != a.sign) return a.sign == 1;
    bool ret;
    if (this->size() != a.size()) ret = this->size() < a.size();
    else ret = this->s < a.s;
    return *this != a and (a.sign == 1 ? ret : not ret);
  }
  bool operator <= (const big_int& a) const {
    if (this->sign != a.sign) return a.sign == 1;
    return *this < a or *this == a;
  }

  // Unary Operator
  big_int operator - () {
    big_int c = *this;
    c.sign *= -1;
    return c;
  }

  // Binary Operator
  big_int operator + (big_int a) {
    if (this->sign != a.sign) return *this - (-a);
    big_int c;
    for( int i = 0, carry = 0; i < (int)a.size() || i < (int)this->size() || carry; i++ ) {
      carry += (i < (int)this->size() ? this->s[i] - 48 : 0) + (i < (int)a.size() ? a[i] - 48 : 0);
      c.s += (carry % 10 + 48);
      carry /= 10;
    }
    return c.normalize(this->sign);
  }
  big_int operator - (big_int a) {
    if (this->sign != a.sign) return *this + (-a);
    if (cmp(a)) return -(a - *this);
    big_int c;
    for(int i = 0, borrow = 0; i < (int)this->size(); i++) {
      borrow = this->s[i] - borrow - (i < (int)a.size() ? a[i] : 48);
      c.s += borrow >= 0 ? borrow + 48 : borrow + 58;
      borrow = borrow >= 0 ? 0 : 1;
    }
    return c.normalize(this->sign);
  }
  big_int operator * (big_int a) {
    big_int c("0");
    for( int i = 0, k = this->s[i]; i < (int)this->size(); i++, k = this->s[i] ) {
      while(k-- - 48) c += a;
      a.s.insert(a.s.begin(), '0');
    }
    return c.normalize(sign * a.sign);
  }
  big_int operator / (big_int a) {
    if(a.size() == 1 and a.s[0] == '0') a.s[0] /= (a.s[0] - 48) ;
    big_int c("0"), d;
    for(int j = 0; j < (int)this->size(); j++) d.s += "0";
    int dSign = sign * a.sign; a.sign = 1;
    for(int i = this->size() - 1; i >= 0; i--) {
      c.s.insert(c.s.begin(), '0');
      c += this->s.substr(i, 1);
      while(!(c < a)) c -= a, d.s[i]++;
    }
    return d.normalize(dSign);
  }
  big_int operator % (big_int a) {
    if (a.sign == -1) a = -a;
    if(a.size() == 1 && a.s[0] == '0') a.s[0] /= (a.s[0] - 48 ) ;
    big_int c("0");
    int cSign = sign * a.sign; a.sign = 1;
    for(int i = this->size() - 1; i >= 0; i--) {
      c.s.insert(c.s.begin(), '0');
      c += this->s.substr( i, 1 );
      while(!(c < a)) c -= a;
    }
    return c.normalize(cSign);
  }
  big_int operator += (const big_int& a) {
    *this = *this + a;
    return this->normalize(this->sign);
  }
  big_int operator -= (const big_int& a) {
    *this = *this - a;
    return this->normalize(this->sign);
  }
  big_int operator *= (const big_int& a) {
    *this = *this * a;
    return this->normalize(this->sign);
  }
  big_int operator /= (const big_int& a) {
    *this = *this / a;
    return this->normalize(this->sign);
  }
  big_int operator %= (const big_int& a) {
    *this = *this % a;
    return this->normalize(this->sign);
  }
};

big_int add_test(big_int a, big_int b) { return a += b; }
big_int subtract_test(big_int a, big_int b) { return a -= b; }
big_int multiply_test(big_int a, big_int b) { return a *= b; }
big_int divide_test(big_int a, big_int b) { return a /= b; }
big_int mod_test(big_int a, big_int b) { return a %= b; }

void whole_test(big_int a, big_int b, long long c, long long d) {
  cout << "Testing a = " << a << ", b = " << b << endl;
  cout << "a = " << a << ", b = " << b << endl;
  cout << "a + b  = " << a+b << '\n';
  cout << "a - b  = " << a-b << endl;
  cout << "a * b  = " << a*b << endl;
  cout << "a / b  = " << a/b << endl;
  cout << "a % b  = " << a%b << endl;
  cout << "a += b = " << add_test(a, b) << endl;
  cout << "a -= b = " << subtract_test(a, b) << endl;
  cout << "a *= b = " << multiply_test(a, b) << endl;
  cout << "a /= b = " << divide_test(a, b) << endl;
  cout << "a %= b = " << mod_test(a, b) << endl;
  cout << "a > b  = " << (a > b) << endl;
  cout << "a >= b = " << (a >= b) << endl;
  cout << "a < b  = " << (a < b) << endl;
  cout << "a <= b = " << (a <= b) << endl;
  cout << "a == b = " << (a == b) << endl;
  cout << "a != b = " << (a != b) << endl;
  cout << endl;
  assert(a == c); assert(b == d);
  assert(a + b == c + d); assert(add_test(a, b) == c + d);
  assert(a - b == c - d); assert(subtract_test(a, b) == c - d);
  assert(a * b == c * d); assert(multiply_test(a, b) == c * d);
  assert(a / b == c / d); assert(divide_test(a, b) == c / d);
  assert(a % b == c % d); assert(mod_test(a, b) == c % d);
  assert((a > b) == (c > d)); assert((a >= b) == (c >= d));
  assert((a < b) == (c < d)); assert((a <= b) == (c <= d));
  assert((a == b) == (c == d)); assert((a != b) == (c != d));
}

int main() {
    big_int i, j;
    cin >> i >> j;
    cout << "Tesing cin >> i >> j" << endl;
    cout << "i = " << i << ", j = " << j << endl;
    cout << endl;

    big_int a("9"), b("2");
    cout << "Testing: big_int a(\"9\"), b(\"2\")" << endl;
    cout << "a = " << a << ", b = " << b << endl; assert(a == big_int(9)); assert(b == big_int(2));
    cout << endl;

    big_int c(9), d(2);
    cout << "Testing: big_int c(9), d(2)" << endl;
    cout << "c = " << c << ", d = " << d << endl; assert(c == big_int(9)); assert(d == big_int(2));
    cout << endl;

    big_int e = a, f = b;
    cout << "Testing: big_int e = a, f = b" << endl;
    cout << "e = " << e << ", f = " << f << endl; assert(e == big_int(9)); assert(f == big_int(2));
    cout << endl;

    big_int g = 9, h = 2;
    cout << "Testing: big_int g = 9, h = 2" << endl;
    cout << "g = " << g << ", h = " << h << endl; assert(g == big_int(9)); assert(h == big_int(2));
    cout << endl;

    a = "9", b = "2";
    cout << "Testing: a = \"9\", b = \"2\"" << endl;
    cout << "a = " << a << ", b = " << b << endl; assert(a == big_int(9)); assert(b == big_int(2));
    cout << endl;

    a = 9, b = 2;
    cout << "Testing: a = 9, b = 2" << endl; 
    cout << "a = " << a << ", b = " << b << endl; assert(a == big_int(9)); assert(b == big_int(2));
    cout << endl;

    for (int i = -4; i < 6; i += 4) {
      for (int j = -6; j < 7; j += 2) if (j)
        whole_test(i, j, i, j);
    }

    return 0;
}

