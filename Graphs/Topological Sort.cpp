// 3
// vis = visited
vector<vector<int>> adj;
vector<int> vis, toposorted;
// 4
void init(int N) {
  adj.assign(N, vector<int>());
  vis.assign(N, 0), toposorted.clear();
}

void addEdge(int u, int v) { adj[u].push_back(v); }
// 12
// returns false if there is a cycle
// O(E)
bool toposort(int u) {
  vis[u] = 1;
  for (auto &v : adj[u])
    if (v != u && vis[v] != 2 &&
        (vis[v] || !toposort(v)))
      return false;
  vis[u] = 2;
  toposorted.push_back(u);
  return true;
}
// 6
// O(V + E)
bool toposort() {
  for (int u = 0; u < adj.size(); u++)
    if (!vis[u] && !toposort(u)) return false;
  return true;
}



vector<int> toposort_bfs(vector<vector<int>> &adjList){
    int n = adjList.size();
    vector<int> incoming_edges(n);

    for(int i = 0; i < n; i++)
        for(auto v: adjList[i])
            incoming_edges[v]++;

    queue<int> q;
    for(int i = 0; i < n; i++){
        if(incoming_edges[i] == 0) q.push(i);        
    }

    int cnt = 0;
    vector<int> ans;
    while(!q.empty()){
        int u = q.front(); q.pop();

        ans.push_back(u);
        cnt++;

        for(auto v: adjList[u]){
            incoming_edges[v]--;

            if(incoming_edges[v] == 0){
                q.push(v);
            }
        }
    }

    //HAY UN CICLO
    if(cnt != n) return {-1};

    return ans;
}
