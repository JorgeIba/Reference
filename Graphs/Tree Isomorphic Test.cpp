// Can check if two rooted trees are the same
// For unrooted tree, try with centroids in Centroids.cpp
const lli pLeft = 1e6+3, pRight = 1e7+19, p3 = 1e8+7, MOD = 1e9+7;
vector<lli> levelRepresentation(const vector<vector<lli>> &adjList, int root) {
    vector<lli> hashes(SZ(adjList));

    auto dfs = [&](const auto &self, auto u, auto p) -> void {
        lli hash_u = 1;
        for(auto v: adjList[u]) {
            if(v == p) continue;
            
            self(self, v, u);
            hash_u = hash_u * (p3 - hashes[v] + MOD) % MOD; // hash = (x-A_0)(x-A_1)(x-A_2)...
        }
        hashes[u] = pLeft * hash_u % MOD * pRight % MOD; // Brackets
    };

    dfs(dfs, root, -1);
    return hashes;
}