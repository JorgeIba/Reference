
typedef int64_t ll;
typedef uint64_t ull;
inline ull multMod(ull a, ull b, ull c) {
  ll ret = a * b - c * ull(1.L / c * a * b);
  return ret + c * (ret < 0) - c * (ret >= (ll)c);
}