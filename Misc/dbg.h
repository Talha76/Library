#include <iostream>
#include <algorithm>
using namespace std;

/*
 * TODO:
 *    - static array dbg
 */

// primitive types
void show(int x) {cerr << x;}
void show(long long x) {cerr << x;}
void show(double x) {cerr << x;}
void show(char x) {cerr << '\'' << x << '\'';}
void show(const string &x) {cerr << '"' << x << '"';}
void show(bool x) {cerr << boolalpha << x;}

// forward declaration
template<typename T, typename V> void show(pair<T, V>);
template<typename... Ts> void show(tuple<Ts...> const&);
template<typename T> void show(T);

// pair
template<typename T, typename V> void show(pair<T, V> x) {
  cerr << '{'; show(x.first); cerr << ", "; show(x.second); cerr << '}';
}

// tuple
template<size_t idx> struct tuple_print {
  template<typename... Ts> static void print(const tuple<Ts...>& x) {
    tuple_print<idx-1>::print(x);
    cerr << ", ";
    show(get<idx>(x));
  }
};
template<> struct tuple_print<0> {
  template<typename... Ts> static void print(const tuple<Ts...>& x) {show(get<0>(x));}
};
template<typename... Ts> void show(tuple<Ts...> const& x) {
  cerr << '{';
  tuple_print<sizeof...(Ts)-1>::print(x);
  cerr << '}';
}

// other containers
template<typename T> void show(T x) {
  int f = 0; cerr << "{";
  for (auto &i: x) cerr << (f++ ? ", " : ""), show(i);
  cerr << "}";
}

void debug_out(string s) {}
template <typename T, typename... V> void debug_out(string s, T t, V... v) {
  s.erase(remove(s.begin(), s.end(), ' '), s.end());
  cerr << "        "; // 8 spaces
  cerr << s.substr(0, s.find(','));
  s = s.substr(s.find(',') + 1);
  cerr << " = ";
  show(t);
  cerr << endl;
  debug_out(s, v...);
}

#define dbg(x...) cerr << "LINE: " << __LINE__ << endl; debug_out(#x, x);
