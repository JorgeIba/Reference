int MOD;

Poly operator*(Poly A, Poly B) {
    Poly C(SZ(A) + SZ(B) - 1);

    for(int i = 0; i < SZ(A); i++) {
        for(int j = 0; j < SZ(B); j++) {
            C[i+j] += 1LL*A[i] * B[j] % MOD;
            if(C[i+j] >= MOD) C[i+j] -= MOD;
        }
    }

    return C;
}

Poly operator%(Poly A, int m) {
    Poly C = A;
    for(int i = m; i < SZ(C); i++) {
        (C[i%m] += C[i]) %= MOD;
    }
    C.resize(m);
    return C;
}


Poly powerMod(Poly A, lli b, int m) {
    Poly R = {1};
    while(b) {
        if(b & 1) R = (R * A) % m;
        A = (A * A) % m;
        b >>= 1; 
    }

    return R;
}

// f(n, 3, 1) = nCr(n, 1) + nCr(n, 4) + nCr(n, 7)
// f(n, 5, 4) = nCr(n, 4) + nCr(n, 9) + nCr(n, 14)
// You can compute this with fft to reduce complexity
lli BinomialSumFiltered(lli n, lli m, lli r) {
    Poly base = {1, 1};
    auto RES = powerMod(base, n, m);
    return RES[r];
}