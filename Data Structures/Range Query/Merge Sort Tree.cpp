const int N = 1e5 + 1;
int n, a[N];
vector<int> tr[N<<2];

void merge_sort(int l=0, int r=n-1, int u=1) {
    if (l == r) {
        tr[u] = {a[l]};
        return;
    }
    int m = l+r >> 1;
    merge_sort(l, m, u<<1);
    merge_sort(m+1, r, u<<1|1);
    tr[u].resize(tr[u<<1].size() + tr[u<<1|1].size());
    merge(all(tr[u<<1]), all(tr[u<<1|1]), tr[u].begin());
}

int query(int ql, int qr, int x, int l=0, int r=n-1, int u=1) {
    if (ql > r or qr < l) return 0;
    if (ql <= l and r <= qr)
      return upper_bound(all(tr[u]), x) - tr[u].begin();
    int m = l+r >> 1;
    return query(ql, qr, x, l, m, u<<1) + query(ql, qr, x, m+1, r, u<<1|1);
}
