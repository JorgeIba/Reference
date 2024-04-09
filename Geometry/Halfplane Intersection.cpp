// Source: https://github.com/mhunicken/icpc-team-notebook-el-vasito
// Lo adapto luego
// Counterclockwise (creo)

#define all(v) v.begin(), v.end()
#define forr(i, a, b) for (int i = a; i < b; i++)
#define pb push_back

const ld EPS = 1e-9, INF = 1e9;

struct point {
  ld x, y;
  point(ld x, ld y) : x(x), y(y) {}
  point() {}
  ld norm2() { return *this * *this; }
  ld norm() { return sqrt(norm2()); }
  bool operator==(point p) {
    return abs(x - p.x) <= EPS && abs(y - p.y) <= EPS;
  }
  point operator+(point p) { return point(x + p.x, y + p.y); }
  point operator-(point p) { return point(x - p.x, y - p.y); }
  point operator*(ld t) { return point(x * t, y * t); }
  point operator/(ld t) { return point(x / t, y / t); }
  ld operator*(point p) { return x * p.x + y * p.y; }

  point unit() { return *this / norm(); }
  ld operator%(const point &p) const { return x * p.y - y * p.x; }
};

struct ln {
  point p, pq;
  ln(point p, point q) : p(p), pq(q - p) {}
  ln() {}

  bool operator/(ln l) { return abs(pq.unit() % l.pq.unit()) <= EPS; }

  point operator^(ln l) { // intersection
    if (*this / l)
      return point(INF, INF);
    point r = l.p + l.pq * ((p - l.p) % pq / (l.pq % pq));
    return r;
  }
};

// polygon intersecting left side of halfplanes
struct halfplane : public ln {
  ld angle;
  halfplane() {}
  halfplane(point a, point b) {
    p = a;
    pq = b - a;
    angle = atan2(pq.y, pq.x);
  }
  bool operator<(halfplane b) const { return angle < b.angle; }
  bool out(point q) { return pq % (q - p) < -EPS; }
};
vector<point> intersect(vector<halfplane> b) {
  vector<point> bx = {{INF, INF}, {-INF, INF}, {-INF, -INF}, {INF, -INF}};

  forr(i, 0, 4) b.pb(halfplane(bx[i], bx[(i + 1) % 4]));
  sort(all(b));

  int n = SZ(b), q = 1, h = 0;
  vector<halfplane> c(SZ(b) + 10);
  forr(i, 0, n) {
    while (q < h && b[i].out(c[h] ^ c[h - 1]))
      h--;
    while (q < h && b[i].out(c[q] ^ c[q + 1]))
      q++;
    c[++h] = b[i];
    if (q < h && abs(c[h].pq % c[h - 1].pq) < EPS) {
      if (c[h].pq * c[h - 1].pq <= 0)
        return {};
      h--;
      if (b[i].out(c[h].p))
        c[h] = b[i];
    }
  }
  while (q < h - 1 && c[q].out(c[h] ^ c[h - 1]))
    h--;
  while (q < h - 1 && c[h].out(c[q] ^ c[q + 1]))
    q++;
  if (h - q <= 1)
    return {};
  c[h + 1] = c[q];
  vector<point> s;
  forr(i, q, h + 1) s.pb(c[i] ^ c[i + 1]);
  return s;
}