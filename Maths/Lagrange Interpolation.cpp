const int MAXN = 5000 + 100;
long long fact[MAXN], ifact[MAXN];

class LagrangePoly {
  public:
    // f(0), f(1), ..., f(k)
    LagrangePoly(vector<lli> _a) {

        // You can precalculate this soutside
        fact[0] = ifact[0] = 1;
        for (int i = 1; i < MAXN; i++) {
            fact[i] = fact[i - 1] * i % MOD;
            ifact[i] = powerMod(fact[i], MOD - 2, MOD);
        }

        y = _a;
        int n = SZ(y);
        den.resize(n);

        for (int i = 0; i < n; i++) {
            y[i] = (y[i] % MOD + MOD) % MOD;
            den[i] = ifact[n - i - 1] * ifact[i] % MOD;
            if ((n - i - 1) % 2 == 1) {
                den[i] = (MOD - den[i]) % MOD;
            }
        }
    }

    lli getVal(lli x) {
        int n = SZ(y);
        x = (x % MOD + MOD) % MOD;
        if (x < n) {
            return y[(int)x];
        }
        vector<lli> l(n), r(n);
        l[0] = 1;
        for (int i = 1; i < n; i++) {
            l[i] = l[i - 1] * (x - (i - 1) + MOD) % MOD;
        }
        r[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            r[i] = r[i + 1] * (x - (i + 1) + MOD) % MOD;
        }
        lli ans = 0;
        for (int i = 0; i < n; i++) {
            lli coef = l[i] * r[i] % MOD;
            ans = (ans + coef * y[i] % MOD * den[i]) % MOD;
        }
        return ans;
    }

  private:
    vector<lli> y, den;
};