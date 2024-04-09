// It computes nCr mod p^k
// Precomputation: O(p^k)
// Query: O(log(n))
// Requires inverse modular function
struct BinomialPrimePower {
  lli p, k;
  lli pk;
  vector<lli> fact_p;
  vector<lli> powers_p;

  BinomialPrimePower() {}
  BinomialPrimePower(lli p, lli k) : p(p), k(k) {
    pk = pow(p, k);
    fact_p.resize(pk, 1);

    for (int i = 2; i < pk; ++i) {
      if (i % p == 0)
        fact_p[i] = fact_p[i - 1];
      else
        fact_p[i] = 1LL * i * fact_p[i - 1] % pk;
    }

    int max_alpha = 100; // Maximum exponent of p in n
    powers_p.resize(max_alpha, 1);
    for (int i = 1; i < max_alpha; i++) {
      powers_p[i] = 1LL * p * powers_p[i - 1] % pk;
    }
  }

  // n! = a x p^k where gcd(n!,a) = 1
  // returns [a % pk, k]
  pair<lli, lli> fact_n(lli n) {
    if (n == 0 || n == 1)
      return {1, 0};

    lli fact_pk;
    if (p > 2 || pk == 4) { // fact_pk = pk-1;
      if (n / pk % 2 == 0)
        fact_pk = 1;
      else
        fact_pk = pk - 1;
    } else {
      fact_pk = 1;
    }

    lli alpha_1 = n / p;
    lli a_1 = fact_pk * fact_p[n % pk] % pk;

    auto [a_2, alpha_2] = fact_n(n / p);
    return {a_1 * a_2 % pk, alpha_1 + alpha_2};
  }

  lli nCr(lli n, lli r) {
    if (n < 0 || r < 0 || r > n)
      return 0;

    auto [a_n, alpha_n] = fact_n(n);
    auto [a_r, alpha_r] = fact_n(r);
    auto [a_nr, alpha_nr] = fact_n(n - r);

    int power = alpha_n - alpha_r - alpha_nr;
    if (power >= k)
      return 0;

    return a_n * inverse(a_r, pk) % pk * inverse(a_nr, pk) % pk *
           powers_p[power] % pk;
  }
};

// Faster iterative version
// Precomputation O(p^k)
// Query O(log_p(n))
// Based on
// https://people.math.rochester.edu/faculty/doug/otherpapers/granville.pdf
struct BinomialPrimePower {
  int p, k;
  int pk;
  vector<int> fact_p, inv_fact_p;

  BinomialPrimePower() {}
  BinomialPrimePower(lli p, lli k_) : p(p), k(k_) {
    pk = 1;
    while (k_--)
      pk *= p;

    fact_p.resize(pk, 1);
    for (int i = 2; i < pk; ++i) {
      if (i % p == 0)
        fact_p[i] = fact_p[i - 1];
      else
        fact_p[i] = 1LL * i * fact_p[i - 1] % pk;
    }

    inv_fact_p.resize(pk, 1);
    inv_fact_p[pk - 1] = inverse(fact_p.back(), pk);
    for (int i = pk - 2; i > 1; i--) {
      if ((i + 1) % p == 0)
        inv_fact_p[i] = inv_fact_p[i + 1];
      else
        inv_fact_p[i] = 1LL * inv_fact_p[i + 1] * (i + 1) % pk;
    }
  }

  int nCr(lli n, lli r) {
    if (n < 0 || r < 0 || r > n)
      return 0;

    lli nr = n - r;
    lli ans = 1;
    int e_0 = 0, e_q = 0;
    for (int i = 1; n; i++) {
      ans = ans * fact_p[n % pk] % pk;
      ans = ans * inv_fact_p[r % pk] % pk;
      ans = ans * inv_fact_p[nr % pk] % pk;

      n /= p, r /= p, nr /= p;

      int exp = n - r - nr;

      e_0 += exp;
      if (e_0 >= k)
        return 0;
      if (i >= k)
        e_q += exp;
    }

    if (!(p == 2 and k >= 3) and (e_q & 1))
      ans = pk - ans;

    ans = ans * powerMod(p, e_0, pk) % pk;
    return ans;
  }
};