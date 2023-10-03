struct Data {
    int p, u, a, b, inc, isp;
};
stack<Data> save;
int cp;

void init() {
    while (save.size())
        save.pop();
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        f[i] = 0;
        rk[i] = 0;
    }
    cp = 0;
}

ii parent(int a) {
    int c = 0;
    while (a != p[a]) {
        c ^= f[a];
        a = p[a];
    }
    return {a, c};
}

bool join(int a, int b, int g) {
    ii pa = parent(a), pb = parent(b);

    if (pa.fi == pb.fi) {
        if (pa.se == pb.se)
            return 0;

        save.push({pa.fi, pb.fi, a, b, 0, g});
        cp += g;
        return 1;
    }

    if (rk[pa.fi] < rk[pb.fi])
        swap(pa, pb);

    save.push({pa.fi, pb.fi, a, b, rk[pa.fi] == rk[pb.fi], g});
    cp += g;

    p[pb.fi] = pa.fi;
    f[pb.fi] = 1 ^ pa.se ^ pb.se;
    rk[pa.fi] += rk[pa.fi] == rk[pb.fi];

    return 1;
}

ii pop(const Data &d) {
    cp -= d.isp;
    p[d.u] = d.u;
    f[d.u] = 0;
    rk[d.p] -= d.inc;
    return {d.a, d.b};
}

void pop() {
    vii a, b;

    if (!cp) {
        while (save.size()) {
            a.pb(pop(save.top()));
            save.pop();
        }
    } else if (!save.top().isp) {
        do {
            if (save.top().isp)
                a.pb(pop(save.top()));
            else
                b.pb(pop(save.top()));
            save.pop();
        } while (cp && a.size() != b.size());

        reverse(all(a));
        reverse(all(b));
    }

    for (ii &p : b)
        join(p.fi, p.se, 0);
    for (ii &p : a)
        join(p.fi, p.se, 1);

    pop(save.top());
    save.pop();
}
