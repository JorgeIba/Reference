
//* n has to be exactly the size of the tree
// return at most 2 centroids of a tree
template <typename T>
vector<T> getCentroids(const vector<vector<T>> &adjList, int n) {
  vector<T> centroids;
  vector<int> sz(n + 1); //! 1-indexed
  auto dfs = [&](const auto &self, auto u, auto p) -> void {
    sz[u] = 1;
    bool is_centroid = true;
    for (auto v : adjList[u]) {
      if (v == p)
        continue;

      self(self, v, u);
      sz[u] += sz[v];
      if (sz[v] > n / 2)
        is_centroid = false;
    }
    if (n - sz[u] > n / 2)
      is_centroid = false;
    if (is_centroid)
      centroids.push_back(u);
  };
  dfs(dfs, 1, -1); //! 1-indexed
  return centroids;
}