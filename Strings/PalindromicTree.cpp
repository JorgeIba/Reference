
// O(n) amortizado
struct PalindromicTree {
	const static int SIG = 10; // Adjust here

	vector<vector<int>> t;
	vector<int> s, len, link, qt;
	int n, last, sz;

	PalindromicTree(int N): t(N+2, vector<int>(SIG)) {
		s = len = link = qt = vector<int>(N+2);
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
