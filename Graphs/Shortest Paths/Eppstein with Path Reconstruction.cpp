#define fi first
#define se second
#define all(v) v.begin(), v.end()
#define pb push_back

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

// Complejidad: O((m + k) * log(n) + k * MAX_PATH_LENTH)
// MAX_PATH_LENTH es n cuando el grafo es un DAG, y n * k cuando tiene ciclos.

struct Node {
  pair<ll, ii> val;
  Node *izq, *der;

  Node() : val({0, {0, 0}}), izq(0), der(0) {}
  Node(const pair<ll, ii> &val) : val(val), izq(0), der(0) {}
  Node(Node *t) { *this = *t; }
};

struct Stack {
  ii val;
  Stack *nex;

  Stack(ii val = {0, 0}, Stack *nex = 0) : val(val), nex(nex) {}
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

typedef pair<pair<ll, Stack *>, Node *> tin;
vector<pair<ll, vi>> klp(int s, int t, int k) {
  dij(t);

  vi q(n);
  iota(all(q), 1);

  // Este sort asume que no hay aristas negativas o con valor igual a cero.
  // Si existen dichas aristas, hay que encontrar un orden topológico tal que
  // p[u] aparezca en el vector q antes que u.
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
        Node *nt = new Node({dis[v.fi] + v.se - dis[u], {u, v.fi}});
        pq[u] = merge(pq[u], nt);
      } else {
        f = 0;
      }
    }
  }

  if (dis[s] == -1)
    return vector<pair<ll, vi>>(k, {-1, {}});

  vector<pair<ll, Stack *>> paths;
  paths.pb({dis[s], 0});

  k--;
  priority_queue<tin, vector<tin>, greater<tin>> hp;
  if (pq[s])
    hp.push({{dis[s] + pq[s]->val.fi, 0}, pq[s]});

  while (k && hp.size()) {
    ll d = hp.top().fi.fi;
    Stack *st = hp.top().fi.se;
    Node *t = hp.top().se;
    hp.pop();

    Stack *new_st = new Stack(t->val.se, st);
    paths.pb({d, new_st});
    k--;

    int v = t->val.se.se;
    if (pq[v])
      hp.push({{d + pq[v]->val.fi, new_st}, pq[v]});

    d -= t->val.fi;
    t = pop(t);
    if (t)
      hp.push({{d + t->val.fi, st}, t});
  }

  while (k--) {
    paths.pb({-1, 0});
  }

  vector<pair<ll, vi>> res;

  for (auto &path : paths) {
    stack<ii> det;
    Stack *it = path.se;
    while (it) {
      det.push(it->val);
      it = it->nex;
    }

    int u = s;
    vi se = {s};
    while (u != t || det.size()) {
      if (det.size() && u == det.top().fi) {
        u = det.top().se;
        det.pop();
      } else {
        u = p[u];
      }
      se.pb(u);
    }

    res.pb({path.fi, se});
  }

  return res;
}

void add(int u, int v, int w) {
  adj[u].pb({v, w});
  rev[v].pb({u, w});
}
