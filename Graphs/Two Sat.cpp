/*
 * n = number of variables
 * u = 2*i, ¬u = 2*i+1 for i = 0,1,...,n
 */
/*----- 2-SAT -----*/
struct two_sat {
  int n, _id = 0, cnt = 0;
  vvi adj;
  vi low, id, SCC;
  vector<bool> in_stack;
  stack<int> s;
  two_sat(int n)
      : n(n), adj(2 * n), low(2 * n, 0), id(2 * n, -1), SCC(2 * n),
        in_stack(2 * n) {}
  int neg(int u) { return u + ((u & 1) ? -1 : 1); }
  void add_edge(int u, int v) { adj[u].pb(v); }
  void add_imp(int u, int v) {
    add_edge(neg(u), v);
    add_edge(neg(v), u);
  }
  void dfs(int u) {
    id[u] = _id++;
    low[u] = id[u];
    in_stack[u] = true;
    s.push(u);
    for (auto v : adj[u]) {
      if (id[v] == -1) {
        dfs(v);
        low[u] = min(low[u], low[v]);
      } else if (in_stack[v])
        low[u] = min(low[u], id[v]);
    }
    if (id[u] == low[u]) {
      int v;
      do {
        v = s.top();
        s.pop();
        in_stack[v] = false;
        SCC[v] = cnt;
      } while (v != u);
      cnt++;
    }
  }
  vector<bool> solve() {
    forn(u, 2 * n) if (id[u] == -1) dfs(u);
    vector<bool> values(n);
    forn(i, n) {
      if (SCC[2 * i] == SCC[2 * i + 1])
        return {};
      else
        values[i] = SCC[2 * i] < SCC[2 * i + 1];
    }
    return values;
  }
};
