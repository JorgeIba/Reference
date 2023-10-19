#define fi first
#define se second
#define all(v) v.begin(), v.end()
#define pb push_back

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

// Complejidad: O((m + k) * log(n))

struct Node {
    ii val;
    Node *izq, *der;

    Node() : val(ii(0, 0)), izq(0), der(0) {}
    Node(const ii &val) : val(val), izq(0), der(0) {}
    Node(Node *t) { *this = *t; }
};

int n;
vi dis, p;
vector<vii> adj, rev;
vector<Node *> pq;

void init() {
    adj.resize(n + 1);
    rev.resize(n + 1);
    pq.resize(n + 1);
}

Node *merge(Node *a, Node *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    if (a->val > b->val)
        swap(a, b);

    Node *nt = new Node(a);
    if (rand() % 2)
        nt->der = merge(nt->der, b);
    else
        nt->izq = merge(nt->izq, b);

    return nt;
}

Node *pop(Node *a) { return merge(a->izq, a->der); }

void dij(int s) {
    dis = vi(n + 1, -1);
    p = vi(n + 1, -1);

    dis[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.emplace(0, s);

    while (pq.size()) {
        int u = pq.top().se;
        ll d = pq.top().fi;
        pq.pop();

        if (dis[u] < d)
            continue;

        for (ii &v : rev[u]) {
            ll w = d + v.se;
            if (dis[v.fi] == -1 || dis[v.fi] > w) {
                dis[v.fi] = w;
                p[v.fi] = u;
                pq.emplace(w, v.fi);
            }
        }
    }
}

typedef pair<ll, Node *> tin;
vi klp(int s, int t, int k) {
    dij(t);

    vi q(n);
    iota(all(q), 1);

    sort(all(q), [&](int i, int j) { return dis[i] < dis[j]; });

    for (int u : q) {
        if (dis[u] == -1)
            continue;

        if (p[u] != -1)
            pq[u] = pq[p[u]];

        int f = 1;

        for (ii &v : adj[u]) {
            if (dis[v.fi] == -1)
                continue;

            if (v.fi != p[u] || dis[u] != dis[v.fi] + v.se || !f) {
                Node *nt = new Node({dis[v.fi] + v.se - dis[u], v.fi});
                pq[u] = merge(pq[u], nt);
            } else {
                f = 0;
            }
        }
    }

    if (dis[s] == -1)
        return vi(k, -1);

    vi res = {dis[s]};
    k--;
    priority_queue<tin, vector<tin>, greater<tin>> hp;
    if (pq[s])
        hp.emplace(dis[s] + pq[s]->val.fi, pq[s]);

    while (k && hp.size()) {
        ll d = hp.top().fi;
        Node *t = hp.top().se;
        hp.pop();

        res.pb(d);
        k--;

        int v = t->val.se;
        if (pq[v])
            hp.emplace(d + pq[v]->val.fi, pq[v]);

        d -= t->val.fi;
        t = pop(t);
        if (t)
            hp.emplace(d + t->val.fi, t);
    }

    // Rellena con -1 si hay menos de k caminos.
    while (k--)
        res.pb(-1);

    return res;
}

void add(int u, int v, int w) {
    adj[u].pb({v, w});
    rev[v].pb({u, w});
}
