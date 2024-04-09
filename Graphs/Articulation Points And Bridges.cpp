typedef pair<int, int> Edge;
int Time;
vector<vector<int>> adj;
vector<int> disc, low, isAp;
vector<Edge> br;
// to get biconnected components
vector<vector<int>> bcc;
stack<int> S;

void init(int N) { adj.assign(N, vector<int>()); }
void addEdge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}
int dfsAPB(int u, int p) {
  int ch = 0, nup = 0;
  low[u] = disc[u] = ++Time;

  // -> to get biconnected components
  S.push(u);
  // <-

  for (int &v : adj[u]) {
    if (v == p && !nup++)
      continue;
    if (!disc[v]) {
      ch++, dfsAPB(v, u);
      if (disc[u] <= low[v]) {
        isAp[u]++;

        // -> to get biconnected components
        bcc.push_back({});
        bcc.back().push_back(u);
        while (true) {
          int x = S.top();
          S.pop();
          bcc.back().pb(x);
          if (x == v)
            break;
        }
        // <-
      }
      if (disc[u] < low[v])
        br.push_back({u, v});
      low[u] = min(low[u], low[v]);
    } else
      low[u] = min(low[u], disc[v]);
  }
  return ch;
}
void APB() {
  bcc.clear();
  br.clear();
  while (!S.empty())
    S.pop();
  isAp = low = disc = vector<int>(adj.size());
  Time = 0;
  for (int u = 0; u < adj.size(); u++)
    if (!disc[u])
      isAp[u] = dfsAPB(u, u) > 1;
}
