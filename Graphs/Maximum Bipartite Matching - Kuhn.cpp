// Maximum Bipartite Matching O(nm)
struct KuhnAlgo {
    int n, m;
    vector<int> left_to_right, right_to_left;
    vector<bool> visited;
    vector<vector<int>> adjListLeft;

    // Left: 0, 1, ..., n
    // Right: 0, 1, ..., m
    KuhnAlgo(int n, int m, const vector<vector<int>> &adjListLeft): n(n), m(m), adjListLeft(adjListLeft) {
        left_to_right.assign(n, -1);
        right_to_left.assign(m, -1);
        visited.assign(n, false);
    }
    
    bool try_Kuhn(int u) {
        if(visited[u]) return false;
        visited[u] = true;

        for(auto v: adjListLeft[u]) {
            if(right_to_left[v] == -1 || try_Kuhn(right_to_left[v])) {
                left_to_right[u] = v;
                right_to_left[v] = u;
                return true;
            }
        }
        return false;
    }
    
    vector<pair<int,int>> getMaxMatching() {
        int sizeMatching = 0;
        for(int u = 0; u < n; u++) {
            fill(all(visited), false);
            if( try_Kuhn(u) )
                sizeMatching++;                
        }
        vector< pair<int,int> > ans;
        for(int u = 0; u < n; u++)
            if(left_to_right[u] != -1)
                ans.push_back({u, left_to_right[u]});
        return ans;
    }
};
