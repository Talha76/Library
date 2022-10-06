// Then which of Allah's favor will you deny?
// problem-url: https://www.spoj.com/problems/RMQSQ/
// author: Mushfiq_Talha
#ifdef MUSHFIQ_DEBUG
#include "dbg.h"
#else
#define dbg(...) {}
#endif
#include "bits/stdc++.h"
#define all(v) v.begin(), v.end()
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

// Finds in range [first, last)
template<typename T> struct seg_tree {
  vector<T> tre;
  seg_tree() {}
  seg_tree(vector<T> &a) : tre(vector<T>(4*a.size() + 4)) {}
  T build(int l, int r, int n = 1) {
    int m = (l + r) >> 1;
    return tre[n] = f(build(l, m, 2*n), build(m, r, 2*n + 1));
  }

  T query(int l, int r, const int i, const int j, int n = 1) {
    if(l >= i and r <= j)
      return tre[n];
    if(i >= r or j <= l)
      return INT_MAX;

    int m = (l + r) >> 1;
    return f(query(l, m, i, j, 2*n), query(m, r, i, j, 2*n + 1));
  }

  T update(int l, int r, const int i, const T v, int n = 1) {
    if(r - l == 1 and l == i)
      return tre[n] = v;
    if(i >= r or i < l)
      return INT_MAX;

    int m = (l + r) >> 1;
    return tre[n] = f(update(l, m, i, v, 2*n), update(m, r, i, v, 2*n + 1));
  }

private:
  T f(T a, T b) { return min(a, b); }
};

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int n;
  cin >> n;
  int x;
  seg_tree<int> s;
  s.tre.assign(4*n + 4, INT_MAX);
  for(int i = 0; i < n; i++) {
    cin >> x;
    s.update(1, n + 1, i + 1, x);
  }

  int q;
  cin >> q;
  while(q--) {
    int i, j;
    cin >> i >> j;
    i++; j += 2;
    cout << s.query(1, n + 1, i, j) << endl;
  }

  return 0;
}

