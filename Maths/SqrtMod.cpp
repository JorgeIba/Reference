// Tonelli - Shanks
// Solve x^2 = a mod p
// If p*p > 1e18 use multMod
// Solutions = {x, p-x}
// O(lg^2 P)
lli sqrtMod(lli a, lli p) {
    if (p == 2)
        return a;
    if (a % p == 0)
        return 0;
    if (powerMod(a, (p - 1) / 2, p) == p - 1)
        return -1;
    if (p % 4 == 3)
        return powerMod(a, (p + 1) / 4, p);

    lli S = 0, q = p - 1;
    while (~q & 1)
        q >>= 1, S++;

    lli n = 2;
    while (powerMod(n, (p - 1) / 2, p) != p - 1)
        n++;

    lli M = S;
    lli c = powerMod(n, q, p);
    lli t = powerMod(a, q, p);
    lli R = powerMod(a, (q + 1) / 2, p);

    while (true) {
        if (t == 1)
            return R;

        lli aux_t = t;
        int m = 1;
        for (; m < M; m++) {
            aux_t = aux_t * aux_t % p;
            if (aux_t == 1)
                break;
        }
        lli b = powerMod(c, 1LL << (M - m - 1), p);
        // for(int i = 0; i < M-m-1; i++) b = b*b % p;
        M = m;
        c = b * b % p;
        t = t * c % p;
        R = R * b % p;
    }
}

// Solve x^2 = n  mod p^k
// p is odd prime
// Solutions: {x, p^k - x};
lli sqrtModK(lli n, lli p, lli k) {
    // Initial Value
    lli ans_i = sqrtMod(n, p);
    if (ans_i == -1 || ans_i == 0)
        return ans_i;

    lli reps = 0;
    while ((1LL << reps) < k)
        reps++;
    lli pi = p;

    for (int i = 1; i <= reps; i++) {
        // f(ans + p^i * t ) = 0 mod p^2i

        lli inv = modularInverse(2 * ans_i, pi);
        lli c = (n - ans_i * ans_i) / pi;
        lli t = c * inv % pi;
        if (t < 0)
            t += pi;

        ans_i = ans_i + pi * t;
        pi = pi * pi;

        ans_i %= pi;
    }

    lli pk = power(p, k);
    return ans_i % pk;
}