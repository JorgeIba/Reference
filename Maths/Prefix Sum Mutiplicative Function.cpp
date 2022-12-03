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


lli g(lli p, lli a) {
    return a+1;
}

lli G(lli n) {
    lli sum = 0;
    for(lli l = 1, r; l <= n; l=r+1) {
        r = n/(n/l);
        sum += (r-l+1)*(n/l);
    }
    return sum;
}

unordered_map<lli,lli> dp_h[64];
// Recursive formula of h if formula is not an option
lli h(lli p, lli a) {
    if(dp_h[a].count(p)) return dp_h[a][p];

    lli sum = (1LL << a);
    for(int e = a-1; e >= 0; e--) {
        sum -= h(p, e) * g(p, a-e);
    }
    return dp_h[a][p] = sum;
}

// Calculates prefix sum of f(n) where f(n) = h o g
// G(n) is easy to calculate and h(p) = 0
// Works in O(sqrt(n))
lli f(lli n, lli curr_h, int idx_prime=-1) {
    lli ans = G(n) * curr_h;

    for(int idx_next = idx_prime+1; idx_next < SZ(primes); idx_next++){
        lli p = primes[idx_next];
        lli curr_n = n / (p*p);
        if(curr_n == 0) break;
        int exp = 2;

        while (curr_n > 0){
            ans += f(curr_n, curr_h * h(p, exp), idx_next);
            curr_n /= p;
            exp++;
        }
    }
    return ans;
}


// Needs primes upto sqrt(N)
vector<lli> powerful_numbers;
void get_powerful(lli N) {

    queue<tuple<lli,lli>> q;
    q.push({-1, 1});  // primes[-1] = 1
    
    while(!q.empty()) {
        auto [idx, num] = q.front(); q.pop();

        powerful_numbers.push_back(num);

        lli n = N/num;
        for(int y = idx+1, p_next = primes[y]; y < SZ(primes) && n >= p_next*p_next; p_next = primes[++y]) {
            for(lli e = 2, power = p_next; power <= n/p_next; e++) {
                power *= p_next;
                q.push({y, num*power});
            }
        }
    }

    return;
}
