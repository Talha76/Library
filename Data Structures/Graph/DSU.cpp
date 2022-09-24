// Then which of Allah's favor will you deny?
#include "bits/stdc++.h"
#define all(v) v.begin(), v.end()
using namespace std;
typedef long long LL;

struct DSU {
  vector<int> parent;
  vector<int> Size;

  DSU(int n):parent(vector<int>(n)), Size(vector<int>(n, 1)) { iota(all(parent), 0); }

  int find(int i) { return parent[i] == i ? i : parent[i] = find(parent[i]); }

  void merge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return;
    if(Size[u] < Size[v]) swap(u, v);
    parent[v] = u;
    Size[u] += Size[v];
  }
};

void magic() {
  
}

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while(T--) {
    magic();
    cout << "\n";
  }

  return 0;
}

