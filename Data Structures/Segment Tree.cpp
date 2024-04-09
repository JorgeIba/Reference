
struct Node {

  int l = 0, r = 0;

  lli ls = 0, rs = 0;
  bool flagLazy = false;
  lli lazy_ls = 0, lazy_rs = 0;

  Node() {}
  Node(int l, int r) : l(l), r(r) {}

  // Combine 2 nodes
  Node operator+(const Node &b) {
    Node res(l, b.r);
    // res.ls = (ls + b.ls) % MOD;
    // res.rs = (rs + b.rs) % MOD;

    return res;
  }

  // Update range
  void updateNode(lli sum_l, lli sum_r) {
    // ls = (ls + sum_l) % MOD;
    // rs = (rs + sum_r) % MOD;

    // lazy_ls = (lazy_ls + sum_l) % MOD;
    // lazy_rs = (lazy_rs + sum_r) % MOD;
    // flagLazy = true;
  }

  void resetLazy() {
    flagLazy = false;
    // lazy_ls = 0;
    // lazy_rs = 0;
  }
};

// T Lo que le vas a pasar
template <typename T> struct SegmentTree {
  vector<Node> ST;
  int N;

  SegmentTree(int n, const vector<T> &values) : N(n) {
    ST.resize(4 * N);
    build(1, 1, N, values);
  }

  void init_leaf(int curr, T value, int idx) {
    // ST[curr] = Node(value, 0, idx, idx);
  }

  void build(int curr, int l, int r, const vector<T> &values) {
    ST[curr].l = l, ST[curr].r = r;
    if (l == r) {
      init_leaf(curr, values[l - 1], l);
    } else {
      int mid = l + (r - l) / 2;
      build(2 * curr, l, mid, values);
      build(2 * curr + 1, mid + 1, r, values);
      ST[curr] = updateFromChildren(ST[2 * curr], ST[2 * curr + 1]);
    }
  }

  void pushToChildren(int curr) {
    if (ST[curr].flagLazy) {
      ST[2 * curr].updateNode(ST[curr].lazy);
      ST[2 * curr + 1].updateNode(ST[curr].lazy);
      ST[curr].resetLazy();
    }
  }

  // UPDATE
  void update(int curr, int l, int r, int ql, int qr, int type, T value) {
    if (l > qr || r < ql)
      return;
    else if (ql <= l && r <= qr) {
      ST[curr].updateNode(type, value);
      return;
    }

    pushToChildren(curr);

    int mid = l + (r - l) / 2;
    update(2 * curr, l, mid, ql, qr, type, value);
    update(2 * curr + 1, mid + 1, r, ql, qr, type, value);

    ST[curr] = ST[2 * curr] + ST[2 * curr + 1];
  }
  void update(int ql, int qr, int type, T value) {
    update(1, 1, N, ql, qr, type, value);
  }

  // QUERY
  Node query(int curr, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)
      return Node();
    else if (ql <= l && r <= qr)
      return ST[curr];
    else {
      pushToChildren(curr);
      int mid = l + (r - l) / 2;
      return query(2 * curr, l, mid, ql, qr) +
             query(2 * curr + 1, mid + 1, r, ql, qr);
    }
  }
  Node query(int ql, int qr) { return query(1, 1, N, ql, qr); }
};
