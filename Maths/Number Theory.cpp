vector<lli> getDivs(vector<pair<lli, lli>> &factors) {
  int n = SZ(factors);
  int factors_count = 1;
  for (int i = 0; i < n; ++i) {
    factors_count *= 1 + factors[i].second;
  }
  vector<lli> divs(factors_count);
  divs[0] = 1;
  int count = 1;
  for (int stack_level = 0; stack_level < n; ++stack_level) {
    int count_so_far = count;
    lli prime = factors[stack_level].first;
    int exponent = factors[stack_level].second;
    lli multiplier = 1;
    for (int j = 0; j < exponent; ++j) {
      multiplier *= prime;
      for (int i = 0; i < count_so_far; ++i) {
        divs[count++] = divs[i] * multiplier;
      }
    }
  }
  return divs;
}

// Discrete Logarithm p prime
// Solves for lowest n in the equation a^n = b mod p prime
// n = x*m - y, a^xm = ba^y
lli discreteLogarithm(lli a, lli b, lli p) {
  if (a == 0) { // Do something depending on problem
  }

  lli m = sqrt(p) + 1;

  unordered_map<lli, lli> rhs;
  lli b_ay = b;
  for (int y = 0; y <= m; y++) {
    rhs[b_ay] = y;
    b_ay = b_ay * a % p;
  }

  lli a_m =
      powerMod(a, m, p); // You can brute force this, complexity is the same
  lli a_xm = a_m;
  for (int x = 1; x <= m; x++) {
    if (rhs[a_xm]) {
      return x * m - rhs[a_xm]; // lowest solution
    }
    a_xm = a_xm * a_m % p;
  }

  return -1; // solution not found
}

// Discrete Logarithm p prime
// Solves for lowest n in the equation a^n = b mod m  not necessarily prime
// n = x*m - y, a^xm = ba^y
lli discreteLogarithm(lli a, lli b, lli mod) {
  if (a == 0) {
    // Depending on problem
    if (b != 0)
      return -1;
    return 1;
  }

  lli g, offset = 0, k = 1;
  while ((g = gcd(a, mod)) > 1) {

    // k*a^(x-add) = k -> (n-offset) = 0
    if (b == k)
      return offset;

    if (b % g != 0)
      return -1;

    b /= g;
    mod /= g;
    offset++;

    k = k * (a / g) % mod;
  }

  a %= mod;
  b %= mod;

  // Here we have k * a^(n-offset) = b mod m,
  // gcd(a,m) = 1
  // Lets solve for k*a^x = b mod m

  lli m = sqrt(mod) + 1;

  unordered_map<lli, lli> rhs;
  lli b_ay = b;
  for (int y = 0; y <= m; y++) {
    rhs[b_ay] = y;
    b_ay = b_ay * a % mod;
  }

  lli a_m = powerMod(a, m, mod);
  lli k_axm = k * a_m % mod;
  for (int x = 1; x <= m; x++) {
    if (rhs.count(k_axm)) {
      return offset + (m * x - rhs[k_axm]);
    }
    k_axm = k_axm * a_m % mod;
  }

  return -1;
}

// Need miu and lowestPrime and getDivs O(log(n) + numDivs(distinctPrimes(n)))
lli coprimesInRange(lli n, lli L, lli R) {
  vector<pair<lli, lli>> factors;

  while (n > 1) {
    lli lowestPrime = lp[n];
    factors.push_back({lowestPrime, 1});
    while (n % lowestPrime == 0)
      n /= lowestPrime;
  }

  lli ans = 0;

  auto divs = getDivs(factors);
  for (auto d : divs) {
    ans += miu[d] * (R / d - (L - 1) / d);
  }
  return ans;
}
