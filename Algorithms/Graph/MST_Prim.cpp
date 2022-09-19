// Then which of Allah's favor will you deny?
// problem-url: https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/tutorial/
#include "bits/stdc++.h"
#define all(v) v.begin(), v.end()
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

bool vis[10002];
vector<PII> adj[10002];

LL MST(int i) {
  LL ans = 0;
  PII e;
  priority_queue<PII, vector<PII>, greater<PII>> pq;
  pq.emplace(0, i);
  while(pq.size()) {
    e = pq.top();
    pq.pop();
    if(vis[e.second]) continue;

    vis[e.second] = true;
    ans += e.first;
    for(auto [w, v] : adj[e.second]) {
      if(not vis[v])
        pq.emplace(w, v);
    }
  }

  return ans;
}

void magic() {
  int n, m, u, v, w;
  cin >> n >> m;
  while(m--) {
    cin >> u >> v >> w;
    u--; v--;
    adj[u].emplace_back(w, v);
    adj[v].emplace_back(w, u);
  }

  cout << MST(0);
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

