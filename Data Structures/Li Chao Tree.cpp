// Works for min
// Don't create node_t(), let the functions handle it
// If you want maximums I think only negate functions and ask
// for the minimum, then negate the answer
// L = l, R = r (dominio of the function aka. the min and max value you will
// pass it) This madre is persistent
typedef long long num_t;
const num_t oo = (num_t)2e18;
struct func_t {
  num_t a, b;
  func_t(num_t a = 0, num_t b = oo) : a(a), b(b) {}
  num_t query(num_t x) { return a * x + b; }
};
struct node_t {
  node_t *l, *r;
  func_t f;
  node_t(node_t *l = 0, node_t *r = 0, func_t f = func_t())
      : l(l), r(r), f(f) {}
  num_t query(num_t x) { return f.query(x); }
};
node_t *upd(node_t *p, int l, int r, int L, int R, func_t f) {
  if (l > R || r < L)
    return p;
  int M = L + ((R - L) >> 1);
  node_t *res = p ? new node_t(p->l, p->r, p->f) : new node_t();
  if (l <= L && r >= R) {
    int fl = f.query(L) >= (p ? p->query(L) : oo);
    int fr = f.query(R) >= (p ? p->query(R) : oo);
    if (fl && fr)
      return res;
    if (!fl && !fr) {
      res->f = f;
      return res;
    }
    int fm1 = f.query(M) >= (p ? p->query(M) : oo);
    if (fl && fm1) {
      res->r = upd(res->r, l, r, M + 1, R, f);
      return res;
    }
    if (!fl && !fm1) {
      res->r = upd(res->r, l, r, M + 1, R, res->f);
      res->f = f;
      return res;
    }
    int fm2 = f.query(M + 1) >= (p ? p->query(M + 1) : oo);
    if (fm2 && fr) {
      res->l = upd(res->l, l, r, L, M, f);
      return res;
    }
    if (!fm2 && !fr) {
      res->l = upd(res->l, l, r, L, M, res->f);
      res->f = f;
      return res;
    }
    assert(0);
  }
  res->l = upd(res->l, l, r, L, M, f);
  res->r = upd(res->r, l, r, M + 1, R, f);
  return res;
}
node_t *upd(node_t *p, int l, int r, int L, int R, num_t a, num_t b) {
  return upd(p, l, r, L, R, func_t(a, b));
}
num_t query(node_t *p, int i, int L, int R) {
  if (!p)
    return oo;
  if (i < L || i > R)
    return oo;
  num_t res = p->query(i);
  if (L < R) {
    res = min(res, query(p->l, i, L, (L + R) >> 1));
    res = min(res, query(p->r, i, ((L + R) >> 1) + 1, R));
  }
  return res;
}

// LI CHAO ROLLBACK
// Rollback delete everything you added until hit a LCH.checkpoint()
// Works for minimum
const lli INF = 1e15;
const int MIN_DOM = -1e9;
const int MAX_DOM = 1e9;

template <lli MI = MIN_DOM, lli MA = MAX_DOM> struct LiChaoTree {
  struct line {
    lli a, b;
    array<int, 2> ch;
    line(lli a_ = 0, lli b_ = INF) : a(a_), b(b_), ch({-1, -1}) {}
    lli operator()(lli x) { return a * x + b; }
  };
  vector<line> ln;
  int sz = 0;
  stack<stack<pair<line &, line>>> st;

  void save(line &x) { st.top().emplace(x, x); }

  void checkpoint() { st.emplace(); }

  void rollback() {
    while (st.top().size()) {
      auto [end, val] = st.top().top();
      st.top().pop();
      end = val;
    }
    st.pop();
  }

  int ch(int p, int d) {
    if (ln[p].ch[d] == -1) {
      ln[p].ch[d] = sz++;
      // ln.emplace_back();
    }
    return ln[p].ch[d];
  }
  LiChaoTree(int n) {
    ln.resize(4 * n);
    st.emplace();
  }

  void add(line s, lli l = MI, lli r = MA, int p = 0) {
    lli m = (l + r) / 2;
    bool L = s(l) < ln[p](l);
    bool M = s(m) < ln[p](m);
    bool R = s(r) < ln[p](r);
    save(ln[p]);
    if (M)
      swap(ln[p], s), swap(ln[p].ch, s.ch);
    if (s.b == INF)
      return;
    if (L != M)
      add(s, l, m - 1, ch(p, 0));
    else if (R != M)
      add(s, m + 1, r, ch(p, 1));
  }
  lli query(int x, lli l = MI, lli r = MA, int p = 0) {
    lli m = (l + r) / 2, ret = ln[p](x);
    if (ret == INF)
      return ret;
    if (x < m)
      return min(ret, query(x, l, m - 1, ch(p, 0)));
    return min(ret, query(x, m + 1, r, ch(p, 1)));
  }
};