template <typename T, typename S> struct SegmentTreeItLazy { // 0 - indexed
    T neutro = 0, neutro_lazy = 0;
    int size, height;
    vector<T> st, delUp;
    vector<bool> upd;

    // S tipo de dato que recibe
    SegmentTreeItLazy(int n, T val = 0, const vector<S> &v = vector<S>()) {
        st.resize(2 * n);
        if (v.empty())
            fill(all(st), val);
        size = n;
        delUp.resize(n, neutro_lazy);
        upd.resize(n);
        height = sizeof(int) * 8 - __builtin_clz(size);
        if (!v.empty())
            forn(i, n) st[i + size] = set(v[i]);
        build();
    }

    T merge(T a, T b) {
        return a + b;
        // return a * b;
        // return __gcd(a, b);
        // return min(a, b);
    }
    void apply(int i, T val, int k) {
        st[i] += val * k;
        if (i < size)
            delUp[i] += val, upd[i] = 1;
    }
    void calc(int i) {
        if (!upd[i])
            st[i] = merge(st[i << 1], st[i << 1 | 1]);
    }
    void build() {
        for (int i = size - 1; i; i--)
            calc(i);
    }
    void build(int p) {
        while (p > 1)
            p >>= 1, calc(p);
    }
    void push(int p) {
        for (int s = height, k = 1 << (height - 1); s; s--, k >>= 1) {
            int i = p >> s;
            if (upd[i]) {
                apply(i << 1, delUp[i], k);
                apply(i << 1 | 1, delUp[i], k);
                upd[i] = 0, delUp[i] = neutro_lazy;
            }
        }
    }
    void update(int l, int r, T val) {
        push(l += size), push(r += size);
        int ll = l, rr = r, k = 1;
        for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1)
                apply(l++, val, k);
            if (~r & 1)
                apply(r--, val, k);
        }
        build(ll), build(rr);
    }
    T query(int l, int r) {
        T ansL = neutro;
        T ansR = neutro;
        push(l += size);
        push(r += size);
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ansL = merge(ansL, st[l++]);
            if (~r & 1)
                ansR = merge(st[r--], ansR);
        }
        return merge(ansL, ansR);
    }
    T &operator[](int i) {
        push(i + size);
        return st[i + size];
    }
    T set(S x) { return x; }
};
