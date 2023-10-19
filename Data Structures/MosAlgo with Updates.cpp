
// O(BLOCK * Q + Q * (N/BLOCK)^2)
// Function is minimum When BLOCK = (2*N)^(2/3)
// O(Q * N^(2/3)) ~ 2e8 for Q,N <= 10^5
// t -> how many updates before the query
struct Query {
    const static int BLOCK = 3420;
    int l, r, k, t, indx;
    bool operator<(const Query &q) const {
        if (l / BLOCK != q.l / BLOCK)
            return l / BLOCK < q.l / BLOCK;
        if (r / BLOCK != q.r / BLOCK)
            return r / BLOCK < q.r / BLOCK;
        return t < q.t;
    }
};

struct Update {
    int pos, oldVal, newVal;
};

void insert(int left, int num, int right) {
    nextt[left] = num;
    prevv[num] = left;
    nextt[num] = right;
    prevv[right] = num;
}

void erase(int left, int num, int right) {
    nextt[left] = right;
    prevv[right] = left;

    prevv[num] = 0;
    nextt[num] = MAXN;
}

void add(int i) {
    int val = nums[i];

    int old_frq = frq[val];
    int new_frq = ++frq[val];

    cnt[new_frq]++;
    if (cnt[new_frq] == 1) {
        insert(old_frq, new_frq, nextt[old_frq]);
    }

    cnt[old_frq]--;
    if (cnt[old_frq] == 0) {
        erase(prevv[old_frq], old_frq, nextt[old_frq]);
    }
}

void remove(int i) {
    int val = nums[i];

    int old_frq = frq[val];
    int new_frq = --frq[val];

    cnt[new_frq]++;
    if (cnt[new_frq] == 1) {
        insert(prevv[old_frq], new_frq, old_frq);
    }

    cnt[old_frq]--;
    if (cnt[old_frq] == 0) {
        erase(prevv[old_frq], old_frq, nextt[old_frq]);
    }
}

void doUpdate(const Update &U, int l, int r) {
    auto [idx, oldVal, newVal] = U;
    bool inside = l <= idx && idx <= r;
    assert(nums[idx] == oldVal);

    if (inside)
        remove(idx);

    nums[idx] = newVal;

    if (inside)
        add(idx);
}

void undoUpdate(const Update &U, int l, int r) {
    auto [idx, oldVal, newVal] = U;
    bool inside = l <= idx && idx <= r;
    assert(nums[idx] == newVal);

    if (inside)
        remove(idx);

    nums[idx] = oldVal;

    if (inside)
        add(idx);
}

int getAns(int k) {
    int l = nextt[0], r = 0;
    int acum = 0;
    int ans = MAXN;

    while (r < MAXN) {
        while (acum < k && nextt[r] != MAXN) {
            r = nextt[r];
            acum += cnt[r];
        }

        if (acum >= k) {
            ans = min(ans, r - l);
        }
        acum -= cnt[l];
        l = nextt[l];
        if (l > r)
            r = nextt[r];
    }

    return ans == MAXN ? -1 : ans;
}

// Be careful of return type
vector<int> mosAlgo(vector<Query> Q, const vector<Update> &U) {
    int n = SZ(Q);
    vector<int> ans(n);
    sort(all(Q));
    int L = 0; // If 1-indexed L = 1, R = 0
    int R = -1;
    int timeU = 0;
    for (int i = 0; i < n; i++) {
        Query q = Q[i];

        while (L > q.l)
            add(--L);
        while (R < q.r)
            add(++R);

        while (L < q.l)
            remove(L++);
        while (R > q.r)
            remove(R--);

        while (timeU < q.t) {
            doUpdate(U[timeU], q.l, q.r);
            timeU++;
        }

        while (timeU > q.t) {
            timeU--;
            undoUpdate(U[timeU], q.l, q.r);
        }

        ans[q.indx] = getAns(q.k);
    }
    return ans;
}