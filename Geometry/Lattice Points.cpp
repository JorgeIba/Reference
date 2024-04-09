// Here is simple function which calculates number of integer points $(x;y)$
// such for $0 \leq x < n$ and $0 < y \leq \lfloor k x+b\rfloor$:
int count_lattices(Fraction k, Fraction b, long long n) {
  auto fk = k.floor();
  auto fb = b.floor();
  auto cnt = 0LL;
  if (k >= 1 || b >= 1) {
    cnt += (fk * (n - 1) + 2 * fb) * n / 2;
    k -= fk;
    b -= fb;
  }
  auto t = k * n + b;
  auto ft = t.floor();
  if (ft >= 1) {
    cnt += count_lattices(1 / k, (t - t.floor()) / k, t.floor());
  }
  return cnt;
}