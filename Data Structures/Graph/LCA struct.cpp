struct LCA {
  int n, k;
  vector<int> lvl;
  vector<vector<int>> anc;
  inline int lg(int n) { return n ? 31 - __builtin_clz(n) : -1; }
  LCA(vector<vector<int>> const& g, int u) : n(g.size()), k(lg(n)+1), lvl(n, -1), anc(n, vector<int>(k, -1)) {
    lvl[u] = 0;
    queue<PII> q;
    for (q.emplace(u, -1); q.size(); q.pop()) {
      auto [u, p] = q.front();
      anc[u][0] = p;
      for (int i = 1; i < k and ~anc[u][i-1]; i++)
        anc[u][i] = anc[anc[u][i-1]][i - 1];
      for (int v: g[u]) if (lvl[v] < 0) {
        lvl[v] = lvl[u] + 1;
        q.emplace(v, u);
      }
    }
  }
  int getAnc(int u, int k) {
    for (int i = 0; ~u and k; i++, k >>= 1) if (k & 1)
      u = anc[u][i];
    return u;
  }
  int lca(int u, int v) {
    if (lvl[u] < lvl[v]) swap(u, v);
    u = getAnc(u, lvl[u] - lvl[v]);
    if (u == v) return u;
    for (int i = k - 1; ~i; i--)
      if (anc[u][i] != anc[v][i])
        u = anc[u][i], v = anc[v][i];
    return anc[u][0];
  }
  int dist(int u, int v) {
    return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];
  }
};
