const int MX = 500005, SIG = 26;
int nex[MX][SIG], fail[MX], out[MX], finish[MX], cnt[MX], sz = 1;
vector<int> ocu[MX];
int cnt_ocu[MX];
void insert(string &s, int ind) {
    int u = 0;
    for (char c : s) {
        c -= 'a';
        if (!nex[u][c]) {
            nex[u][c] = sz;
            finish[sz] = -1;
            sz++;
        }
        u = nex[u][c];
    }
    finish[u] = ind;
    cnt[u]++;
}
int getFail(int u, int c) {
    while (u && !nex[u][c])
        u = fail[u];
    return nex[u][c];
}
void build() {
    finish[0] = -1;
    queue<int> q;
    for (int i = 0; i < SIG; i++)
        if (nex[0][i])
            q.push(nex[0][i]);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < SIG; i++) {
            int v = nex[u][i];
            if (v && u) {
                fail[v] = getFail(fail[u], i);
                cnt[v] += cnt[fail[v]];
                q.push(v);
                // -> comentar si no se necesitan ocurrencias exactas
                out[v] = fail[v];
                if (finish[out[v]] == -1)
                    out[v] = out[fail[v]];
                // <-
            }
        }
    }
}
int number_of_occ(string &t) {
    int u = 0, res = 0;
    for (int i = 0; i < t.size(); i++) {
        char c = t[i] - 'a';
        if (nex[u][c])
            u = nex[u][c];
        else
            u = getFail(fail[u], c);
        res += cnt[u];
        // <comentar> Si no necesitan las ocurrencias exactas de cada patron
        int v = u;
        while (v && cnt[v]) {
            if (finish[v] != -1) {
                // <comentar> Si no necesitan las posiciones
                ocu[finish[v]].push_back(i);
                // </comentar>
                cnt_ocu[finish[v]]++;
            }
            v = out[v];
        }
        // </comentar>
    }
    return res;
}
