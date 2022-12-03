/*
    Needs FFT or NTT
    O( N log(n) log(k) )
    N = Order of the recurrence
    K = kth Term
*/
template<typename T>
T kthTermLinearRecurrence(const vector<T> &initial, const vector<T> &constants, lli k) {
	int n = SZ(initial);
	if(k < n) return initial[k];

	Poly<T> R_k = vector<lli>{0, 1}; // x -> x^k
	Poly<T> F = constants;
    F = F * (MOD-1);
    F.resize(n+1);
    F[n] = 1;

    // x^k mod F
    auto MODU = R_k.binPow(k, F);
	
    T ans = 0;
    for(int i = 0; i < n; i++) 
        (ans += initial[i] * MODU[i] % MOD) %= MOD; //! MOD
    return ans;
}


/*
    O( N^2 log(K) )
	0 - Indexed
*/
lli kthTermLinearRecurrence(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= MOD;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= MOD;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= MOD;
	return nValue;
}
 