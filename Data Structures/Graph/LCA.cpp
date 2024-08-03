namespace LCA {
  typedef vector<vector<int>> adj_list;
  inline int lg(int n) { return n ? 31 - __builtin_clz(n) : -1; }

  pair<adj_list, vector<int>> init(int u, adj_list const& g) {
    int n = g.size(), k = lg(n) + 1;
    adj_list anc(n, vector<int>(k));
    vector<int> lvl(n, -1);
    lvl[u] = 0;
    queue<PII> q;
    for (q.emplace(u, -1); q.size(); q.pop()) {
      auto [u, p] = q.front();
      anc[u][0] = p;
      for (int i = 1; i < k; i++)
        anc[u][i] = ~anc[u][i-1] ? anc[anc[u][i-1]][i-1] : -1;
      for (int v: g[u]) if (lvl[v] < 0) {
        lvl[v] = lvl[u] + 1;
        q.emplace(v, u);
      }
    }
    return {anc, lvl};
  }

  int getAnc(int u, int k, adj_list const& anc) {
    for (int i = 0; ~u and k; i++, k >>= 1) if (k & 1)
      u = anc[u][i];
    return u;
  }

  int lca(int u, int v, adj_list const& anc, vector<int> const& lvl) {
    if (lvl[u] < lvl[v]) swap(u, v);
    u = getAnc(u, lvl[u] - lvl[v], anc);
    if (u == v) return u;
    int k = anc[0].size();
    for (int i = k - 1; ~i; i--)
      if (anc[u][i] != anc[v][i])
        u = anc[u][i], v = anc[v][i];
    return anc[u][0];
  }

  int dist(int u, int v, adj_list const& anc, vector<int> const& lvl) {
    return lvl[u] + lvl[v] - 2 * lvl[lca(u, v, anc, lvl)];
  }
}
