// Tarjan's algorithm
vector< vector<int> > SCC(int n) {
    vector< vector<int> > comps;
    stack<int> st;

    vector<int> disc(n, -1), low(n), popped(n);
    int Time = 1;

    auto dfs = [&](const auto &dfs, int u) -> void {
        disc[u] = low[u] = Time++;
        st.push(u);

        for(auto v: adjList[u]) {
            if(disc[v] == -1) { // Down edge
                dfs(dfs, v);

                low[u] = min(low[u], low[v]);
            } else if(disc[v] < disc[u] && !popped[v]) { // Back edge
                low[u] = min(low[u], disc[v]);
            }
        }

        // Boss of component
        if(disc[u] == low[u]) {
            vector<int> comp;

            while(st.top() != u) { // Pop nodes in same component
                comp.push_back(st.top()); 
                popped[st.top()] = 1;
                st.pop();
            }

            comp.push_back(u);
            popped[u] = 1;
            st.pop();

            comps.push_back(comp);
        }
    };

    forn(i, n) {
        if(disc[i] == -1)
            dfs(dfs, i);
    }

    return comps;
}