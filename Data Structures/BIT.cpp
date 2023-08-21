// 1-indexed
struct Fenwick {
    int n;
    vector<long long> tree;

    Fenwick(int _n): n(_n), tree(n+1, 0) { }

    void update(int idx, long long val) {
        for (; idx <= n ; idx += idx & -idx) {
            tree[idx] += val;
        }
    }

    long long query(int idx) {
        long long ret = 0;
        for(; idx > 0 ; idx -= idx & -idx){
            ret += tree[idx];
        }
        return ret;
    }

    long long query(int x, int y) {
        return query(y) - query(x-1);
    }
};


// query(l, r) -> sum[l, ..., r]
// update(l, r, v)-> sum[l, ..., r] = (a[l]+v) + (a[l+1]+v) + ... + (a[r]+v)
// query - O(log(n))
// update - O(log(n))
// 0-indexed
template<typename T>
struct FenwickTree{
	int n;
    vector< vector<T> > bit;

    FenwickTree(int n): n(n) {
        bit.assign(2, vector<T>(n+1));
    }
    T get(int x, int i) {
        T ret = 0;
        for (; i; i -= i&-i) ret += bit[x][i];
        return ret;
    }
    void add(int x, int i, T val) {
        for (; i <= n; i += i&-i) bit[x][i] += val;
    }
    T get2(int p) {
        return get(0, p) * p + get(1, p);
    }
    T query(int l, int r) {
        return get2(r+1) - get2(l);
    }
    void update(int l, int r, T x) {
        add(0, l+1, x), add(0, r+2, -x);
        add(1, l+1, -x*l), add(1, r+2, x*(r+1));
    }
};