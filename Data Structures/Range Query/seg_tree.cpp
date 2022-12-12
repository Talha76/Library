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
private:
  int n;
  vector<T> a, Tree;

  T f(T a, T b) { return min(a, b); }

  T seg_query(const int i, const int j, int l, int r, int node = 1) {
    if(l >= i and r <= j) return Tree[node];
    if(i > r or j < l) return 1e18;
    int m = (l + r) >> 1;
    return f(seg_query(l, m, i, j, 2*node), seg_query(m + 1, r, i, j, 2*node + 1));
  }

  T seg_update(const int i, const T v, int l, int r, int node = 1) {
    if(i > r or i < l) return Tree[node];
    if(l == r) return Tree[node] = v;
    int m = (l + r) >> 1;
    return Tree[node] = f(seg_update(l, m, i, v, 2*node), seg_update(m + 1, r, i, v, 2*node + 1));
  }
public:
  seg_tree() {}
  seg_tree(vector<T> &a) : n(a.size()), a(a), Tree(vector<T>(4*a.size())) { a.insert(a.begin(), -1); build(1, n); }

  T build(int l, int r, int node = 1) {
    if(l == r) return Tree[node] = a[l];
    int m = (l + r) >> 1;
    return Tree[n] = f(build(l, m, 2*node), build(m + 1, r, 2*node + 1));
  }

  T query(const int &i, const int &j) { return seg_query(i, j, 1, n); }

  T update(const int &i, const int &v) { return seg_update(i, v, 1, n); }
};

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int n;
  cin >> n;
  vector<LL> a(n);
  for(auto &i : a)
    cin >> i;
  
  seg_tree<LL> s(a);
  int q;
  cin >> q;
  while(q--) {
    int i, j;
    cin >> i >> j;
    i++; j++;
    cout << s.query(i, j) << endl;
  }

  return 0;
}

