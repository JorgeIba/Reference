const int maxN = 3e5 + 100;
const int maxLOG = 20;

typedef pair<int,int> pairr;

vector< vector<pairr> > adjList;
vector<int> depth, order;
int ancestors[maxN][maxLOG];
int min_bet_ancestors[maxN][maxLOG];


void dfs_prec(int u, int w_parent, int depth_u=0, int p = -1) {
    ancestors[u][0] = p;
    min_bet_ancestors[u][0] = w_parent;

    depth[u] = depth_u;
    order.push_back(u);

    for(auto [v, w]: adjList[u]){
        if(v == p) continue;
        dfs_prec(v, w, depth_u+1, u);
    }
}

void prec() {
    for(auto u: order) {
        for(int i = 1; i < maxLOG && (1<<i) <= depth[u]; i++) {
            ancestors[u][i] = ancestors[ ancestors[u][i-1] ][i-1];
            min_bet_ancestors[u][i] = min( min_bet_ancestors[u][i-1], min_bet_ancestors[ ancestors[u][i-1]  ][i-1]  );
        }
    }
}

int get_kth_parent(int u, int k){
    for(int i = maxLOG - 1; i >= 0; i--) {
        if(k & (1 << i)) {
            u = ancestors[u][i];
        }
    }
    return u;
}

int get_lca(int u, int v) {
    if(depth[u] > depth[v]) swap(u, v);
    v = get_kth_parent(v, depth[v] - depth[u]);

    for(int i = maxLOG-1; i >= 0; i--) {
        if(ancestors[u][i] != ancestors[v][i]) {
            u = ancestors[u][i];
            v = ancestors[v][i];
        }
    }
    return u != v ? ancestors[u][0] : u;
}

// v is ancestor of u
int get_minimum(int u, int v){
    int k = depth[u] - depth[v];
    int mn = 1e9;
    for(int i = maxLOG - 1; i >= 0; i--) {
        if(k & (1 << i)) {
            mn = min(mn, min_bet_ancestors[u][i]);
            u = ancestors[u][i];
        }
    }
    return mn;
}

