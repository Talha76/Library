#include "bits/stdc++.h"
using namespace std;

template <class T>
struct lazy_seg {
  vector<T> Tree, prop;
  lazy_seg() {}
  lazy_seg(vector<T> &a) : Tree(vector<T>(4*a.size() + 4)), prop(vector<T>(4*a.size() + 4)) { build(1, a.size(), a); }

  T build(int l, int r, vector<T> &a, int n = 1) {
    if(l == r) return Tree[n] = a[l];
    int m = (l + r) >> 1;
    return Tree[n] = f(build(l, m, a, 2*n), build(m + 1, r, a, 2*n + 1));
  }

  T update(int i, int j, int x, int l, int r, int node = 1) {}
};

int main() {
  return 0;
}
