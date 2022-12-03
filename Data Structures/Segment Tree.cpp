/* 
    To support other things, you need to:
    
    * Add extra things in Node
    * Add update method in UPDATES 
    * Add update node method in NODE UPDATES
    * Support updateFromChildren
    * Add query method in QUERIES
*/

const lli maxN = 5e5+10;
const lli neutro_lazy_sum = 0;
struct Node{
    lli l, r;

    lli value;
    lli sum;
    lli lazySUM = neutro_lazy_sum;
};

Node ST[4*maxN]; 

template<typename T>
struct SegmentTree {
    lli N;
    

    SegmentTree(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].value = value;
        ST[curr].sum = value;
    }

    //* NODE UPDATES *//
    void updateNodeSUM(int curr, T value){
        ST[curr].sum += (ST[curr].r - ST[curr].l + 1) * value;
        ST[curr].value += value;
        ST[curr].lazySUM += value;
    }

    //* LAZY MANAGMENT *//
    void pushToChildren(int curr){
        if(ST[curr].lazySUM != neutro_lazy_sum){
            updateNodeSUM(2*curr, ST[curr].lazySUM);
            updateNodeSUM(2*curr+1, ST[curr].lazySUM);
            ST[curr].lazySUM = neutro_lazy_sum;
        }
    }

    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].sum = ST[2 * curr].sum + ST[2 * curr + 1].sum;     
    }
    
    //* UPDATES *//
    // SUM
    void updateSUM(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNodeSUM(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateSUM(2*curr, l, mid, ql, qr, value);
        updateSUM(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateSUM(int ql, int qr, T value){
        updateSUM(1, 1, N, ql, qr, value);
    }
    
    //? QUERIES ?//
    // SUM
    lli query_sum(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return 0;
        else if(ql <= l && r <= qr) return ST[curr].sum;
        else {
            pushToChildren(curr);
            lli mid = (l+r) / 2;
            return query_sum(2*curr, l, mid, ql, qr) + query_sum(2*curr+1, mid+1, r, ql, qr);
        }
    }
    lli query_sum(int ql, int qr){
        return query_sum(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1]);
        } else {
            lli mid = (l+r)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            updateFromChildren(curr);
        }
    }
};