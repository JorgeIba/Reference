// 18
vector<array<int, 2>> ranges;
vector<int> order;
int time_r = 1;

void dfs_euler(int u, int p = -1) {
  order.push_back(u);
  ranges[u][0] = time_r++;

  for (auto v : adjList[u]) {
    if (v == p)
      continue;
    dfs_euler(v, u);
  }

  ranges[u][1] = time_r - 1;
}
