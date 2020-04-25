//12
void build() //ST size == 2*n
{
    for(int i = n; i<2*n; i++)
    {
        ST[i] = nums[i-n];
    }
    for(int i = n-1; i>0; i--)
    {
        ST[i] = Merge( ST[i<<1] , ST[i<<1|1] ) ;
    }
}
//11
Node query(lli l, lli r) //Node could be just an integer
{
    Node MAX1;
    Node MAX2;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        if(l&1) MAX1 = Merge(MAX1, ST[l++]);   
        if(~r&1) MAX2 = Merge(ST[r--],MAX2);
    }
    return Merge(MAX1, MAX2);
}
//10
void update(int index, Node value)
{
    index+=n
    ST[index] = Merge(value, ST[index]);
    for(; index; index>>=1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
    }
}

