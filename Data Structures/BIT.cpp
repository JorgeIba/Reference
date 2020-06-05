//10
vector<lli> BIT(MAXN+1);
void update(lli idx, lli value)
{
    while(idx < BIT.size())
    {
        BIT[idx] += value;
        idx += idx&(-idx);
    }
}
//10
lli sum(lli idx)
{
    lli res = 0;
    while(idx)
    {
        res += BIT[idx];
        idx -= idx&(-idx);
    }
    return res;
}