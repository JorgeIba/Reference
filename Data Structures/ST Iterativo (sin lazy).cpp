// 0-indexed
template <typename T, typename S> struct SegmentTreeIt {
  T neutro = T();
  int size;
  vector<T> st;
  SegmentTreeIt(int n, T val = T(), const vector<S> &v = vector<S>()) {
    st.resize(2 * n);
    if (v.empty())
      fill(all(st), val);
    size = n;
    if (!v.empty())
      forn(i, n) st[i + size] = set(v[i]);
    build();
  }
  T merge(T a, T b) { return a + b; }
  void build() {
    for (int i = size - 1; i; i--)
      st[i] = merge(st[i << 1], st[i << 1 | 1]);
  }
  void update(int i, T val) {
    for (st[i += size] = val; i > 1; i >>= 1)
      if (i & 1)
        st[i >> 1] = merge(st[i ^ 1], st[i]);
      else
        st[i >> 1] = merge(st[i], st[i ^ 1]);
  }
  T query(int l, int r) {
    T ansL = neutro;
    T ansR = neutro;
    for (l += size, r += size; l <= r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansL = merge(ansL, st[l++]);
      if (~r & 1)
        ansR = merge(st[r--], ansR);
    }
    return merge(ansL, ansR);
  }
  T set(S x) { return T(x); }
  T &operator[](int i) { return st[i + size]; }
};
