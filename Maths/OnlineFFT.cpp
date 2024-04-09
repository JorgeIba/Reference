#define forr(i, a, b) for (int i = int(a); i <= int(b); i++)

vi operator*(vi A, vi B) {
  int sz = A.size() + B.size() - 1;
  int size = nearestPowerTwo(sz);
  A.resize(size), B.resize(size);

  ntt(A, 1), ntt(B, 1);
  for (int i = 0; i < size; i++)
    A[i] = 1ll * A[i] * B[i] % mod;
  ntt(A, -1);

  A.resize(sz);
  return A;
}

int n;
vi P;

// Solve recurrence P[n]=a(n)*sum_(1 <= i <= n - 1){b(i)P[i] * c(n - i)P[n - i]}
// for l <= n <= r Where b(i) and c(i) may depend on P[i] Given base case P[1]
// (the code can be modified to add more case bases) Complexity O(n*log^2(n))

lli a(int i) {}
lli b(int i) {}
lli c(int i) {}

void online_fft(int l, int r) {
  if (l == r) {
    P[l] = a(l) * P[l] % mod;
    return;
  }

  int m = (l + r) / 2;
  online_fft(l, m);

  vi B, C;
  forr(i, l, m) B.pb(b(i));
  forr(i, 1, r - l) C.pb(c(i));
  vi D = B * C;
  forr(i, m + 1, r)(P[i] += D[i - l - 1]) %= mod;

  if (l != 1) {
    B.clear(), C.clear();
    forr(i, 1, r - l) B.pb(b(i));
    forr(i, l, m) C.pb(c(i));
    D = B * C;
    forr(i, m + 1, r)(P[i] += D[i - l - 1]) %= mod;
  }

  online_fft(m + 1, r);
}
