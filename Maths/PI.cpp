// Calculate 2^k + 3^k + 5^k + ...
// For each value floor(N/i)
struct SumPrimes{
    vector<lli> poss_vals, dp;
    lli N, k, sqN, sz_vals;

    SumPrimes(lli N, lli k = 0): N(N), k(k), sqN(sqrt(N)) {
        poss_vals.reserve(2*sqN);
        for(lli i = 1; i <= sqN; i++) {
            poss_vals.push_back(i);
            if(N/i != i) poss_vals.push_back(N/i);
        }    
        sort(all(poss_vals), greater<lli>());
        sz_vals = SZ(poss_vals);
        dp.resize(sz_vals + 1);

        build(N);
    }

    lli powerSum(lli n) { 
        if(k == 0) return n;
        else if(k == 1) return n*(n+1)/2; //! MOD
        else return -1;
    }

    lli getIdx(lli n){
        if (n <= sqN) return n - 1;
        else return  sz_vals - (N / n);
    }

    lli query(lli n) { return dp[getIdx(n)];}

    void build(lli N) {
        for(auto n: poss_vals) 
            dp[ getIdx(n)  ] = powerSum(n)-1;

        for(lli p = 2; p <= sqN; p++)
        {
            if(dp[ getIdx(p) ] == dp[ getIdx(p-1) ]) continue;
            lli p_k = binPower(p, k);

            for(auto n: poss_vals) {
                if(p*p > n) break;
                dp[ getIdx(n) ] -=  p_k*(dp[ getIdx(n / p)] - dp[ getIdx(p-1) ]); //! MOD
            }
        }
    }
};