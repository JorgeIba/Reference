struct SuffixArray {
    vector<int> suff;       // Suffix array itself
    string t;               // String that the suffix array belongs to
    vector<int> lcp;        // Longest common preffix between i and i+1
    vector<vector<int>> cl; // Classes of strings of size 2^k (can be used
                            // as sparse table). On most cases can be
                            // changed for a vector storing the last
                            // version of the classes.
    int N;                  // size of the string

    void count_sort(vector<int> &p, const vector<int> &c) {
        int n = c.size();
        vector<int> p_new(n), cnt(n + 1);
        for (int x : c)
            cnt[x + 1]++;
        for (int i = 1; i < n; i++)
            cnt[i] += cnt[i - 1];
        for (int x : p)
            p_new[cnt[c[x]]++] = x;
        p.swap(p_new);
    }

    // Complexity: O(n log n)
    SuffixArray(string s) {
        t = s + "#"; // Alphabetically smaller to all characters in the string
        N = t.size();
        suff.assign(N, 0);
        vector<int> c_new(N);
        vector<pair<char, int>> a(N);

        for (int i = 0; i < N; i++)
            a[i] = {t[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < N; i++)
            suff[i] = a[i].second;

        c_new[suff[0]] = 0;
        for (int i = 1; i < N; i++) {
            if (a[i].first == a[i - 1].first)
                c_new[suff[i]] = c_new[suff[i - 1]];
            else
                c_new[suff[i]] = c_new[suff[i - 1]] + 1;
        }
        cl.push_back(c_new);

        int k = 0;
        while ((1 << k) < N) {
            auto &c = cl.back();
            for (int i = 0; i < N; i++)
                suff[i] = (suff[i] - (1 << k) + N) % N;
            count_sort(suff, c);
            c_new[suff[0]] = 0;
            for (int i = 1; i < N; i++) {
                pair<int, int> prev = {c[suff[i - 1]],
                                       c[(suff[i - 1] + (1 << k)) % N]};
                pair<int, int> now = {c[suff[i]], c[(suff[i] + (1 << k)) % N]};
                if (now == prev)
                    c_new[suff[i]] = c_new[suff[i - 1]];
                else
                    c_new[suff[i]] = c_new[suff[i - 1]] + 1;
            }
            cl.push_back(c_new);
            k++;
        }
    }

    void calcLCP() {
        lcp.assign(N, 0);
        int k = 0;
        auto &c = cl.back();
        for (int i = 0; i < N - 1; i++) {
            int pi = c[i];
            int j = suff[(pi - 1 + N) % N];
            while ((i + k) < N && (j + k) < N && t[i + k] == t[j + k])
                k++;
            lcp[pi] = k;
            k = max(k - 1, 0);
        }
    }
    // Compares two substrings of the string of size l starting in i and j
    // respectively. k = floor(log(l)) (it's easier to precompute all values of
    // log(l) . The complexity is O(1)
    // Returns:
    // 		0  -> strings are equal
    // 		1  -> string starting in j is smaller
    // 		-1 -> string starting in i is smaller
    int compare(int i, int j, int l, int k) {
        pair<int, int> a = {cl[k][i], cl[k][(i + l - (1 << k) + N) % N]};
        pair<int, int> b = {cl[k][j], cl[k][(j + l - (1 << k) + N) % N]};
        return a == b ? 0 : a < b ? -1 : 1;
    }

    void print() {
        int n = t.size();
        for (int x : suff)
            cout << t.substr(x, n - x) << '\n';
    }

    lli number_diff_strings() {
        calcLCP();
        lli n = t.size() - 1;
        lli ans = (n * n + n) / 2;
        for (int i = 0; i <= n; i++)
            ans -= lcp[i];
        return ans;
    }
};
