Aho Corasick Dinámico : const int MX = 300005, SIG = 26, LMX = 19;

struct aho_corasick {
    struct Node {
        Node *sig[SIG], *fail;
        int finish, cnt;

        Node() : fail(this), finish(0), cnt(0) {
            for (int i = 0; i < SIG; i++)
                sig[i] = this;
        }

        Node(Node *root) : fail(root), finish(0), cnt(0) {
            for (int i = 0; i < SIG; i++)
                sig[i] = root;
        }
    };

    Node *root;

    aho_corasick() { reset(); }

    void reset() { root = new Node; }

    void insert(string &s, int ind) {
        Node *u = root;

        for (char c : s) {
            c -= 'a';

            if (u->sig[c] == root) {
                u->sig[c] = new Node(root);
                u->sig[c]->finish = -1;
            }

            u = u->sig[c];
        }

        u->finish = ind;
        u->cnt++;
    }

    Node *getFail(Node *u, int c) {
        while (u != root && u->sig[c] == root)
            u = u->fail;
        return u->sig[c];
    }

    void build() {
        queue<Node *> q;

        for (int i = 0; i < SIG; i++)
            if (root->sig[i] != root)
                q.push(root->sig[i]);

        while (q.size()) {
            Node *u = q.front();
            q.pop();

            for (int i = 0; i < SIG; i++) {
                Node *v = u->sig[i];

                if (v != root) {
                    v->fail = getFail(u->fail, i);
                    v->cnt += v->fail->cnt;
                    q.push(v);
                }
            }
        }
    }

    int match(string &t) {
        Node *u = root;
        int res = 0;

        for (int i = 0; i < t.size(); i++) {
            char c = t[i] - 'a';

            if (u->sig[c] != root)
                u = u->sig[c];
            else
                u = getFail(u->fail, c);
            res += u->cnt;
        }

        return res;
    }
};

typedef vector<string *> vs;

struct dynamic_aho_corasick {
    aho_corasick ac[LMX];
    vs s[LMX];
    int exi;

    dynamic_aho_corasick() : exi(0) {}

    int insert(string &str) {
        int j = 0;
        while (exi & (1 << j))
            j++;
        s[j].push_back(new string(str));

        for (int i = 0; i < j; i++) {
            for (string *t : s[i])
                s[j].push_back(t);
            s[i].clear();
            ac[i].reset();
        }

        for (string *t : s[j])
            ac[j].insert(*t, 1);
        ac[j].build();

        exi++;
    }

    int match(string &t) {
        int res = 0;

        for (int i = 0; i < LMX; i++)
            if (exi & (1 << i))
                res += ac[i].match(t);

        return res;
    }
};
