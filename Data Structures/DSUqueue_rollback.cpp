struct DSUstack {
  struct update {
    int *u, val;
    update(int *u, int val) : u(u), val(val) {}
    void apply() { *u = val; }
  };
  vector<int> pa, sz;
  vector<update> st;
  DSUstack(int n) : pa(n), sz(n, 1) { iota(all(pa), 0); }
  int find(int u) { return (pa[u] == u) ? u : find(pa[u]); }
  void join(int u, int v) {
    u = find(u), v = find(v);
    if (sz[u] < sz[v])
      swap(u, v);
    st.push_back(update(&sz[u], sz[u]));
    st.push_back(update(&pa[v], v));
    if (u == v)
      return;
    sz[u] += sz[v];
    pa[v] = u;
  }
  int getSize(int u) { return sz[find(u)]; }
  void undo() { // Change this and update according to the problem
    assert(st.size());
    st.back().apply();
    st.pop_back();
    st.back().apply();
    st.pop_back();
  }
};

// Amortized complexity of O(q log N * f(u))
// where f(u) is the complexity in an update
struct DSUqueue {
  struct qupdate {
    char type;
    int u, v;
    qupdate(int u, int v, char type) : u(u), v(v), type(type) {}
  };
  DSUstack dsu;
  vector<qupdate> S;
  int onlB; // <= this index all elements are 'B'
  DSUqueue(int n) : dsu(n), onlB(0) {}

  void join(int u, int v, char type = 'B') {
    S.pb(qupdate(u, v, type));
    dsu.join(u, v);
  }
  inline void advance() {
    while (onlB < S.size() && S[onlB].type == 'B')
      onlB++;
  }

  void fix() {
    if (!S.size() || S.back().type == 'A')
      return;
    vector<qupdate> A, B;
    do {
      if (S.back().type == 'A')
        A.push_back(S.back());
      else
        B.push_back(S.back());
      S.pop_back(), dsu.undo();
    } while (S.size() > onlB && A.size() != B.size());
    reverse(all(B));
    reverse(all(A));
    for (const auto &x : B)
      join(x.u, x.v, x.type);
    for (const auto &x : A)
      join(x.u, x.v, x.type);
    advance();
  }

  void reverseQueries() {
    forn(i, S.size()) dsu.undo();
    reverse(all(S));
    forn(i, SZ(S)) {
      S[i].type = 'A';
      dsu.join(S[i].u, S[i].v);
    }
    onlB = 0;
  }
  void undo() {
    advance();
    if (onlB == S.size())
      reverseQueries();
    fix();
    dsu.undo();
    S.pop_back();
  }

  int getSize(int u) { return dsu.getSize(u); }
};
