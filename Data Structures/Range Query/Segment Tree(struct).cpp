/*
 * ***Important:*** Declare 'I' and 'None' in a local scope
 *                  Declaring these in global scope gives compilation error
 *                  Also use g++20 or later versions
 */
template<typename DT, auto I, auto update_fn, auto query_fn>
struct segtree {
    vector<DT> val;
    int L, R;

    segtree(vector<DT> v, int _L, int _R) : val(v.size()<<2), L(_L), R(_R) { build(L, R, v); }
    void build(int l, int r, vector <DT> const &v, int u = 1) {
        if(l == r) {
            val[u] = v[l];
            return;
        }
        int m = l+r >> 1, lft = u << 1, ryt = lft | 1;
        build(l, m, v, lft);
        build(m+1, r, v, ryt);
        val[u] = query_fn(val[lft], val[ryt], l, r);
    }
    void update(int i, DT uval, int l = -1, int r = -1, int u = 1) {
        l = ~l ? l : L, r = ~r ? r : R;
        if (i < l or i > r) return;
        if(i == l and i == r) {
            val[u] = update_fn(val[u], uval, l, r);
            return;
        }
        int m = l+r >> 1, lft = u << 1, ryt = lft | 1;
        update(i, uval,  l,  m, lft);
        update(i, uval, m+1, r, ryt);
        val[u] = query_fn(val[lft], val[ryt], l, r);
    }
    DT query(int ql, int qr, int l = -1, int r = -1, int u = 1) {
        l = ~l ? l : L, r = ~r ? r : R;
        if (qr < l or ql > r) return I;
        if (ql <= l and r <= qr) return val[u];
        int m = l+r >> 1, lft = u << 1, ryt = lft | 1;
        DT ansl = query(ql, qr, l, m, lft);
        DT ansr = query(ql, qr, m + 1, r, ryt);
        return query_fn(ansl, ansr, l, r);
    }
};
