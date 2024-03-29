int nearestPowerTwo(int n) {
    int r = 1;
    while (r < n)
        r <<= 1;
    return r;
}

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    b %= mod - 1;
    if (b < 0)
        b += mod - 1;
    while (b) {
        if (b & 1)
            res = (res * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

// This speeds up mucho when NTT is used a lot

/*
lli wp[MAXLOG][MAXN], wp_inv[MAXLOG][MAXN];
void prec_ntt() {
    for(int i = 0, n = 1; i < MAXLOG; i++, n <<= 1) {
        lli wk = powerMod(g, (p-1) / (n << 1), p);
        lli wk_inv = powerMod(g, -1 * (p-1) / (n << 1), p);
        wp[i][0] = 1;
        wp_inv[i][0] = 1;
        for(int j = 1; j < MAXN; j++){
            wp[i][j] = wp[i][j-1] * wk % p;
            wp_inv[i][j] = wp_inv[i][j-1] * wk_inv % p;
        }
    }
}
*/
// You need to change this line
// int u = A[i + j], v = (A[i+j+k] * (inv ? wp_inv[logg][j] : wp[logg][j] ) ) %
// p; comment these:
//
/*
        vector<lli> wp(n>>1, 1);

        lli wk = powerMod(g, (inv?-1:1) * (p - 1) / (k<<1), p);
        for(int j = 1; j < k; ++j)
                wp[j] = (wp[j - 1] * wk) % p;
*/
// where logg = log2(k)
// so change for(int k = 1, logg = 0; k < n; k <<= 1, logg++){

template <int p, int g, typename T>
void ntt(vector<T> &A, bool inv) { // O(n log n)
    int n = SZ(A);
    for (int i = 1, j = 0; i < n - 1; ++i) {
        for (int k = n >> 1; (j ^= k) < k; k >>= 1)
            ;
        if (i < j)
            swap(A[i], A[j]);
    }

    vector<lli> wp(n >> 1, 1);

    for (int k = 1; k < n; k <<= 1) {
        lli wk = powerMod(g, (inv ? -1 : 1) * (p - 1) / (k << 1), p);
        for (int j = 1; j < k; ++j)
            wp[j] = (wp[j - 1] * wk) % p;

        for (int i = 0; i < n; i += k << 1) {
            for (int j = 0; j < k; ++j) {
                int u = A[i + j], v = (A[i + j + k] * wp[j]) % p;
                A[i + j] = (u + v < p) ? u + v : u + v - p;
                A[i + j + k] = (u - v >= 0) ? u - v : u - v + p;
            }
        }
    }

    if (inv) {
        lli inv_n = powerMod(n, p - 2, p);
        for (auto &x : A)
            x = (x * inv_n) % p;
    }
}

template <int p = 998244353, int g = 3, typename T>
vector<T> multiply(vector<T> A, vector<T> B) { // O(n logn) it uses NTT
    int sz = SZ(A) + SZ(B) - 1;
    int size = nearestPowerTwo(sz);

    A.resize(size), B.resize(size);
    ntt<p, g>(A, false);
    ntt<p, g>(B, false);
    for (int i = 0; i < size; i++)
        A[i] = (lli)A[i] * B[i] % p;
    ntt<p, g>(A, true);

    A.resize(sz);
    return A;
}

/* To found primitive roots
        for(lli g = 2; g<=20 ; g++)
    {
        if(powerMod(g, (MOD-1)/2, MOD) != 1) cout << g << endl;
    }
*/
