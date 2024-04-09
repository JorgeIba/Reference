/*
Calculate f(u) * g(v) * dist(u, v)
For each u and v
Needs adjList, Poly (possibly fft)

How to use it?
TreeConvolution TC(n);
TC.getAns(f, g, h);

where f, g and h are functions or lambdas
*/
struct TreeConvolution {
  int n;

  vector<bool> visited;
  vector<int> sizeSub, heightSub, ansArray;

  TreeConvolution(int n)
      : n(n), visited(n), sizeSub(n), heightSub(n), ansArray(2 * n) {}

  inline int getCentroids(int root, int n) {
    int centroid = -1;

    auto dfs_ = [&](const auto &dfs_, auto u, auto p) -> void {
      sizeSub[u] = 1;
      bool is_centroid = true;
      for (auto v : adjList[u]) {
        if (v == p || visited[v])
          continue;

        dfs_(dfs_, v, u);
        sizeSub[u] += sizeSub[v];
        if (sizeSub[v] > n / 2)
          is_centroid = false;
      }
      if (n - sizeSub[u] > n / 2)
        is_centroid = false;
      if (is_centroid)
        centroid = u;
    };
    dfs_(dfs_, root, -1);
    return centroid;
  }

  template <class lambda>
  void dfs_ans(int root_centroid, int n_sz, lambda const &dfs_in) {
    Poly A_all(n_sz + 1), B_all(n_sz + 1);
    visited[root_centroid] = 1;

    dfs_in(dfs_in, root_centroid, 0, A_all, B_all);

    // Sum of all
    Poly almost = A_all * B_all;
    for (int i = 0; i < SZ(almost); i++) {
      ansArray[i] = (ansArray[i] + almost[i]);
      if (ansArray[i] >= MOD)
        ansArray[i] -= MOD;
    }

    for (auto v : adjList[root_centroid]) {
      if (visited[v])
        continue;

      Poly A_sub(heightSub[v] + 1), B_sub(heightSub[v] + 1);

      dfs_in(dfs_in, v, 1, A_sub, B_sub);

      // Substraction of subtree paths
      Poly sub = A_sub * B_sub;
      for (int i = 0; i < SZ(sub); i++) {
        ansArray[i] = (ansArray[i] - sub[i]);
        if (ansArray[i] < 0)
          ansArray[i] += MOD;
      }
    }

    for (auto v : adjList[root_centroid]) {
      if (visited[v])
        continue;

      auto centroid_v = getCentroids(v, sizeSub[v]);
      dfs_ans(centroid_v, sizeSub[v], dfs_in);
    }
  }

  template <class F, class G, class H> lli getAns(F f, G g, H h) {

    auto dfs = [&](const auto &dfs, int u, int dist, Poly &A, Poly &B,
                   int p = -1) -> void {
      A[dist] += f(u);
      if (A[dist] >= MOD)
        A[dist] -= MOD;

      B[dist] += g(u);
      if (B[dist] >= MOD)
        B[dist] -= MOD;

      sizeSub[u] = 1;
      heightSub[u] = 1;
      for (auto v : adjList[u]) {
        if (v == p || visited[v])
          continue;
        dfs(dfs, v, dist + 1, A, B, u);
        sizeSub[u] += sizeSub[v];
        heightSub[u] = max(heightSub[u], heightSub[v] + 1);
      }
    };

    auto centroid = getCentroids(0, n);
    dfs_ans(centroid, n, dfs);

    int ansT = 0;
    for (int i = 0; i < SZ(ansArray); i++) {
      ansT += 1LL * ansArray[i] * h(i) % MOD;
      if (ansT >= MOD)
        ansT -= MOD;
    }

    return ansT;
  }
};