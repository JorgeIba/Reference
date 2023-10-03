// All in Polynomio.cpp

// O(n log n)
template <typename T> // Returns 1 / F, with d coeffs
vector<T> invertPolynomio(vector<T> F, int d) {
    vector<T> R_n = {powerMod(F[0], p - 2, p)}; // equivalent to: 1 / F[0]
    while (SZ(R_n) <= d) {
        int j = 2 * SZ(R_n);
        auto FF = F;
        FF.resize(j);
        vector<T> RnF = multiply(R_n, FF);
        for (auto &x : RnF)
            x = p - x;
        RnF[0] = RnF[0] + 2 < p ? RnF[0] + 2 : RnF[0] + 2 - p;
        R_n = multiply(R_n, RnF);
        R_n.resize(j);
    }
    R_n.resize(d + 1);
    return R_n;
}

// O(n log n)
template <typename T> // Returns Q -> A = Q*B + R
vector<T> division(vector<T> A, vector<T> B) {
    int n = SZ(A), m = SZ(B);
    if (n < m)
        return {0};
    reverse(all(A));
    reverse(all(B));
    A.resize(n - m + 1);
    B.resize(n - m + 1);
    A = multiply(A, invertPolynomio(B, SZ(B)));
    A.resize(n - m + 1);
    reverse(all(A));
    return A;
}

// O(n log n)
template <typename T> // Return R = A - Q*B
vector<T> remainder(vector<T> A, const vector<T> &B) {
    int n = SZ(A), m = SZ(B);
    if (n >= m) {
        vector<T> R = multiply(division(A, B), B);
        A.resize(m - 1);
        for (int i = 0; i < m - 1; i++) {
            A[i] -= R[i];
            if (A[i] < 0)
                A[i] += p;
        }
    }
    return A;
}

//////////// MULTI-EVALUATE ////////////
// O(n log^2 n)
// Needs Division, Multiply, Remainder, subMod
vector<vector<lli>> STE;            // Segment Tree - Evaluate
void buildSTE(const vector<lli> &x) //(x-x_0)(x-x_1)(x-x_2)...(x-x_n)
{
    int n = SZ(x);
    STE.resize(2 * n);
    for (int i = n; i < 2 * n; i++)
        STE[i] = {subMod(0, x[i - n]), 1}; // Only if it need Mod
    for (int i = n - 1; i; i--)
        STE[i] = multiply(STE[i << 1], STE[i << 1 | 1]);
}

template <typename T>
vector<T> multiEvaluate(const vector<T> &A, const vector<lli> &x) {
    buildSTE(x);
    int m = SZ(x);
    vector<vector<T>> ans(2 * m);
    ans[1] = remainder(A, STE[1]);
    for (int i = 2; i < 2 * m; i++)
        ans[i] = remainder(ans[i >> 1], STE[i]);
    vector<T> evals(m);
    for (int i = m; i < 2 * m; i++)
        evals[i - m] = ans[i][0];
    return evals;
}
//////////// END ////////////

template <typename T> vector<T> derivate(const vector<T> &A) {
    int n = SZ(A);
    vector<T> ans(n - 1);
    for (int i = 1; i < n; i++) {
        ans[i - 1] = (A[i] * i) % p;
    }
    return ans;
}

template <typename T> vector<T> integrate(const vector<T> &P) {
    vector<T> A(SZ(P) + 1);
    for (int i = 1; i <= SZ(P); i++)
        A[i] = (P[i - 1] * inv[i]) % p;
    return A;
}

template <typename T> vector<T> logn(const vector<T> &P) {
    assert(P[0] == 1);
    int n = SZ(P);
    vector<T> A = integrate(multiply(derivate(P), invert(P)));
    A.resize(n);
    return A;
}

template <typename T>
vector<T> exp(const vector<T> &P, int d = -1) { // E(x) = E(x)(1-ln(E(x))+A(x))
    if (d == -1)
        d = SZ(P);
    assert(P[0] == 0);
    vector<T> E(1, 1);
    while (SZ(E) < d) {
        int c = 2 * SZ(E);
        E.resize(c);
        vector<T> S = logn(E);
        for (int i = 0; i < min(SZ(P), SZ(S)); i++) {
            S[i] = (P[i] - S[i] + p) % p;
        }
        S[0] = 1;
        E = multiply(E, S);
        E.resize(c);
    }
    E.resize(d);
    return E;
}

vector<lli> addPoly(vector<lli> P, const vector<lli> &S) {
    P.resize(max(SZ(P), SZ(S)));
    for (int i = 0; i < SZ(S); i++) {
        P[i] = (P[i] + S[i]) % p;
    }
    while (!P.empty() && !P.back())
        P.pop_back();
    return P;
}

// O(n log^2 n)
template <typename T> // Needs multiEvaluate, addPoly, derivate, multiply
vector<T> interpolate(const vector<T> &x, const vector<T> &y) {
    buildSTE(x);
    int n = SZ(x);
    auto pp = derivate(STE[1]);
    vector<T> d = multiEvaluate(pp, x);
    vector<vector<T>> inTree(2 * n);
    for (int i = n; i < 2 * n; i++)
        inTree[i] = {(y[i - n] * powerMod(d[i - n], p - 2, p)) % p}; // y_i /
                                                                     // d_i
    for (int i = n - 1; i; i--) {
        // inTree[i] = inTree[i<<1]*STE[i<<1|1] + inTree[1<<1|1]*STE[i<<1];
        auto F = multiply(inTree[i << 1], STE[i << 1 | 1]);
        auto S = multiply(inTree[i << 1 | 1], STE[i << 1]);
        assert(SZ(S) == SZ(F));
        inTree[i] = addPoly(F, S);
    }
    return inTree[1];
}

/////////MULTIPLY BIG NUMBERS//////////
string normalize(VLL &v) {
    string ss;
    int carry = 0;
    for (int i = SZ(v) - 1; i >= 0; i--) {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] %= 10;
    }

    if (carry > 0)
        ss += (carry + '0');
    for (auto x : v)
        ss += (x + '0');
    return ss;
}

string multiply_numbers(string &s1, string &s2) {
    int degree = s1.length() + s2.length() - 1;
    int sz = nearestPowerTwo(degree);
    if (s1 == "0" || s2 == "0")
        return "0";

    vector<cd> FA(sz), FB(sz);
    for (int i = 0; i < (int)s1.length(); i++)
        FA[i] = (s1[i] - '0');
    for (int i = 0; i < (int)s2.length(); i++)
        FB[i] = (s2[i] - '0');

    fft(FA, false); // Or NTT
    fft(FB, false);
    for (int i = 0; i < sz; i++) {
        FA[i] *= FB[i];
    }
    fft(FA, true);
    VLL ans(degree);
    for (int i = 0; i < degree; i++) {
        ans[i] = (lli)(round(FA[i].real()));
    }

    return normalize(ans);
}
/////////// END ////////////