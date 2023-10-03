// Calculate array G
// g_d = a_i * b_j where gcd(i, j) = d
// a and b are 1-indexed
// forr(i, 1, n)
//   forr(j, 1, n)
//     g[gcd(i, j)] += a[i]*b[j]
// O(n log n)
template <int mod = MOD, typename T = int>
vector<T> gcdConvolution(const vector<T> &a, const vector<T> &b) {
    int n = SZ(a);

    vector<T> A(n + 1), B(n + 1), G(n + 1);
    for (int g = 1; g <= n; g++) {
        for (int k = g; k <= n; k += g) {
            A[g] = (A[g] + a[k - 1]) % mod;
            B[g] = (B[g] + b[k - 1]) % mod;
        }
        G[g] = 1LL * A[g] * B[g] % mod;
    }

    vector<T> dp_g(n);
    for (int i = n; i >= 1; i--) {

        dp_g[i - 1] = G[i];

        for (int k = 2 * i; k <= n; k += i) {
            dp_g[i - 1] = (dp_g[i - 1] - dp_g[k - 1] + mod) % mod;
        }
    }
    return dp_g;
}