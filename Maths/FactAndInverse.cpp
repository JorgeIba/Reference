// 13
const lli MAXN = 1e6;
const lli MOD = 998244353; // Initialize
vector<lli> fact(MAXN + 1, 1), inv(MAXN + 1, 1), invFact(MAXN + 1, 1);
void prec() {
    for (lli i = 2; i <= MAXN; ++i) {
        fact[i] = i * fact[i - 1] % MOD;
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        invFact[i] = inv[i] * invFact[i - 1] % MOD;
    }
}

lli nCr(lli n, lli r) {
    if (n < 0 || r > n || r < 0)
        return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// 15
lli nCr[MAXN + 5][MAXN + 5];
void prec() {
    nCr[0][0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i)
                nCr[i][j] = 1;
            else {
                nCr[i][j] = (nCr[i - 1][j - 1] + nCr[i - 1][j]);
            }
        }
    }
}
