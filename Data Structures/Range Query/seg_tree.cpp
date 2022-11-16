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

// Finds in range [first, last]
template<typename T> struct seg_tree {
  vector<T> Tree;
  seg_tree() {}
  seg_tree(vector<T> &a) : Tree(vector<T>(4*a.size() + 4)) { build(1, a.size(), a); }

  T build(int l, int r, vector<T> &a, int n = 1) {
    if(l == r) return Tree[n] = a[l];
    int m = (l + r) >> 1;
    return Tree[n] = f(build(l, m, a, 2*n), build(m + 1, r, a, 2*n + 1));
  }

  T query(int l, int r, const int i, const int j, int n = 1) {
    if(l >= i and r <= j) return Tree[n];
    if(i > r or j < l) return 1e18;
    int m = (l + r) >> 1;
    return f(query(l, m, i, j, 2*n), query(m + 1, r, i, j, 2*n + 1));
  }

  T update(int l, int r, const int i, const T v, int n = 1) {
    if(i > r or i < l) return 1e18;
    if(l == r) return Tree[n] = v;
    int m = (l + r) >> 1;
    return Tree[n] = f(update(l, m, i, v, 2*n), update(m, r, i, v, 2*n + 1));
  }

private:
  T f(T a, T b) { return min(a, b); }
};

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int n;
  cin >> n;
  seg_tree<LL> s;
  s.Tree.assign(4*n + 4, 1e18);
  for(int i = 1; i <= n; i++) {
    LL x;
    cin >> x;
    s.update(1, n + 1, i, x);
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

