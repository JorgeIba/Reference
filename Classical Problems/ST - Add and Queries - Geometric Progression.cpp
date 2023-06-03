/*
    If you have an array [0, 0, 0, 0, 0, 0]
    update(l, r) adds x, x^2, x^3, x^4 starting from l

    Example: 
    x = 2
    update(2, 5) -> [0, 2, 4, 8, 16, 0]

    query(l, r) -> sum(arr[l], arr[l+1], ..., arr[r])
*/


struct Node{

    int l=0, r=0;

    lli ls=0, rs=0;
    bool flagLazy = false;
    lli lazy_ls=0, lazy_rs=0;

    Node(){}
    Node(int l, int r): l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(l, b.r);
        res.ls = (ls + b.ls) % MOD;
        res.rs = (rs + b.rs) % MOD;

        return res;
    }

    // Update range
    void updateNode(lli sum_l, lli sum_r) {
        ls = (ls + sum_l) % MOD;
        rs = (rs + sum_r) % MOD;

        lazy_ls = (lazy_ls + sum_l) % MOD;
        lazy_rs = (lazy_rs + sum_r) % MOD;
        flagLazy = true;
    }

    void resetLazy() {
        flagLazy = false;
        lazy_ls = 0;
        lazy_rs = 0;
    }

};

struct SegmentTree {
    vector<Node> ST;
    int N;
    lli x, x_inv;

    SegmentTree(int n, lli x): N(n), x(x) {
        x_inv = powerMod(x, MOD-2);
        ST.resize(4*N);
        build(1, 1, N);
    }

    void build(int curr, int l, int r){
        ST[curr].l = l, ST[curr].r = r;

        if(l == r) return;
        int mid = l + (r-l)/2;
        build(2*curr, l, mid);
        build(2*curr+1, mid+1, r);
    }

    void pushToChildren(int curr){
        if(ST[curr].flagLazy){
            int size_child_left  = (ST[2*curr].r   - ST[2*curr].l + 1);
            int size_child_right = (ST[2*curr+1].r - ST[2*curr+1].l + 1);

            lli sum_r_to_left  = ST[curr].lazy_rs * powerMod(x_inv, size_child_right) % MOD;
            lli sum_l_to_right = ST[curr].lazy_ls * powerMod(x, size_child_left) % MOD;

            ST[2*curr].updateNode(ST[curr].lazy_ls, sum_r_to_left);
            ST[2*curr+1].updateNode(sum_l_to_right, ST[curr].lazy_rs);

            ST[curr].resetLazy();
        }
    }

    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, int start)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            int offset_l = l - start + 1;
            int offset_r = offset_l + (r-l+1) - 1;
            ST[curr].updateNode(powerMod(x, offset_l), powerMod(x, offset_r + 1));
            return;
        }

        pushToChildren(curr);

        int mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, start);
        update(2*curr+1, mid+1, r, ql, qr, start);

        ST[curr] = ST[2*curr] + ST[2*curr+1];
    }
    void update(int ql, int qr, int start){
        update(1, 1, N, ql, qr, start);
    }
    
    // QUERY
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        if(ql <= l && r <= qr) return ST[curr];
        else {
            pushToChildren(curr);
            int mid = l + (r-l) / 2;
            return query(2*curr, l, mid, ql, qr) + query(2*curr+1, mid+1, r, ql, qr);
        }
    }
    lli query(int ql, int qr){
        auto ans = query(1, 1, N, ql, qr);
        
        return (ans.ls - ans.rs + MOD) * powerMod(1 - x + MOD, MOD-2) % MOD;;
    }
};