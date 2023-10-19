const lli inf = numeric_limits<lli>::max();
const int dim = 3;

struct Point {
    lli x[dim];
    lli &operator[](int i) { return x[i]; }
};
typedef vector<Point> vp;

// Modificar si se necesita distancia euclidiana.
lli dist(Point &a, Point &b) {
    lli d = 0;
    for (int i = 0; i < dim - 1; i++)
        d += abs(a[i] - b[i]);
    d -= abs(a[i] - b[i]);
    return d ? d : inf;
}

void build(vp &p, int i, int j, int lvl) {
    if (i >= j)
        return;

    int m = (i + j) / 2;
    int cur = lvl % dim;

    nth_element(p.begin() + i, p.begin() + m, p.begin() + j + 1,
                [&](Point &a, Point &b) { return a[cur] < b[cur]; });

    build(p, i, m - 1, lvl + 1);
    build(p, m + 1, j, lvl + 1);
}

lli find_closest(vp &p, Point &x, int i, int j, int lvl) {
    if (i == j)
        return dist(x, p[i]);
    if (i > j)
        return inf;

    int m = (i + j) / 2;
    int cur = lvl % dim;
    lli res;

    if (x[cur] < p[m][cur]) {
        res = find_closest(p, x, i, m - 1, lvl + 1);
        if (res > (x[cur] - p[m][cur]) * (x[cur] - p[m][cur]))
            res = min(res, find_closest(p, x, m + 1, j, lvl + 1));
    } else {
        res = find_closest(p, x, m + 1, j, lvl + 1);
        if (res > (x[cur] - p[m][cur]) * (x[cur] - p[m][cur]))
            res = min(res, find_closest(p, x, i, m - 1, lvl + 1));
    }

    return min(res, dist(x, p[m]));
}

int n;
vp p, aux;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    p.resize(n);

    for (int i = 0; i < n; i++)
        cin >> p[i][0] >> p[i][1];

    aux = p;
    build(aux, 0, n - 1, 0);

    for (int i = 0; i < n; i++)
        cout << find_closest(aux, p[i], 0, n - 1, 0) << endl;

    return 0;
}
