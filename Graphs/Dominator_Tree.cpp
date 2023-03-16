//Grafo indexado en 1
const int MX = 100005;
vi adj[MX], tree[MX], rad[MX], buc[MX];
int sdom[MX], par[MX], dom[MX], dsu[MX], lab[MX];
int arr[MX], rev[MX], cnt;

void init () {
    cnt = 1;
    for (int i = 0; i < MX; i++)
        sdom[i] = dsu[i] = lab[i] = i;
}

void dfs (int u) {
    arr[u] = cnt, rev[cnt] = u, cnt++;

    for (int v : adj[u]) {
        if (!arr[v]) {
            dfs(v);
            par[arr[v]] = arr[u];
        }
        rad[arr[v]].push_back(arr[u]);
    }
}

int find (int u, int x = 0) {
    if (u == dsu[u])
        return x ? -1 : u;
    
    int v = find (dsu[u], x + 1);
    if (v < 0)
        return u;
    
    if (sdom[lab[dsu[u]]] < sdom[lab[u]])
        lab[u] = lab[dsu[u]];
    dsu[u] = v;

    return x ? v : lab[u];
}

void joint (int u, int v) {
    dsu[v] = u;
}

void obtDT () {
    init();
    dfs(1);

    for (int i = cnt - 1; i >= 1; i--) {
        for (int v : rad[i])
            sdom[i] = min(sdom[i], sdom[find(v)]);
        if (i > 1)
            buc[sdom[i]].push_back(i);

        for (int v : buc[i]) {
            int w = find(v);
            if (sdom[v] == sdom[w])
                dom[v] = sdom[v];
            else
                dom[v] = w;
        }

        if (i > 1)
            joint(par[i], i);
    }

    for (int i = 2; i < cnt; i++) {
        if (dom[i] != sdom[i])
            dom[i] = dom[dom[i]];
        tree[rev[i]].push_back(rev[dom[i]]);
        tree[rev[dom[i]]].push_back(rev[i]);
    }
}
