const lli INF = 1e18;
bool Q = 0;
struct Line {
    mutable lli m, b, x;
    // Maximo: m < ot.m
    // Minimo: m > ot.m
    bool operator<(const Line ot) const { return Q ? x < ot.x : m < ot.m; }
};

lli ceil(lli a, lli b) {
    if ((a < 0) != (b < 0))
        return a / b;
    return (abs(a) + abs(b) - 1) / abs(b);
}
lli intersection(const Line &p, const Line &q) {
    return ceil(q.b - p.b, p.m - q.m);
}

struct Hull : multiset<Line> {
    bool valid(auto it) {
        if (it == begin()) {
            auto sig = it;
            sig++;
            if (sig != end())
                sig->x = intersection(*it, *sig);
            return it->x = -INF;
        }

        auto ant = it, sig = it;
        ant--, sig++;

        if (sig == end()) {
            it->x = intersection(*it, *ant);
            return 1;
        }

        lli x = intersection(*it, *ant);
        lli y = intersection(*it, *sig);

        if (x > y)
            return 0;
        it->x = x, sig->x = y;
        return 1;
    }

    void add(lli m, lli b) {
        auto it = lower_bound({m, b, -INF});

        if (it != end() && it->m == m) {
            // Maximo: it->b > b
            // Minimo: it->b < b
            if (it->b > b)
                return;
            it->b = b;
        } else {
            it = insert({m, b, -INF});
        }

        if (!valid(it)) {
            erase(it);
            return;
        }

        auto ant = it;
        while (ant != begin()) {
            if (valid(--ant))
                break;
            erase(ant);
            if (it == begin()) {
                it->x = -INF;
                break;
            }
            ant = it;
        }

        auto sig = it;
        sig++;
        while (sig != end() && !valid(sig))
            erase(sig++);
    }

    lli query(lli x) {
        if (empty())
            return 0;

        Q = 1;
        auto it = upper_bound({0, 0, x});
        it--;
        Q = 0;
        return x * it->m + it->b;
    }
};

//* Otra Implementación mas corta
struct Line {
    mutable lli k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(lli x) const { return p < x; }
};
// Works for maximum
// If you want minimum, multiply m and b for -1, and
// multiply for -1 the query
struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use INF = 1/.0, div(a,b) = a/b)
    const lli INF = LLONG_MAX;
    lli div(lli a, lli b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = INF;
            return false;
        }
        if (x->k == y->k)
            x->p = x->m > y->m ? INF : -INF;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(lli k, lli m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    lli query(lli x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};