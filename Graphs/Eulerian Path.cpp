int n = MAXN;
vi adj[MAXN];

bool has_eulerian_path(int num_edges, vi &in, vi &out) {
    if (num_edges == 0)
        return false;

    int start_nodes = 0, end_nodes = 0;

    for (int i = 0; i < n; i++) {
        if (out[i] - in[i] > 1 || in[i] - out[i] > 1)
            return false;
        else if (out[i] - in[i] == 1)
            start_nodes++;
        else if (in[i] - out[i] == 1)
            end_nodes++;
    }

    return (end_nodes == 0 && start_nodes == 0) ||
           (end_nodes == 1 && start_nodes == 1);
}

void dfs_eulerian(int u, vi &out, vi &path) {
    while (out[u]) {
        int v = adj[u][--out[u]];
        dfs_eulerian(v, out, path);
    }
    path.push_back(u);
}

vi get_eulerian_path() {
    vi in(n);
    vi out(n);
    int num_edges = 0;

    for (int u = 0; u < n; u++) {
        for (auto v : adj[u]) {
            in[v]++, out[u]++;
            num_edges++;
        }
    }

    if (!has_eulerian_path(num_edges, in, out))
        return {};

    int start = 0;
    for (int i = 0; i < n; i++) {
        if (out[i] - in[i] == 1) {
            start = i;
            break;
        }
        if (out[i] > 0)
            start = i;
    }

    vi path;
    dfs_eulerian(start, out, path);
    if (path.size() != num_edges + 1)
        return {};
    reverse(path.begin(), path.end());
    return path;
}
