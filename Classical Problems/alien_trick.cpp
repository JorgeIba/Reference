const int MAXN = 1e6 + 5;
 
int n,k,l;
lli lambda;
bool A[MAXN];
string s;
plli mem[MAXN];
 
plli dp(int i){
	if(i >= n)
		return {0,0};
	plli& ans = mem[i];
	if(ans.fi != -1)
		return ans;
	plli a = dp(i+1);
	a.fi += A[i];
	plli b = dp(i+l);
	b.fi += lambda;
	b.se += 1;
	return ans = min(a,b);
}
 
int solve(){
	lli l,r;
	l = 0; r = 1e6+5;
	plli ans;
	forn(i,22){
		lambda = (l+r) / 2;
		fill(mem,mem+n,make_pair(-1,-1));
		ans = dp(0);
//		cout << "lamda: " << lambda << " ans: " << ans.fi << " steps: " << ans.se << endl;
		if(ans.se <= k)
			r = lambda;
		else
			l = lambda;
	}
	lambda = r;
	fill(mem,mem+n,make_pair(-1,-1));
	ans = dp(0);
//	cout << "ans: " << ans.fi << " lambda: " << lambda << endl;
	return ans.fi - lambda*k;
}
