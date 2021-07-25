//13
const lli maxN = 1e6;
const lli MOD = 998244353; // Initialize
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

//15
lli nCr[maxN+5][maxN+5];
void prec()
{
    nCr[0][0] = 1;
    for(int i = 1; i<=maxN; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            if(j==0 || j == i) nCr[i][j] = 1;
            else
            {
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]);
            }
            //cout << nCr[i][j] << " ";
        }
        //cout << endl;
    }
}
