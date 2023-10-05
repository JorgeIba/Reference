struct state {
    int len, link;
    map<int, int> child;
    state(int len = 0, int link = -1) : len(len), link(link) {}
    state(int len, int link, map<int, int> child)
        : len(len), link(link), child(child) {}
};

struct SuffixAutomaton {
    vector<state> st;
    int last = 0;

    // It's used to store info about the automaton, for example, the number of
    // paths that pass through a node, which can be used to get the number of
    // different strings
    vector<vector<lli>> dp;

    SuffixAutomaton() { st.emplace_back(); }

    void extend(char c) {
        int curr = (int)st.size(), p;
        st.emplace_back(st[last].len + 1);
        for (p = last; p != -1 && !st[p].child.count(c); p = st[p].link)
            st[p].child[c] = curr;

        if (p == -1)
            st[curr].link = 0;
        else {
            int q = st[p].child[c];
            if (st[p].len + 1 == st[q].len)
                st[curr].link = q;
            else {
                int w = (int)st.size();
                st.emplace_back(st[p].len + 1, st[q].link, st[q].child);
                for (; p != -1 && st[p].child[c] == q; p = st[p].link)
                    st[p].child[c] = w;
                st[q].link = st[curr].link = w;
            }
        }
        last = curr;
    }
    void dfs(int u, vector<lli> &curr, int idx) {
        assert(u < dp[idx].size());
        if (dp[idx][u] != -1)
            return;
        dp[idx][u] = curr[u];
        for (auto [c, v] : st[u].child) {
            dfs(v, curr, idx);
            dp[idx][u] += dp[idx][v];
        }
    }
    void prec() {
        dp.resize(2);
        dp[0].resize(st.size() + 10, -1);
        dp[1].resize(st.size() + 10, -1);
        vector<lli> is_ac(st.size() + 10);
        for (int p = last; p != -1; p = st[p].link)
            is_ac[p] = 1;
        // How many accepted node can reach?
        dfs(0, is_ac, 0);
        // Number of strings that node u can reach
        dfs(0, dp[0], 1);
    }
    void get_kth_string_with_rep(int u, lli &k, string &t) {
        if (u)
            k -= dp[0][u];
        if (k <= 0) {
            return;
        }
        for (auto [c, v] : st[u].child) {
            if (dp[1][v] >= k) {
                t += (char)c;
                get_kth_string_with_rep(v, k, t);
                return;
            }
            k -= dp[1][v];
        }
        assert(false);
    }
};
