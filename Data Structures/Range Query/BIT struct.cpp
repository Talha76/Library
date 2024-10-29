// 1-indexing
template<typename T> struct BIT {
    int n;
    vector<T> Tree;
    
    BIT() {}
    BIT(int n): n(n) { Tree.assign(n, 0); }
    // Pass a 1-indexed vector
    BIT(vector<T> &a): n(a.size()) {
        Tree.assign(n, 0);
        for(int i = 1; i < n; i++) update(i, a[i]);
    }
    
    void update(int i, int val) { for(; i < n; i += (i & -i)) Tree[i] += val; }
    
    T query(int i) {
        T ret = 0;
        for(; i; i -= (i & -i)) ret += Tree[i];
        return ret;
    }
    
    // [l, r]
    T query(int l, int r) { return query(r) - query(l - 1); }
};
