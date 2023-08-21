#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}


pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < a.size(); ++i){
		auto[d, s, t] = extendedGcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
}

lli inverse(lli a, lli m){
	auto[d, x, y] = extendedGcd(a, m);
	if(d != 1) return -1;
	if(x < 0) x += m;
	return x;
}

lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


struct BinomialPrimePower{
    int p, k;
    int pk;
    vector<int> fact_p, inv_fact_p;

    BinomialPrimePower() {}
    BinomialPrimePower(lli p, lli k_): p(p), k(k_){
        pk = 1;
        while(k_--) pk *= p;

        fact_p.resize(pk, 1); 
        for(int i = 2; i < pk; ++i){
            if(i % p == 0) 
                fact_p[i] = fact_p[i-1];
            else
                fact_p[i] = 1LL*i*fact_p[i-1] % pk;
        }

        inv_fact_p.resize(pk, 1);
        inv_fact_p[pk-1] = inverse(fact_p.back(), pk);
        for(int i = pk-2; i > 1; i--){
            if((i+1) % p == 0)
                inv_fact_p[i] = inv_fact_p[i+1];
            else 
                inv_fact_p[i] = 1LL*inv_fact_p[i+1] * (i+1) % pk;
        }
    }

    int nCr(lli n, lli r){
        if(n < 0 || r < 0 || r > n) return 0;

        lli nr = n - r;
        lli ans = 1;
        int e_0 = 0, e_q = 0;
        for(int i = 1; n; i++){
            ans = ans * fact_p[n%pk] % pk;
            ans = ans * inv_fact_p[r%pk] % pk;
            ans = ans * inv_fact_p[nr%pk] % pk;

            n /= p, r /= p, nr /= p;

            int exp = n - r - nr;

            e_0 += exp;
            if(e_0 >= k) return 0;
            if(i >= k) e_q += exp;
        }
        
        if(!(p == 2 and k >= 3) and (e_q & 1))
            ans = pk - ans;
        
        ans = ans * powerMod(p, e_0, pk) % pk;
        return ans;
    }
};


vector< pair<int,int> > factorize(int n){
    vector<pair<int,int>> facts;

    for(int i = 2; 1LL * i * i <= n; i++) {
        if(n % i == 0) {
            int power = 0;
            while(n % i == 0){
                n /= i;
                power++;
            }
            facts.push_back({i, power});
        }
    }
    if(n > 1) facts.push_back({n, 1});
    return facts;
}




int main () {
	fastIO();

    int t, m; cin>>t>>m;

    auto facts = factorize(m);
    int r = SZ(facts);

    vector< BinomialPrimePower > BPPs(r);
    forn(i, r){
        auto [p, e] = facts[i];
        BPPs[i] = BinomialPrimePower(p, e);
    }

    while(t--){
        lli n, k; cin>>n>>k;
        if(m == 1){
            cout << 0 << endl;
            continue;
        }

        vector<lli> a(r), mods(r);

        forn(i, r){
            a[i] = BPPs[i].nCr(n, k);
            mods[i] = BPPs[i].pk;
        }

        auto [ans, mod] = crt(a, mods);
        assert(mod == m);
        cout << ans << endl;
    }


	return 0;
}

