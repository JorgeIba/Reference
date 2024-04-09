
// Represent numbers of form: a + sqr*b
// a and b integers
template <int sqr = 5, int mod = 1'000'000'000 + 7> struct Ext {
  lli a, b;

  Ext() : a(0), b(0) {}
  Ext(lli a, lli b = 0) : a(a), b(b) {}

  Ext operator*(const Ext &A) const {
    lli new_a = (a * A.a % mod + sqr * b % mod * A.b % mod) % mod;
    lli new_b = (a * A.b % mod + b * A.a % mod) % mod;

    return {new_a, new_b};
  }

  Ext operator+(const Ext &A) const {
    return {(a + A.a) % mod, (b + A.b) % mod};
  }
  Ext operator-(const Ext &A) const {
    return {(a - A.a + mod) % mod, (b - A.b + mod) % mod};
  }
  Ext operator*(const lli k) const { return {a * k % mod, b * k % mod}; }
  bool operator==(const Ext &A) const { return a == A.a && b == A.b; }
  bool operator!=(const Ext &A) const { return !(*this == A); }

  Ext power(lli k) const {
    Ext res = Ext(1, 0);
    for (auto A = *this; k; k >>= 1, A = A * A) {
      if (k & 1)
        res = res * A;
    }
    return res;
  }

  Ext conj() const { return {a, mod - b}; }

  Ext inv() const {
    lli den = a * a % mod - sqr * b % mod * b % mod;
    assert(den != 0);
    if (den < 0)
      den += mod;
    return conj() * powerMod(den, mod - 2, mod);
  }
};