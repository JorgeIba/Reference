/*
 * preffix array at position i gives us the length of the largest propper
 * preffix which is also a suffix in substring patt[0,...,i]
 */
vector <int> preffix_array(string& patt){
	int length = patt.size();
	vector <int> lps (length, 0);
	int j = 0;
	for(int i = 1; i < length; i++) {
		j = lps[i-1];
		while(j > 0 && patt[i] != patt[j]) j = lps[j-1];
		lps[i] = j + patt[i] == patt[j];
	}
	return lps;
}
// Returns an array of all the indexes of text where pattern can be found
vector<int> kmp(string text, string pattern){
	vector<int> indexes;
	int i = 0;
	int j = 0;
	vector<int> lps = preffix_array(pattern);
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
