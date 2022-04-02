vector<lli> getDivs(vector<pair<lli,lli>> &factors)
{
    int n = SZ(factors);
    int factors_count = 1;
    for (int i = 0; i < n; ++i)
    {
        factors_count *= 1+factors[i].second;
    }
    vector<lli> divs(factors_count); divs[0] = 1;
    int count = 1;
    for (int stack_level = 0; stack_level < n; ++stack_level)
    {
        int count_so_far = count;
        int prime = factors[stack_level].first;
        int exponent = factors[stack_level].second;
        int multiplier = 1;
        for (int j = 0; j < exponent; ++j)
        {
            multiplier *= prime;
            for (int i = 0; i < count_so_far; ++i)
            {
                divs[count++] = divs[i] * multiplier;
            }
        }
    }
    return divs;
}


//Need miu and lowestPrime and getDivs O(log(n) + numDivs(distinctPrimes(n)))
lli coprimesInRange(lli n, lli L, lli R)
{
    vector< pair<lli,lli> > factors;

    while(n > 1)
    {
        lli lowestPrime = lp[n];
        factors.push_back({lowestPrime, 1});
        while( n % lowestPrime == 0) 
            n/=lowestPrime;
    }

    lli ans = 0;

    auto divs = getDivs(factors);
    for(auto d: divs)
    {
        ans += miu[d] * (R / d - (L-1)/d);
    }
    return ans;
}
