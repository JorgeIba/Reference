struct PalindromicTree {
	const static int SIG = 26; // Adjust here

	vector<vector<int>> t;
	vector<int> s, len, link, qt;
	int n, last, sz;

    vector<int> quickLink;
    vector<int> diff, seriesLink;

	PalindromicTree(int N): t(N+2, vector<int>(SIG)) {
		s = len = link = qt = vector<int>(N+2);
        
        quickLink = diff = seriesLink = vector<int>(N+2);
		n = 1, last = 0, sz = 2;

		s[0] = -1;
		link[0] = 1, len[0] = 0, link[1] = 1, len[1] = -1;
	}

	int getLink(int curr, int symb) {
		while(s[n - len[curr] - 2] != symb)
			curr = link[curr];
		return curr;
	}

	void add(int c) {
		s[n++] = c -= 'a'; // Adjust here
		last = getLink(last, c);
		if(t[last][c]) {
			qt[last = t[last][c]]++;
			return;
		}

		int prev = getLink(link[last], c);

		link[sz] = t[prev][c];
		len[sz] = len[last] + 2;
		t[last][c] = sz++;

		qt[last = t[last][c]]++;
		

        // Extras
        diff[last] = len[last] - len[link[last]];
        if(diff[last] == diff[link[last]]) 
            seriesLink[last] = seriesLink[link[last]];
        else
            seriesLink[last] = link[last];

		// Change getLink
		if(s[n - len[link[last]] - 1] == s[n - len[link[link[last]]] - 1]) 
            quickLink[last] = quickLink[link[last]];
        else
            quickLink[last] = link[link[last]];
	}

	// To get the frequency for each palindrome
	lli propagate() {
		lli total = 0;
		for(int i = sz-1; i > 1; i--) {
			qt[link[i]] += qt[i];
			total += qt[i];
		}
		return total;
	}
};

// What's the minimum number of odd-even (count) palindromes to form s.
const int INF = 1e9;
void k_factorization(const string &s) {
    int n = SZ(s);

    PalindromicTree PT(n);
    vector<int> dp_even(n+1, INF), series_even(n+3, INF), dp_odd(n+1, INF), series_odd(n+3, INF);

    dp_even[0] = 0;
    series_even[0] = 0;

    for(int i = 1; i <= n; i++) {
        PT.add(s[i-1]);

        for(int v = PT.last; v > 0; v = PT.seriesLink[v]) {
            series_even[v] = dp_even[i - PT.len[PT.seriesLink[v]] - PT.diff[v]];
            series_odd[v]  = dp_odd[i - PT.len[PT.seriesLink[v]] - PT.diff[v]];

            if(PT.diff[v] == PT.diff[PT.link[v]]) {
                series_even[v] = min(series_even[v], series_even[PT.link[v]]);
                series_odd[v]  = min(series_odd[v],  series_odd[PT.link[v]]);
            }

            dp_even[i] = min(series_odd[v] + 1, dp_even[i]);
            dp_odd[i]  = min(series_even[v] + 1,  dp_odd[i]);
        }

        cout << dp_odd[i] << " - " << dp_even[i] << endl;
    }
}

// Ways to describe s as even length palindromes
int partitionsEvenLength(const string &s) {
	int n = SZ(s);

	PalindromicTree PT(n);
	vector<int> dp(n + 1), seriesDP(n + 3);

	dp[0] = 1;
	for(int i = 1; i <= n; i++) {
		PT.add(s[i-1]);

		for(int v = PT.last; v > 1; v = PT.seriesLink[v]) {
			seriesDP[v] = dp[i - PT.len[PT.seriesLink[v]] - PT.diff[v]]; // Last element of the serie

			if(PT.diff[v] == PT.diff[PT.link[v]]) {
				seriesDP[v] += seriesDP[PT.link[v]]; // It has 'almost' all the elements of the serie
			}

			dp[i] += seriesDP[v];
		}
		if(i % 2)
			dp[i] = 0;
	}

	return dp[n];
}
