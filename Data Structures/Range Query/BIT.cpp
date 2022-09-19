// problem-url: https://lightoj.com/problem/curious-robin-hood
// Then which of Allah's favor will you deny?
#include "bits/stdc++.h"
#define all(v) v.begin(), v.end()
using namespace std;
typedef long long LL;

// 1-indexing
template<typename T> struct BIT {
  int n;
  vector<T> Tree;

  BIT() {}
  BIT(int n): n(n) { Tree.assign(n, 0); }
  // Pass a 1-indexed vector
  BIT(vector<T> &a): n(a.size()) {
    Tree.assign(n, 0);
    for(int i = 1; i < n; i++)
      update(i, a[i]);
  }

  void update(int i, int val) {
    for(; i < n; i += (i & -i))
      Tree[i] += val;
  }

  T query(int i) {
    T ret = 0;
    for(; i; i -= (i & -i))
      ret += Tree[i];
    return ret;
  }

  // [l, r]
  T query(int l, int r) { return query(r) - query(l - 1); }
};

void magic() {
  int n, q, x;
  cin >> n >> q;
  BIT<LL> bit(n + 1);
  for(int i = 1; i <= n; i++) {
    cin >> x;
    bit.update(i, x);
  }

  while(q--) {
    int c;
    cin >> c;
    int i, v, j;
    cin >> i;
    i++;
    switch(c) {
      case 1: {
              int ans = bit.query(i, i);
              cout << ans << "\n";
              bit.update(i, -ans);}
      break;
      case 2: {cin >> v;
              bit.update(i, v);}
      break;
      default: {cin >> j;
               cout << bit.query(j + 1, i) << "\n";}
    }
  }
}

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int T = 1, kase = 0;
  cin >> T;
  while(T--) {
    cout << "Case " << ++kase << ":\n";
    magic();
  }

  return 0;
}

