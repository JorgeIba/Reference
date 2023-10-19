template <typename T> struct SparseTable {
    int N, maxLevel;
    vector<vector<T>> table;

    SparseTable(vector<T> &init) {
        N = init.size();
        maxLevel = log2(N) + 1;
        table.assign(maxLevel + 1, vector<T>(N));

        for (int i = 0; i < N; i++)
            table[0][i] = init[i];
        for (int lvl = 1; lvl <= maxLevel; lvl++) {
            for (int i = 0; i < N; i++) {
                int idx_half = i + (1 << (lvl - 1));
                if (idx_half >= N)
                    continue;
                table[lvl][i] =
                    operation(table[lvl - 1][i], table[lvl - 1][idx_half]);
            }
        }
    }

    // 0-indexed
    T query(lli l, lli r) {
        lli idx = l, sizee = r - l + 1, pot = 0;
        T ans = neutro();

        while (sizee) {
            if (sizee & 1) {
                ans = operation(ans, table[pot][idx]);
                idx += (1 << pot);
            }
            pot++;
            sizee >>= 1;
        }

        return ans;
    }

    T operation(T a, T b) { return a + b; }
    T neutro() { return 0; }
};