// requires lli = __int128, otherwise change the values of MOD, P ans PI
// (inverse of P)
struct Hash {
  lli MOD = 212345678987654321LL, P = 1777771, PI = 106955741089659571LL;
  // lli MOD = 1e9 + 7, P = 31, PI = 129032259ll; // For lowercase english
  // letters lli MOD = 1e9 + 7, P = 53, PI = 56603774ll; // For
  // lower/uppercase english letters lli MOD = 1824261409, P = 53, PI =
  // 1411221090;
  vector<lli> h, pi;
  Hash(string &s) {
    assert((P * PI) % MOD == 1);
    h.resize(s.size() + 1);
    pi.resize(s.size() + 1);
    h[0] = 0;
    pi[0] = 1;
    lli p = 1;
    forr(i, 1, s.size()) {
      h[i] = (h[i - 1] + p * s[i - 1] % MOD) % MOD;
      pi[i] = pi[i - 1] * PI % MOD;
      p = p * P % MOD;
    }
  }
  // returns the hash of substring [s,e)
  lli get(int s, int e) { return ((h[e] - h[s] + MOD) % MOD) * pi[s] % MOD; }
};
;
