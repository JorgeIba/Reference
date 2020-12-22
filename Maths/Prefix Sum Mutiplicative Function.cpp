/*	
    O(n^(2/3)) if precompute limit = n^(2/3)
    Prefix sum of multiplicative functions :
    p_f : the prefix sum of f (x) (1 <= x <= limit).
    p_g : the prefix sum of g (x) (0 <= x <= N).
    p_c : the prefix sum of f * g (x) (0 <= x <= N).
    limit : the thereshold, generally should be n ^ (2 / 3).
*/
struct Prefix_F{

	typedef lli (*func) (lli);

	func p_f, p_g, p_f_conv_g; //Funcion para obtener P_G y P_F_conv_G (Deben ir en corto)
	lli limit, inv;
	unordered_map <lli, lli> dp;

	Prefix_F(func p_f, func p_g, func p_f_conv_g, lli limit) : p_f (p_f), p_g (p_g), p_f_conv_g (p_f_conv_g), limit(limit) {}

	lli go(lli n) {
		if (n <= limit) return p_f (n);
		if (dp.count(n)) return dp[n];
		lli ans = 0;
		for (lli i = 2, r; i <= n; i = r + 1) {
			r = n / (n / i);
			ans += (p_g(r) - p_g(i - 1) + MOD)%MOD * go(n / i)%MOD;
            if(ans>=MOD) ans-=MOD;
		}
        //assert(ans >= 0 && ans < MOD);
		ans = p_f_conv_g (n) - ans; ans = ans / inv;

		return dp[n] = ans;
	}

	lli get(lli n) {
		if (n <= 0) return 0;
		inv = p_g (1);
		return go(n); 
	}
};
