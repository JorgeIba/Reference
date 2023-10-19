// It supports values in vertices or in edges
// Call first dfs and then build
// dfs(adjList, root)
// build(adjList, root, root)
// DataStructure is initialized with HLD->indexDS:
// values[ HLD->indexDS[i] - 1 ] = nums[i-1]; if DS is 1 indexed
// Each query in O(log n * C) where C is the time DS process queries
// For custom queries/updates, call traversePath with custom lambda
// 1-Indexed
template <typename T = int> struct HeavyLight {
    vector<int> depth, parent, subtree, chainHead, indexDS;
    bool valuesInEdges = false;
    int cnt = 1;

    HeavyLight(int n, bool valuesInEdges = false)
        : depth(n), parent(n), subtree(n), chainHead(n), indexDS(n),
          valuesInEdges(valuesInEdges) {}

    template <class G> void dfs(const G &adjList, int u, int p = -1) {
        subtree[u] = 1;
        for (auto v : adjList[u]) {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs(adjList, v, u);

            subtree[u] += subtree[v];
        }
    }

    template <class G>
    void buildHLD(const G &adjList, int u, int head, int p = -1) {
        chainHead[u] = head;
        indexDS[u] = cnt++;

        int heavy = -1, sz_heavy = 0;
        for (auto v : adjList[u]) {
            if (v == p)
                continue;
            if (sz_heavy < subtree[v])
                heavy = v, sz_heavy = subtree[v];
        }

        if (heavy != -1)
            buildHLD(adjList, heavy, head, u);

        for (auto v : adjList[u]) {
            if (v == p || v == heavy)
                continue;
            buildHLD(adjList, v, v, u);
        }
    }

    template <class BinaryOperation>
    void traversePath(int u, int v, BinaryOperation op) {
        // if(valuesInEdges && u == v) {
        //     op(indexDS[u], indexDS[u]);
        //     return;
        // }

        for (; chainHead[u] != chainHead[v]; u = parent[chainHead[u]]) {
            if (depth[chainHead[u]] < depth[chainHead[v]])
                swap(u, v);
            op(indexDS[chainHead[u]], indexDS[u]);
        }

        if (depth[u] > depth[v])
            swap(u, v);

        // if(valuesInEdges && u == v) return;
        op(indexDS[u] + valuesInEdges, indexDS[v]);
    }

    template <class DSType> T query(int u, int v, DSType *DS) {
        T ans = T();
        traversePath(
            u, v, [this, &ans, DS](int l, int r) { ans += DS->query(l, r); });
        return ans;
    }

    template <class DSType> void update(int u, int v, T val, DSType *DS) {
        traversePath(u, v,
                     [this, &val, DS](int l, int r) { DS->update(l, r, val); });
    }
};

/*
    If merge is not commutative:
    1.- Change traversePath, query and update for these
    2.- You have to create 2 DataStructures
        2.1.- DS_L is array reversed
        2.2.- DS_R is normal array

    No lo he testeado con valores en las aristas xd
*/
template <class BinaryOperation>
void traversePath(int u, int v, BinaryOperation op) {
    if (valuesInEdges && u == v) {
        op(indexDS[u], indexDS[u], true);
        return;
    }

    bool left = true;
    for (; chainHead[u] != chainHead[v]; u = parent[chainHead[u]]) {
        if (depth[chainHead[u]] < depth[chainHead[v]]) {
            swap(u, v);
            left = !left;
        }
        op(indexDS[chainHead[u]], indexDS[u], left);
    }

    if (depth[u] > depth[v])
        swap(u, v);
    else
        left = !left;

    if (valuesInEdges && u == v)
        return;
    op(indexDS[u] + valuesInEdges, indexDS[v], left);
}

template <class DSType>
T query(int u, int v, int n, DSType *DS_L, DSType *DS_R) {
    T ansL = T();
    T ansR = T();
    traversePath(
        u, v,
        [this, &ansL, &ansR, &n, DS_L, DS_R](int l, int r, bool left = true) {
            if (left)
                ansL = ansL + DS_L->query(n + 1 - r, n + 1 - l);
            else
                ansR = DS_R->query(l, r) + ansR;
        });
    return ansL + ansR;
}

template <class DSType>
void update(int u, int v, int val, int n, DSType *DS_L, DSType *DS_R) {
    traversePath(u, v,
                 [this, &val, n, DS_L, DS_R](int l, int r, bool left = true) {
                     DS_L->update(n + 1 - r, n + 1 - l, val);
                     DS_R->update(l, r, val);
                 });
}