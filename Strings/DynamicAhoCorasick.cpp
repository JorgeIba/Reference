const int MX = 300005, SIG = 26, LMX = 19;
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
    // all the function can be implemented for static aho corasick
    // when asking if(u) -> if(u -> fail != root)
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
