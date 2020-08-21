lli getLCA(lli u, lli v)
{
    if(depth[u] < depth[v]) swap(u, v);
    lli diff = depth[u] - depth[v];
    for(int i = LOG-1; i>=0; i--)
    {
        if(  diff & (1<<i) )
        {
            u = ancestors[u][i];
        }
    }
    assert(depth[u] == depth[v]);
    for(int i = LOG-1; i>=0; i--)
    {
        if(ancestors[u][i] != ancestors[v][i])
        {
            u = ancestors[u][i];
            v = ancestors[v][i];
        }
    }

    return u!=v? parent[u]: u;
}
