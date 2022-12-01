/*
 * preffix array at position i gives us the length of the largest propper
 * preffix which is also a suffix in substring patt[0,...,i]
 */
vector <int> preffix_function(string& patt){
	int length = patt.size();
	vector <int> lps (length, 0);
	int j = 0;
	for(int i = 1; i < length; i++) {
		j = lps[i-1];
		while(j > 0 && patt[i] != patt[j]) j = lps[j-1];
		lps[i] = j + (patt[i] == patt[j]);
	}
	return lps;
}
// Returns an array of all the indexes of text where pattern can be found
vector<int> kmp(string text, string pattern){
	vector<int> indexes;
	int i = 0;
	int j = 0;
	vector<int> lps = preffix_function(pattern);
	for(int i = 0; i < text.size(); i++) {
		while(j > 0 && pattern[j] != text[i]) j = lps[j - 1];
		if(text[i] == pattern[j]) {
			j++;
			if(j == pattern.size()) {
				indexes.push_back(i - j + 1);
				j = lps[j-1];
			}
		}
	}
	return indexes;
}
/*
 * Returns an array of size |s| + 1, the i-th position of this array conains
 * the number of occurrences of preffix s[1,...,i] (1-based). Position 0
 * doesn't contain relevant information.
 */
vector<int> number_of_occ_preff(string s) {
	vector<int> pi = preffix_function(s);
	int len = s.size();
	vector<int> ans(len + 1);
	for(int i = 0; i < len; i++)
		ans[pi[i]]++;
	for(int i = len - 1; i > 0; i--)
		ans[pi[i-1]] += ans[i];
	for(int i = 0; i <= len; i++)
		ans[i]++;
	return ans;
}
