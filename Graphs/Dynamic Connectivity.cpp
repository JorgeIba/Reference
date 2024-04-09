
struct DSURollback {
  // u is the root in join(u, v)
  struct DataChanges {
    bool checkpoint;
    int u, size_u;
    int v, dad_v;
    DataChanges() : checkpoint(true) {}
    DataChanges(int u, int size_u, int v, int dad_v)
        : u(u), size_u(size_u), v(v), dad_v(dad_v) {}
  };

  int N;
  vector<int> dad, size;
  stack<DataChanges> changes;
  int components;

  DSURollback(int n) : N(n), dad(n), size(n, 1), components(n) {
    while (n--)
      dad[n] = n;
    changes.push(DataChanges());
  }

  int root(int u) {
    if (dad[u] == u)
      return u;
    return root(dad[u]);
  }

  void checkpoint() { changes.push(DataChanges()); }

  void rollback() {
    while (!changes.empty() && !changes.top().checkpoint) {
      DataChanges D = changes.top();
      changes.pop();
      int u = D.u, size_u = D.size_u;
      int v = D.v, dad_v = D.dad_v;
      size[u] = size_u;
      dad[v] = dad_v;
      components++;
    }
    if (SZ(changes) != 1 && changes.top().checkpoint)
      changes.pop();
  }

  bool join(int u, int v) {
    u = root(u), v = root(v);

    if (u == v)
      return false;

    if (size[u] < size[v])
      swap(u, v);

    DataChanges D(u, size[u], v, dad[v]);
    changes.push(D);

    components--;
    dad[v] = u;
    size[u] += size[v];
    return true;
  }
};

#define update_t array<int, 4> // {l, r, u, v}
#define query_t pair<int, int>

// Maybe we should do something to support multi edges
struct DynammicCon {
  map<pair<int, int>, int> edge_to_l;
  vector<query_t> queries;
  vector<update_t> updates;
  DSURollback DSU;

  int curr_time = 0;

  DynammicCon(int n) : DSU(n) {}

  void add(int u, int v) {
    if (u > v)
      swap(u, v);

    edge_to_l[{u, v}] = curr_time;
    queries.push_back({-1, -1});
    curr_time++;
  }

  void query(int u, int v) {
    if (u > v)
      swap(u, v);

    queries.push_back({u, v});
    curr_time++;
  }

  void remove(int u, int v) {
    if (u > v)
      swap(u, v);

    int l = edge_to_l[{u, v}];
    updates.push_back({l, curr_time, u, v});
    edge_to_l.erase({u, v});

    queries.push_back({-1, -1});
    curr_time++;
  }

  void process() {
    for (auto [edge, l] : edge_to_l) {
      updates.push_back({l, curr_time, edge.first, edge.second});
    }

    queries.push_back({-1, -1});
    go(0, curr_time, updates);
  }

  void go(int l, int r, vector<update_t> curr_updates) {
    DSU.checkpoint();

    vector<update_t> updates_down;
    for (auto [ql, qr, u, v] : curr_updates) {
      if (qr < l || r < ql)
        continue;
      else if (ql <= l && r <= qr) {
        DSU.join(u, v);
      } else {
        updates_down.push_back({ql, qr, u, v});
      }
    }

    if (l == r) {
      // Answer Queries
      if (queries[l].first != -1) {
        cout << DSU.components << endl;
      }
    } else {
      int mid = (l + r) / 2;
      go(l, mid, updates_down);
      go(mid + 1, r, updates_down);
    }

    DSU.rollback();
  }
};