/*
 * You may need to edit the following lines/functions:
 * - DT: Data type of your choice
 * - get(x, i): int = Returns value at i^th position of x
 * - next_val(x, i): bool = Checks if next position of i exists in x
 *                          by changing the value of i
 * - next_pos(i): int = Returns next traversal position of i
 * - new_node(v): int = Creates a new node with value=v;
 *                      update other information while creating a new node;
 *                      returns new node number
 * - copy(u, v): int = Copies node v to u and returns u
 * - update(u, x): Updates the value of node u after inserting
 *                 to it's children, according to value v and position i
 * - update_leaf(u): Update node u as a leaf
 * - query(x): <YOUR_WISH> = The way you want to do the query,
 *             you can change the parameters
 * - init(SZ, START): Call init to initialize trie,
 *                    SZ is the number of children,
 *                    START is the position to start from
 */
namespace Trie {
    using DT = int;
    int SZ, START;
    vector child(0, vector<int>());
    vector<int> sz, roots;
    
    inline int get(const DT& x, int i) { return x >> i & 1; }
    inline bool next_val(const DT& x, int i) { return ~i; }
    inline int next_pos(int i) { return i-1; }
    
    int new_node() {
        int new_num = child.size();
        child.emplace_back(SZ);
        sz.push_back(0);
        return new_num;
    }
    int copy(int u, int v) {
        child[u] = child[v];
        sz[u] = sz[v];
        return u;
    }
    
    void update(int u, const DT& x, int i, bool leaf=false) { sz[u]++; }
    
    int query(const DT& x, int l, int r) {
        l = roots[--l], r = roots[r];
        int ret = 0;
        for (int i = START; next_val(x, i); i = next_pos(i)) {
            int bit = get(x, i) ^ 1;
            bit ^= sz[child[r][bit]] - sz[child[l][bit]] == 0;
            ret |= (get(x, i) ^ bit) << i;
            l = child[l][bit], r = child[r][bit];
        }
        return ret;
    }
    
    /* Don't touch anything below */
    void init(int _SZ, int _START=0) {
        SZ = _SZ, START = _START;
        roots.push_back(new_node());
    }
    int insert(const DT x, int pos=START, int u=roots.back()) {
        int new_u = new_node();
        u = copy(new_u, u);
        if (not next_val(x, pos)) update(u, x, pos, true);
        else {
            child[u][get(x, pos)] = insert(x, next_pos(pos), child[u][get(x, pos)]);
            update(u, x, pos);
        }
        return u;
    }
}
