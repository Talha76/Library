namespace segtree {
    const int N = 1001, M = N;
    using DT = int;
    
    int xL, xR, yL, yR;
    constexpr DT I = 0;
    DT val[N<<2][M<<2];
    
    DT merge(const DT& a, const DT& b) { return a+b; }
    
    void apply(int xu, int yu, const DT uval) { val[xu][yu] += uval; }
    
    void build_y(vector<vector<DT>> const& v, int xl, int xr, int xu, int yl=yL, int yr=yR, int yu=1) {
        if (yl == yr) {
            if (xl == xr) val[xu][yu] = v[xl][yl];
            else val[xu][yu] = merge(val[xu<<1][yu], val[xu<<1|1][yu]);
            return;
        }
        int m = yl+yr >> 1;
        build_y(v, xl, xr, xu, yl, m, yu<<1);
        build_y(v, xl, xr, xu, m+1, yr, yu<<1|1);
        val[xu][yu] = merge(val[xu][yu<<1], val[xu][yu<<1|1]);
    }
    void build_x(vector<vector<DT>> const& v, int l=xL, int r=xR, int u=1) {
        if (l != r) {
            int m = l+r >> 1;
            build_x(v, l, m, u<<1);
            build_x(v, m+1, r, u<<1|1);
        }
        build_y(v, l, r, u);
    }
    DT query_y(int qyl, int qyr, int xl, int xr, int xu, int yl=yL, int yr=yR, int yu=1) {
        if (qyl > yr or qyr < yl) return I;
        if (qyl <= yl and yr <= qyr) return val[xu][yu];
        int m = yl+yr >> 1;
        DT ans_l = query_y(qyl, qyr, xl, xr, xu, yl, m, yu<<1),
           ans_r = query_y(qyl, qyr, xl, xr, xu, m+1, yr, yu<<1|1);
        return merge(ans_l, ans_r);
    }
    DT query_x(int qxl, int qxr, int qyl, int qyr, int l=xL, int r=xR, int u=1) {
        if (qxl > r or qxr < l) return I;
        if (qxl <= l and r <= qxr) return query_y(qyl, qyr, l, r, u);
        int m = l+r >> 1;
        DT ans_l = query_x(qxl, qxr, qyl, qyr, l, m, u<<1),
           ans_r = query_x(qxl, qxr, qyl, qyr, m+1, r, u<<1|1);
        return merge(ans_l, ans_r);
    }
    void update_y(int qx, int qy, DT uval, int xl, int xr, int xu, int yl=yL, int yr=yR, int yu=1) {
        if (qy > yr or qy < yl) return;
        if (qy == yl and yl == yr) {
            if (qx > xr or qx < xl) return;
            if (xl == qx and qx == xr) apply(xu, yu, uval);
            else val[xu][yu] = merge(val[xu<<1][yu], val[xu<<1|1][yu]);
            return;
        }
        int m = yl+yr >> 1;
        update_y(qx, qy, uval, xl, xr, xu, yl, m, yu<<1);
        update_y(qx, qy, uval, xl, xr, xu, m+1, yr, yu<<1|1);
        val[xu][yu] = merge(val[xu][yu<<1], val[xu][yu<<1|1]);
    }
    void update_x(int qx, int qy, DT uval, int l=xL, int r=xR, int u=1) {
        if (qx > r or qx < l) return;
        if (l != r) {
            int m = l+r >> 1;
            update_x(qx, qy, uval, l, m, u<<1);
            update_x(qx, qy, uval, m+1, r, u<<1|1);
        }
        update_y(qx, qy, uval, l, r, u);
    }
    void init(int xl, int xr, int yl, int yr, vector<vector<DT>> const& v) {
        xL = xl, xR = xr, yL = yl, yR = yr;
        build_x(v);
    }
}
