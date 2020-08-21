// 10
typedef long long int lli;

lli binPow(li a, li p) {
  lli ans = 1LL;
  while (p) {
    if (p & 1LL) ans *= a;
    a *= a, p >>= 1LL;
  }
  return ans;
}