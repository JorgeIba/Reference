

struct LCA_T{
    const static int maxLOG = 18;
    int n;
    vector<int> depth, order;    

    vector< vector<int> > ancestors;
    // uncomment if you wanna get minimum between paths
    // vector< vector<int> > min_ancestors; 

    template<class G>
    LCA_T(int n, const G &adjList, int root = 1): n(n), depth(n) {
        ancestors.assign(n, vector<int>(maxLOG));
        for(int i = 0; i < n; i++) ancestors[i][0] = i;

        // min_ancestors.assign(n, vector<int>(maxLOG));

        dfs(root, adjList);
        prec();
    }


    template<class G>
    void dfs(int u, const G &adjList, int p = -1) {
    
        order.push_back(u);
        for(auto v: adjList[u]){
            if(v == p) continue;

            ancestors[v][0] = u;
            depth[v] = depth[u] + 1;
            // Add here if queries of min, sum, etc.

            dfs(v, adjList, u);
        }
    }

    void prec() {
        for(auto u: order) 
            for(int i = 1; i < maxLOG; i++) 
                ancestors[u][i] = ancestors[ ancestors[u][i-1] ][i-1];
                // Add here if queries of min, sum, etc
        order.clear();
    }

    int get_kth_parent(int u, int k){
        for(int i = maxLOG - 1; i >= 0; i--) 
            if(k & (1 << i))
                u = ancestors[u][i];

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
};

