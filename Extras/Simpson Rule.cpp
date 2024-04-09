ld simpson_rule(ld a, ld b, int n = 1e5) {
  ld h = (b - a) / n;

  ld sum_odds = 0.0;
  for (int i = 1; i < n; i += 2)
    sum_odds += f(a + i * h);

  ld sum_evens = 0.0;
  for (int i = 2; i < n; i += 2)
    sum_evens += f(a + i * h);

  return (f(a) + f(b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
}