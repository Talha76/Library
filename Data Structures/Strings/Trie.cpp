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
 * - update(u, x, i, leaf): Updates the value of node u according to insertion x
 *                          of position i; call leaf=true if u is a leaf node
 * - query(x): <YOUR_WISH> = The way you want to do the query, you can change the parameters
 * - init(SZ, START): Call init to initialize trie,
 *                    SZ is the number of children,
 *                    START is the position to start from
 */
namespace Trie {
    using DT = int;
    int SZ, START;
    vector child(0, vector<int>());
    vector<int> sz;
    
    inline int get(const DT& x, int i) { return x >> i & 1; }
    inline bool next_val(const DT& x, int i) { return ~i; }
    inline int next_pos(int i) { return i-1; }
    
    int new_node() {
        int new_num = child.size();
        child.emplace_back(SZ);
        sz.push_back(0);
        return new_num;
    }
    
    void update(int u, const DT& x, int i, bool leaf=false) { sz[u]++; }
    
    int query(const DT& x) {}
    
    /* Don't touch anything below */
    void init(int _SZ, int _START=0) {
        SZ = _SZ, START = _START;
        new_node();
    }
    void insert(const DT x) {
        int u = 0, i;
        for (i = START; next_val(x, i); i = next_pos(i)) {
            update(u, x, i);
            int nxt_v = get(x, i);
            if (not child[u][nxt_v])child[u][nxt_v] = new_node();
            u = child[u][nxt_v];
        }
        update(u, x, i, true);
    }
}
