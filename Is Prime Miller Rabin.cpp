//22
bool isPrimeMillerRabin(lli n) //int128 -> __int128
{
    if(n < 2) return false;
    if( ~n & 1) return false;
    lli d = n-1, s = 0; //n-1 = 2^s*k
    for(;(~d&1); d>>=1, s++); //d = k
    for(lli a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if(n == a) return true;
        int128 residuo = binaryPow(a, d, n);
        if(residuo == 1 or residuo == n-1) continue;
        lli x = s;
        while(--x)
        {
            residuo = (residuo * residuo) % n;
            if(residuo == n-1) break;
        }
        if(x==0) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
}
