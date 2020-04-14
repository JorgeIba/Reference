vector <int> KMP(string& pat){
	int length = pat.size();
	vector <int> lps (length, 0);
	lps[0] = 0;
	int i = 0;
	int j = 1;
	while(j < length){
		if(pat[i] != pat[j]){
			if(i != 0)
				i = lps[i-1];
			else{
				lps[j] = 0;
				j++;
			}

		}
		else{
			lps[j] = i + 1;
			i++;
			j++;
		}
	}
	return lps;
}
vector<int> substringSearch(string text, string pattern){
	vector<int> indexes;
	int i = 0;
	int j = 0;
	vector<int> lps = KMP(pattern);
	while(i < text.size()){
		if(text[i] == pattern[j]){
			i++;
			j++;
		}
		if(j == pattern.size()){
			indexes.push_back(i-j+1);
			j = lps[j-1];
		}
		else if(i < text.size() && pattern[j] != text[i]){
		       if(j != 0)
			       j = lps[j-1];
		       else i++;
		}
	}
	// A vector with the indexes where the pattern matches
	return indexes;
}
