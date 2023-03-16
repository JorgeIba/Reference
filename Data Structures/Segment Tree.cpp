struct Node{
    lli value=0, sum=0;
    lli lazy = 0;
    bool flagLazy = false;

    lli l, r;

    Node(){}
    Node(lli value, int l, int r): value(value), sum(value), l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(0, l, b.r);
        res.sum = sum + b.sum;
        return res;
    }
};

template<typename T>
struct SegmentTree {
    vector<Node> ST;
    int N;

    SegmentTree(int n, const vector<T> &values): N(n){
        ST.resize(4*N);
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value, int idx){
        ST[curr] = Node(value, idx, idx);
    }

    //* NODE UPDATES *//
    void updateNode(int curr, T value){
        lli sz = ST[curr].r - ST[curr].l + 1;
        
        ST[curr].value = value;
        ST[curr].sum += sz*value;

        ST[curr].lazy += value;
        ST[curr].flagLazy = true;
    }

    void pushToChildren(int curr){
        if(ST[curr].flagLazy){
            updateNode(2*curr, ST[curr].lazy);
            updateNode(2*curr+1, ST[curr].lazy);
            ST[curr].flagLazy = false;
        }
    }

    Node updateFromChildren(Node left, Node right){
        return left + right;
    }
    
    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNode(curr, value);
            return;
        }

        pushToChildren(curr);

        int mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, value);
        update(2*curr+1, mid+1, r, ql, qr, value);

        ST[curr] = updateFromChildren(ST[2*curr], ST[2*curr+1]);
    }
    void update(int ql, int qr, T value){
        update(1, 1, N, ql, qr, value);
    }
    
    // QUERY
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        else if(ql <= l && r <= qr) return ST[curr];
        else {
            pushToChildren(curr);
            int mid = l + (r-l) / 2;
            return query(2*curr, l, mid, ql, qr) + query(2*curr+1, mid+1, r, ql, qr);
        }
    }
    Node query(int ql, int qr){
        return query(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1], l);
        } else {
            int mid = l + (r-l)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            ST[curr] = updateFromChildren(ST[2*curr], ST[2*curr+1]);
        }
    }
};



// Version mejorada pero falta testear la parte del lazy:

struct Node{
    lli dishes=0, people=0;

    int l, r;

    bool flagLazy = false;
    int lazy = 0;

    Node(){}
    Node(lli dishes, lli people, int l, int r): dishes(dishes), people(people), l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(0, 0, l, b.r);
        res.dishes = b.dishes + (dishes - min(dishes, b.people));
        res.people = people + (b.people - min(dishes, b.people));

        return res;
    }

    // Update range
    void updateNode(int type, int value) {
        if(type == 0) {
            dishes += value;
        } else {
            people += value;
        }

        int match = min(dishes, people);

        dishes -= match;
        people -= match;
    }
};

// T Lo que le vas a pasar
template<typename T>
struct SegmentTree {
    vector<Node> ST;
    int N;

    SegmentTree(int n, const vector<T> &values): N(n){
        ST.resize(4*N);
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value, int idx){
        if(value > 0) {
            ST[curr] = Node(value, 0, idx, idx);
        } else {
            ST[curr] = Node(0, -value, idx, idx);
        }
    }


    // void pushToChildren(int curr){
    //     if(ST[curr].flagLazy){
    //         ST[2*curr].updateNode(ST[curr].lazy);
    //         ST[2*curr+1].updateNode(ST[curr].lazy);
    //         ST[curr].flagLazy = false;
    //     }
    // }

    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, int type, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            ST[curr].updateNode(type, value);
            return;
        }

        // pushToChildren(curr);

        int mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, type, value);
        update(2*curr+1, mid+1, r, ql, qr, type, value);

        ST[curr] = ST[2*curr] + ST[2*curr+1];
    }
    void update(int ql, int qr, int type, T value){
        update(1, 1, N, ql, qr, type, value);
    }
    
    // QUERY
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        else if(ql <= l && r <= qr) return ST[curr];
        else {
            // pushToChildren(curr);
            int mid = l + (r-l) / 2;
            return query(2*curr, l, mid, ql, qr) + query(2*curr+1, mid+1, r, ql, qr);
        }
    }
    Node query(int ql, int qr){
        return query(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1], l);
        } else {
            int mid = l + (r-l)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            ST[curr] = updateFromChildren(ST[2*curr], ST[2*curr+1]);
        }
    }
};

