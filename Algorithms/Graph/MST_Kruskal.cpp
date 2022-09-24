// Then which of Allah's favor will you deny?
// author: Mushfiq_Talha
// problem-url: https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/tutorial/
#include "bits/stdc++.h"
#define all(v) v.begin(), v.end()
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

LL MST(int n, vector<array<int, 3>> &edges) {
  struct DSU {
    vector<int> parent;
    vector<int> Size;

    DSU(int n):parent(vector<int>(n)), Size(vector<int>(n, 1)) { iota(all(parent), 0); }

    int root(int i) { return parent[i] == i ? i : parent[i] = root(parent[i]); }

    void merge(int u, int v) {
      u = root(u); v = root(v);
      if(u == v) return;
      if(Size[u] < Size[v]) swap(u, v);
      parent[v] = u;
      Size[u] += Size[v];
    }
  };
  DSU dsu(n);
  LL ans = 0;
  priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;
  for(auto &i : edges) pq.emplace(i);

  for(array<int, 3> a; --n and pq.size(); ) {
    a = pq.top();
    pq.pop();
    if(dsu.root(a[1]) == dsu.root(a[2])) {
      n++;
      continue;
    }
    ans += a[0];
    dsu.merge(a[1], a[2]);
  }

  return ans;
}

void magic() {
  int n, m, u, v, w;
  vector<array<int, 3>> edges;
  cin >> n >> m;
  while(m--) {
    cin >> u >> v >> w;
    u--; v--;
    edges.push_back({w, u, v});
  }

  cout << MST(n, edges);
}

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int T = 1;
  while(T--) {
    magic();
    cout << "\n";
  }

  return 0;
}

