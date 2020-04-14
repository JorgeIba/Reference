//9
vector<int> fact(N+1);
vector<int> inverse(N+1);
fact[0] = inverse[0] = 1;
for(int i =1; i<=N; i++)
{
    fact[i] = (fact[i-1] * i ) % MOD;
    inverse[i] = binPow(fact[i], MOD-2, MOD); //MOD is prime
}