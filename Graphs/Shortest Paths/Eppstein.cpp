// Complexity: O((m + k) * log(n))
#define pb push_back

typedef long long int dist_t;
typedef pair<dist_t,int> info_t;
typedef pair<int,dist_t> edge;
const dist_t NONE = 1e9;

template<typename T>
struct Node {
    T val;
    Node *left, *right;

    Node() : val(T(0, 0)), left(0), right(0) {}
    Node(const T &val) : val(val), left(0), right(0) {}
    Node(Node *t) { *this = *t; }

    static Node<T> *merge(Node *a, Node *b) {
        if (!a)
            return b;
        if (!b)
            return a;

        if (a->val > b->val)
            swap(a, b);

        Node *nt = new Node(a);
        if (rand() % 2)
            nt->right = merge(nt->right, b);
        else
            nt->left = merge(nt->left, b);

        return nt;
    }

    static Node<T> *pop(Node *a) { return merge(a->left, a->right); }
};

using Heap = Node<info_t>;
struct Eppstein {
    int n;
    vector<dist_t> dist;
    vector<int> p;
    vector<vector<edge>> adj, rev;
    vector<Heap*> pq;

    Eppstein(int n): n(n), adj(n), rev(n), pq(n) {}

    void add(int u, int v, dist_t w) {
        adj[u].pb({v, w});
        rev[v].pb({u, w});
    }

    // Calculates dist and parent.
    // parent[u] = edge s.t. u should go to there to reach t
    void shortest_path(int s) {
        dist = vector<dist_t>(n, NONE);
        p = vector<int>(n + 1, -1);

        dist[s] = 0;
        priority_queue<info_t, vector<info_t>, greater<info_t>> pq;
        pq.emplace(0, s);

        while (pq.size()) {
            auto [u, d] = pq.top();
            pq.pop();

            if (dist[u] < d)
                continue;

            for (auto &[v, vw] : rev[u]) {
                dist_t w = d + vw;
                if (dist[v] == -1 || dist[v] > w) {
                    dist[v] = w;
                    p[v] = u;
                    pq.emplace(w, v);
                }
            }
        }
    }

    typedef pair<dist_t, Heap*> tin;
    vector<dist_t> k_shortest_paths(int s, int t, int k) {
        shortest_path(t);

        vector<int> order(n);
        iota(all(order), 0);
        sort(all(order), [&](int i, int j) { return dist[i] < dist[j]; });
        // auto order = toposort_bfs(adj);
        // reverse(all(order));

        for (int u : order) {
            if (dist[u] == NONE)
                continue;

            if (p[u] != -1)
                pq[u] = pq[p[u]];

            int f = 1;

            for (auto &[v, w] : adj[u]) {
                if (dist[v] == NONE)
                    continue;

                if (v != p[u] || dist[u] != dist[v] + w || !f) {
                    Heap *nt = new Heap({dist[v] + w - dist[u], v});
                    pq[u] = Heap::merge(pq[u], nt);
                } else {
                    f = 0;
                }
            }
        }

        if (dist[s] == NONE)
            return vector<dist_t>(k, NONE);

        vector<dist_t> res = {dist[s]};
        k--;
        priority_queue<tin, vector<tin>, greater<tin>> hp;
        if (pq[s])
            hp.emplace(dist[s] + pq[s]->val.first, pq[s]);

        while (k && hp.size()) {
            auto [d, t] = hp.top(); hp.pop();

            res.pb(d);
            k--;

            int v = t->val.second;
            if (pq[v])
                hp.emplace(d + pq[v]->val.first, pq[v]);

            d -= t->val.first;
            t = Heap::pop(t);
            if (t)
                hp.emplace(d + t->val.first, t);
        }

        // Fill with -1 remaining paths
        res.resize(SZ(res) + k, NONE);

        return res;
    }
};