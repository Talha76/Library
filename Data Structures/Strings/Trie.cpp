/*
 * You may need to edit the following lines/functions:
 * - DT: Data type of your choice
 * - get(x, i): Returns value at i^th position of x
 * - next_val(x, i): Checks if next position of i exists in x
 *                   by changing the value of i
 * - update(u): Updates the value of node u after inserting
 *              to it's children
 * - query(x): The way you want to do the query,
 *             you can change the parameters
 * - new_node(v): Creates a new node with value=v;
 *                update other information while creating a new node
 * - init(SZ, START): Call init to initialize trie,
 *                    SZ is the number of children,
 *                    START is the position to start from
 */
namespace Trie {
  using DT = int;
  int SZ, START;
  vector child(0, vector<int>());

  int get(const DT& x, int i) {
    return x >> i & 1;
  }

  bool next_val(const DT& x, int& i) {
    return i--;
  }

  void update(int u) {}

  int query(const DT& x) {}

  int new_node() {
    int new_num = child.size();
    child.emplace_back(SZ);
    return new_num;
  }

  /* Don't touch anything under */
  void init(int _SZ, int _START=0) {
    SZ = _SZ, START = _START;
    new_node();
  }
  void insert(const DT& x, int pos=START, int u=0) {
    int nxt = get(x, pos);
    if (not child[u][nxt])
      child[u][nxt] = new_node();
    if (next_val(x, pos)) {
      insert(x, pos, child[u][nxt]);
      update(u);
    }
  }
}
