/* 
    Supports:
    Range update floor(a/x)
    Range update a = x
    Range query sum(l, r)
*/


const lli INF = 1e18;
const lli maxN = 5e5+10;
const lli neutro_lazy_equal = -INF;
const lli neutro_lazy_floor = 1;
struct Node{
    lli l, r;

    bool equalRange;

    lli value;
    lli sum;
    lli lazyEQUAL = neutro_lazy_equal;
    lli lazyFLOOR = neutro_lazy_floor;
};


template<typename T>
struct SegmentTreeBeats {
    lli N;
    Node ST[4*maxN]; 


    static const int MIN = 0;
    static const int MAX = 1;
    static const int PLUS = 2;
    static const int FLOOR = 3;


    SegmentTreeBeats(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].equalRange = true;
        ST[curr].value = value;
        ST[curr].sum = value;
    }

    //* NODE UPDATES *//
    void updateNodeEQUAL(int curr, T value){
        ST[curr].sum = (ST[curr].r - ST[curr].l + 1) * value;
        ST[curr].value= value;
        ST[curr].lazyEQUAL = value;
        ST[curr].equalRange = true;
    }

    //* LAZY MANAGMENT *//
    void pushToChildren(int curr){
        if(ST[curr].lazyEQUAL != neutro_lazy_equal){
            updateNodeEQUAL(2*curr, ST[curr].lazyEQUAL);
            updateNodeEQUAL(2*curr+1, ST[curr].lazyEQUAL);
            ST[curr].lazyEQUAL = neutro_lazy_equal;
        }
    }

    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].sum = ST[2 * curr].sum + ST[2 * curr + 1].sum;     

        // Mantain Is same value whole range
        bool sameRangeBoth = ST[2 * curr].equalRange && ST[2 * curr + 1].equalRange;
        bool sameValue = ST[2 * curr].value == ST[2 * curr + 1].value;
        
        ST[curr].value = ST[2 * curr].value;
        ST[curr].equalRange = sameRangeBoth && sameValue;
    }

    //* CONDITIONS *//
    bool breakCondition(int curr, int type_query, T value){
        switch (type_query) {
            // case EQUAL: return false; // leaves same
        }
        return false;
    }

    bool tagCondition(int curr, int type_query, T value){
        switch (type_query) {
            case FLOOR: return ST[curr].equalRange;
            // case EQUAL: return true; // leaves same
        }
        return true;
    }
    
    //* UPDATES *//
    // EQUAL
    void updateEQUAL(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNodeEQUAL(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateEQUAL(2*curr, l, mid, ql, qr, value);
        updateEQUAL(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateEQUAL(int ql, int qr, T value){
        updateEQUAL(1, 1, N, ql, qr, value);
    }


    // FLOOR
    void updateFLOOR(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, FLOOR, value)) return;
        else if(ql <= l && r <= qr && (tagCondition(curr, FLOOR, value))){
            updateNodeEQUAL(curr, ST[curr].value / value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateFLOOR(2*curr, l, mid, ql, qr, value);
        updateFLOOR(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateFLOOR(int ql, int qr, T value){
        updateFLOOR(1, 1, N, ql, qr, value);
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
    
    /*
    void debug(int curr){
        cout << "Value: " << ST[curr].value << ", equalRange: " << ST[curr].equalRange << ", lazyFLOOR: " << ST[curr].lazyFLOOR << ", lazyEQUAL: " << ST[curr].lazyEQUAL << endl;
    }
    void debug_tree(int curr, int l, int r){
        if(l == r) {
            cout << l << " leaf -> "; debug(curr);
        } else {

            pushToChildren(curr);
            lli mid = (l+r)/2;
            debug_tree(2*curr, l, mid);
            debug_tree(2*curr+1, mid+1, r);
            updateFromChildren(curr);

            cout << "not leaf -> "; debug(curr);
        }
    }
    */
};
