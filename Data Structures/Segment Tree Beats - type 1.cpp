/* 
    Supports:
    Range update min(a,x)
    Range update max(a,x)
    Range update a += x
    Range query sum(l, r)

    for Range update a %= x
    tagCondition is just if node is a leaf
    breakCondition is just if max < x
*/



const lli INF = 1e18;
const lli maxN = 2e5+10;
const lli neutro_lazy_sum = 0;
const lli neutro_lazy_equal = -INF;
struct Node{
    lli l, r;

    lli max;
    lli frMax;
    lli secondMax;

    lli min;
    lli frMin;
    lli secondMin;

    lli sum;
    lli lazySUM = neutro_lazy_sum;
    lli lazyEQUAL = neutro_lazy_equal;
};


template<typename T>
struct SegmentTreeBeats {
    lli N;
    Node ST[4*maxN]; 


    static const int MIN = 0;
    static const int MAX = 1;
    static const int PLUS = 2;


    SegmentTreeBeats(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].max = ST[curr].min = ST[curr].sum = value;
        ST[curr].frMax = ST[curr].frMin = 1;
        ST[curr].secondMax = -INF;
        ST[curr].secondMin = INF;
    }

    // Updates
    void updateNodeEQUAL(int curr, T value){
        ST[curr].max = ST[curr].min = value;
        ST[curr].secondMax = -INF;
        ST[curr].secondMin = INF;

        ST[curr].frMax = ST[curr].frMin = (ST[curr].r - ST[curr].l + 1);

        ST[curr].sum = (ST[curr].r - ST[curr].l + 1) * value;
        ST[curr].lazySUM = 0;
        ST[curr].lazyEQUAL = value;
    }

    void updateNodeMAX(int curr, T value){
        if(value > ST[curr].min){
            if(ST[curr].max == ST[curr].min){
                updateNodeEQUAL(curr, value);
            } 
            else {
                if(ST[curr].secondMax == ST[curr].min) ST[curr].secondMax = value;

                ST[curr].sum += (value - ST[curr].min) * ST[curr].frMin;
                ST[curr].min = value;
            }
        }
    }

    void updateNodeMIN(int curr, T value){
        if(value < ST[curr].max){
            if(ST[curr].max == ST[curr].min){
                updateNodeEQUAL(curr, value);
            }
            else {
                if(ST[curr].secondMin == ST[curr].max) ST[curr].secondMin = value;

                ST[curr].sum -= (ST[curr].max - value) * ST[curr].frMax;
                ST[curr].max = value;
            }
        }
    }

    void updateNodePLUS(int curr, T value){
        ST[curr].max += value;
        if(ST[curr].secondMax != -INF) ST[curr].secondMax += value;

        ST[curr].min += value;
        if(ST[curr].secondMin != INF) ST[curr].secondMin += value;

        ST[curr].sum += (ST[curr].r - ST[curr].l + 1) * value;
        ST[curr].lazySUM += value;
    }

    void pushToChildren(int curr){

        if(ST[curr].lazyEQUAL != neutro_lazy_equal){
            updateNodeEQUAL(2*curr, ST[curr].lazyEQUAL);
            updateNodeEQUAL(2*curr+1, ST[curr].lazyEQUAL);
            ST[curr].lazyEQUAL = neutro_lazy_equal;
        }
        
        if(ST[curr].lazySUM != neutro_lazy_sum){
            updateNodePLUS(2*curr, ST[curr].lazySUM);
            updateNodePLUS(2*curr+1, ST[curr].lazySUM);
            ST[curr].lazySUM = neutro_lazy_sum;
        }

        // Lazy is just ask if father is max than us or not
        updateNodeMIN(2*curr, ST[curr].max);
        updateNodeMIN(2*curr+1, ST[curr].max);

        updateNodeMAX(2*curr, ST[curr].min);
        updateNodeMAX(2*curr+1, ST[curr].min);
    }

    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].sum = ST[2 * curr].sum + ST[2 * curr + 1].sum; 

        // Mantain max and second max and frMax
        ST[curr].max = max(ST[2 * curr].max, ST[2 * curr + 1].max);
        ST[curr].secondMax = max(ST[2*curr].secondMax, ST[2*curr+1].secondMax);
        ST[curr].frMax = 0;

        if(ST[curr].max == ST[2*curr].max){
            ST[curr].frMax += ST[2*curr].frMax;
        } else {
            ST[curr].secondMax = max(ST[curr].secondMax, ST[2*curr].max);
        }
        if(ST[curr].max == ST[2*curr+1].max){
            ST[curr].frMax += ST[2*curr+1].frMax;
        } else {
            ST[curr].secondMax = max(ST[curr].secondMax, ST[2*curr+1].max);
        }

        // Maintain min and second min and frMIN
        ST[curr].min = min(ST[2 * curr].min, ST[2 * curr + 1].min);
        ST[curr].secondMin = min(ST[2*curr].secondMin, ST[2*curr+1].secondMin);
        ST[curr].frMin = 0;

        if(ST[curr].min == ST[2*curr].min){
            ST[curr].frMin += ST[2*curr].frMin;
        } else {
            ST[curr].secondMin = min(ST[curr].secondMin, ST[2*curr].min);
        }
        if(ST[curr].min == ST[2*curr+1].min){
            ST[curr].frMin += ST[2*curr+1].frMin;
        } else {
            ST[curr].secondMin = min(ST[curr].secondMin, ST[2*curr+1].min);
        }
    }

    bool breakCondition(int curr, int type_query, T value){
        switch (type_query) {
            case MIN: return ST[curr].max < value;
            case MAX: return ST[curr].min > value;
            // case EQUAL: return false; // leaves same
        }
        return false;
    }

    bool tagCondition(int curr, int type_query, T value){
        switch (type_query) {
            case MIN: return ST[curr].secondMax < value;
            case MAX: return ST[curr].secondMin > value;
            // case EQUAL: return true; // leaves same
        }
        return true;
    }
    
    //* UPDATES *//
    // MIN
    void updateMIN(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, MIN, value)) return;
        else if(ql <= l && r <= qr && tagCondition(curr, MIN, value)){
            updateNodeMIN(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateMIN(2*curr, l, mid, ql, qr, value);
        updateMIN(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateMIN(int ql, int qr, T value){
        updateMIN(1, 1, N, ql, qr, value);
    }

    //MAX
    void updateMAX(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, MAX, value)) return;
        else if(ql <= l && r <= qr && tagCondition(curr, MAX, value)){
            updateNodeMAX(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateMAX(2*curr, l, mid, ql, qr, value);
        updateMAX(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateMAX(int ql, int qr, T value){
        updateMAX(1, 1, N, ql, qr, value);
    }

    // PlUS 
    void updatePLUS(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql || breakCondition(curr, PLUS, value)) return;
        else if(ql <= l && r <= qr && tagCondition(curr, PLUS, value)){
            updateNodePLUS(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updatePLUS(2*curr, l, mid, ql, qr, value);
        updatePLUS(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updatePLUS(int ql, int qr, T value){
        updatePLUS(1, 1, N, ql, qr, value);
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
    cout << "max: " << ST[curr].max  << ", sum: " << ST[curr].sum << " , frMax: " << ST[curr].frMax << " , secondMax: " << ST[curr].secondMax << ", min: " << ST[curr].min << ", secondMin: " << ST[curr].secondMin; 
    cout << ", frMin: " << ST[curr].frMin << ", lazySum: " << ST[curr].lazySUM << endl;;
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