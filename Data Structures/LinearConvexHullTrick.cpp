struct Line {
    lli m, b;
};

lli ceil(lli a, lli b) {
    if ((a < 0) != (b < 0))
        return a / b;
    return (abs(a) + abs(b) - 1) / abs(b);
}

lli inter(const Line &p, const Line &q) { return ceil(q.b - p.b, p.m - q.m); }

lli eval(const Line &p, lli x) { return p.m * x + p.b; }

// max
// increasing m in add
// decreasing x in query
struct CHT {
    vector<Line> st;

    void clear() { st.clear(); }

    void add(lli m, lli b) {
        if (st.size() && st.back().m == m) {
            if (st.back().b > b)
                return;
            st.pop_back();
        }

        Line p(m, b);
        while (st.size() > 1 &&
               inter(st.end()[-2], st.end()[-1]) >= inter(st.end()[-1], p)) {
            st.pop_back();
        }

        st.pb(p);
    }

    lli query(lli x) {
        if (st.empty())
            return 0;

        while (st.size() > 1 && eval(st.end()[-2], x) > eval(st.end()[-1], x))
            st.pop_back();

        return eval(st.end()[-1], x);
    }
};
