// Constructs Suffix Array on O(n)
// Suff : stores indexes of the alphabetically ordered sufixes
// lcp : longest common prefix betwen suffix i, i+1
vector<int> suff;
string t;
vector<int> lcp;
void count_sort(vector<int>& p, const vi& c){
	int n = c.size();
	vector<int> p_new(n), cnt(n+1);
	for(int x : c) cnt[x+1]++;
	for(int i = 1; i < n; i++) cnt[i] += cnt[i-1];
	for(int x : p) p_new[cnt[c[x]]++] = x;
	p.swap(p_new);
}
void suffixArray(string t){
	t += "$"; //Alphabetically less that all characters
	int n = t.size();
	suff.assign(n,0);
	vector<int> c(n);
	vector<pair<char,int>> a(n);
	for(int i = 0; i < n; i++) a[i] = {t[i], i};
	sort(a.begin(), a.end());
	for(int i = 0; i < n; i++) p[i] = a[i].se;
	c[p[0]] = 0;
	for(int i = 1; i < n; i++){
		if(a[i].fi == a[i-1].fi) c[suff[i]] = c[suff[i-1]];
		else c[suff[i]] = c[suff[i-1]]+1;
	}
	int k = 0;
	while((1<<k) < n){
		for(int i = 0; i < n; i++) suff[i] = (suff[i]-(1<<k)+n)%n;
		count_sort(suff,c);
		vector<int> c_new(n);
		c_new[suff[0]] = 0;
		for(int i = 1; i < n; i++){
			pair<int,int> prev = {c[suff[i-1]], c[(suff[i-1]+(1<<k))%n]};
			pair<int,int> now = {c[suff[i]], c[(suff[i]+(1<<k))%n]};
			if(now == prev) c_new[suff[i]] = c_new[suff[i-1]];
			else c_new[suff[i]] = c_new[suff[i-1]]+1;
		}
		c.swap(c_new);
		k++;
	}
	k = 0;
	for(int i = 0; i < n-1; i++){
		int pi = (c[i]-1+n)%n;
		int j = suff[pi];
		while((i+k) < n && (j+k) < n && t[i+k] == t[j+k]) k++;
		lcp[pi] = k;
		k = max(k-1, 0);
	}
}
void print(){
	int n = t.size();
	for(int x : suff) cout << t.substr(x, n-x);
}
