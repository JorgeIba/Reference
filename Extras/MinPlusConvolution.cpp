/*
    Receives two convex values A,B:
    A[i] - A[i-1] < A[i+1] - A[i] &&
    B[i] - B[i-1] < B[i+1] - B[i]

    And returns a vector C s.t:
    C[k] = min(A[j] + B[k - j])
*/
template<typename T>
vector<T> min_plus_convolution(const vector<T> &A, const vector<T> &B) {
    int n = SZ(A), m = SZ(B);
    vector<T> ans = {A[0] + B[0]};
    int i = 0, j = 0;
    for(int t = 1; t < n + m - 1; t++) {
        if((j+1 == m) || (i+1 < n && A[i+1] - A[i] < B[j+1] - B[j])) {
            ans.push_back(A[++i] + B[j]);
        } else {
            ans.push_back(A[i] + B[++j]);
        }
    }
    return ans;
}

/*
    This code is to remember you can mantain de slopes and combine is just 
    a merge sort, so you can do small to large with multiset.
*/
template<typename T>
vector<T> min_plus_convolution_diff(const vector<T> &A, const vector<T> &B) {
    int n = SZ(A), m = SZ(B);
    multiset<T> dA, dB;
    for(int i = 1; i < n; i++)
        dA.insert(A[i] - A[i-1]);

    for(int i = 1; i < m; i++)
        dB.insert(B[i] - B[i-1]);
    
    if(SZ(dA) < SZ(dB))
        swap(dA, dB);

    for(auto x: dB)
        dA.insert(x);

    vector<T> ans = {A[0] + B[0]};
    ans.insert(ans.end(), all(dA));
    partial_sum(all(ans), ans.begin());

    return ans;
}


// With one of the arrays arbitrary:
// Taken from https://judge.yosupo.jp/submission/183704

template<typename F>
vector<int> MonotoneMinima(int R, int C, F cmp){
    vector<int> ret(R);
    auto rec=[&](auto &f, vector<int> target)-> void {
        int m = target.size();
        if(m == 0)return;
        vector<int> even;
        for(int i=1; i < m; i += 2) even.push_back(target[i]);
        f(f,even);
        int cur=0;
        for(int i=0; i < m; i += 2){
            ret[target[i]]=cur;
            int end= C - 1;
            if(i != m - 1)
                end = ret[ even[ i / 2 ] ];
            while(cur < end){
                cur++;
                if(cmp(target[i],ret[target[i]],cur))
                    ret[target[i]] = cur;
            }
        }
    };
    vector<int> tmp(R);
    iota(all(tmp),0);
    rec(rec,tmp);
    return ret;
}

template <typename T>
vector<T> MinPlusConvolution_arbitrary_convex(vector<T> &a, vector<T> &b) {
    int n = a.size(), m = b.size();
    auto cmp = [&](int i, int j, int k) -> bool {
        if (i < k)
            return false;
        if (i - j >= m)
            return true;
        return a[j] + b[i - j] >= a[k] + b[i - k];
    };
    auto arg = MonotoneMinima(n + m - 1, n, cmp);
    vector<lli> ret(n + m - 1);
    forn(i, n + m - 1) ret[i] = a[arg[i]] + b[i - arg[i]];
    return ret;
}

// Taken from https://judge.yosupo.jp/submission/244637

// A is concave
template<typename T>
vector<T> MinPlusConvolution_arbitrary_concave(vector<T>& a,vector<T>& b){
    int n = SZ(a), m = SZ(b);
    vector<T> c(n + m - 1, numeric_limits<T>::max() );

    auto rec= [&](auto& rec,int x1,int y1,int x2,int y2) -> void {
        if(x1 == x2 || y1 == y2)return;
        if((x2 - 1) < y1 || x1 - (y2 - 1) >= n)return;
        
        if(x1 >= (y2 - 1) && (x2 - 1) - y1 <n){
            auto get= [&](int x,int y) -> T {
                int i = x + x1;
                int j = y2 - 1 - y;
                return a[i-j] + b[j];
            };
            auto cmp=[&](int i,int j,int k) -> bool {
                return get(i,j) > get(i,k);
            };
            vector<int> pos = MonotoneMinima(x2-x1, y2-y1, cmp);
            forn(x, x2 - x1){
                int i= x + x1;
                int j= y2 - 1 - pos[x];
                assert(x1 <= i and i < x2);
                assert(y1 <= j and j < y2);

                c[i] = min(c[i], a[i-j] + b[j]);
            }
            return;
        }
        
        if(x2 - x1 >= y2 - y1){
            int mid = (x1 + x2) >> 1;
            rec(rec, x1, y1, mid, y2);
            rec(rec, mid, y1, x2, y2);
        }
        else{
            int mid = (y1 + y2) >> 1;
            rec(rec, x1, y1, x2, mid);
            rec(rec, x1, mid, x2, y2);
        }
    };
    rec(rec, 0, 0, n + m - 1, m);
    return c;
}

