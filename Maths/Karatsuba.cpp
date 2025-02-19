Poly karatsuba(const Poly &A, const Poly &B) {
    int n = SZ(A); // A and B need to be same size
    if(n <= 0) return {};
    if(n <= 35) return A * B;
    
    int n0 = n / 2;
    
    Poly A0(A.begin(), A.begin()+n0), A1(A.begin()+n0, A.end());
    Poly B0(B.begin(), B.begin()+n0), B1(B.begin()+n0, B.end());
    
    Poly A0B0 = karatsuba(A0, B0);
    Poly A0A1_B0B1 = karatsuba(A0 + A1, B0 + B1);
    Poly A1B1 = karatsuba(A1, B1);
    Poly A0B1_A1B0 = A0A1_B0B1 - A0B0 - A1B1;

    Poly C(SZ(A) + SZ(B) - 1);
    forn(i, SZ(A0B0)) C[i] += A0B0[i];
    forn(i, SZ(A0B1_A1B0)) C[n0 + i] += A0B1_A1B0[i];
    forn(i, SZ(A1B1)) C[n0 + n0 + i] += A1B1[i];

    return C;
}
