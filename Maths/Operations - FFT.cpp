
template<typename T>
vector<T> invertPolynomio(vector<T> F, int d) // R_2n = R_n(2 - R_nF)
{
    vector<T> R_n = { powerMod(F[0], p-2, p) }; //equivalent to: 1 / F[0]
    while(SZ(R_n) <= d)
    {
        int j = 2*SZ(R_n);
        auto FF = F; FF.resize(j);
        vector<T> RnF = multiply<p,g>(R_n, FF);
        for(auto &x: RnF) x = p-x;
        RnF[0] = RnF[0] + 2 < p? RnF[0] + 2: RnF[0] + 2 - p; 
        R_n = multiply<p,g>(R_n, RnF);
        R_n.resize(j);
    }
    R_n.resize(d+1);
    return R_n;
}


template<typename T> //A = Q*B + R
vector<T> division(vector<T> A, vector<T> B) //Needs invertPolynomio
{
    int n = SZ(A), m = SZ(B);
    if(n < m) return {0};
    reverse(all(A));
    reverse(all(B));
    A.resize(n-m+1); B.resize(n-m+1);
    A = multiply(A, invertPolynomio(B, m));
    A.resize(n-m+1);
    reverse(all(A)); //R = A-Q*B
    return A;
}


/////////MULTIPLY BIG NUMBERS//////////
string normalize(VLL &v)
{
    string ss;
    int carry =0;
    for(int i = SZ(v)-1; i>=0; i--)
    {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] %= 10;
    }

    if(carry>0)
        ss+=(carry+'0');
    for(auto x: v) ss+=(x+'0');
    return ss;
}

string multiply_numbers(string &s1, string &s2)
{
    int degree = s1.length() + s2.length() - 1;
    int sz = nearestPowerTwo(degree);   
    if(s1 == "0" || s2 == "0") return "0";

    vector<cd> FA(sz), FB(sz);
    for(int i = 0; i<(int)s1.length(); i++) FA[i] = (s1[i] - '0');
    for(int i = 0; i<(int)s2.length(); i++) FB[i] = (s2[i] - '0');

    fft(FA, false);
    fft(FB, false);

    for(int i = 0; i<sz; i++)
    {
        FA[i]*=FB[i];
    }
    fft(FA, true);
    VLL ans(degree);
    for(int i = 0; i<degree; i++)
    {
        ans[i] = (lli)(round(FA[i].real()));
    }

    return normalize(ans);
}
/////////// END ////////////