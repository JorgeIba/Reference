/*-----Centroid Descomposition-----*/
int stsz[MAXN]        // substree's size
    int parent[MAXN]; // parent of the node int the centroid's tree
bool vis[MAXN];

// precomputes the subtrees's size
void dfs(int u, int p) {
  stsz[u] = 1;
  for (auto v : adj[u]) {
    if (v == p)
      continue;
    dfs(v, u);
    stsz[u] += stsz[v];
  }
}

// builds the centroid's tree
int centrDesc(int root) {
  int sz = 1;
  for (auto v : adj[root])
    if (!vis[v])
      sz += stsz[v];
  while (true) {
    int cent = -1;
    for (auto v : adj[root]) {
      if (!vis[v] && 2 * stsz[v] > sz)
        cent = v;
    }
    if (cent == -1)
      break;
    stsz[root] = sz - stsz[cent];
    root = cent;
  }
  vis[root] = true;
  for (auto v : adj[root])
    if (!vis[v])
      parent[centrDesc(v)] = root;
  return root;
}

// returns the root of the tree of centroids
int build(int root) {
  dfs(root, -1);
  return centrDesc(root);
}
