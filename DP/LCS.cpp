//19
int lcs(int index1, int index2)
{
    if( index1==s.length() || index2==t.length() ) // s & t are strings
    {
        return 0;
    }
    if( dp[index1][index2] != 1  )
    {
        return dp[index1][index2];
    }
    if(s[index1] == t[index2])
    {
        return dp[index1][index2] = lcs(index1+1, index2 + 1) + 1;
    }
    int primero = lcs(index1 + 1, index2);
    int ultimo = lcs(index1, index2 + 1);
    return dp[index1][index2] = max(primero, segundo);
}