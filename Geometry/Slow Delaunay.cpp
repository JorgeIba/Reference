/*
    Works in O(n^4)
    Does not handle degenerate cases
    Obtained and adapted from:
   https://cs.stanford.edu/group/acm/oldsite/SLPC/notebook.pdf
*/

vector<vector<point>> delaunay(const vector<point> &p) {
  int n = SZ(p);
  vector<ld> z(n);
  vector<vector<point>> ret;
  for (int i = 0; i < n; i++)
    z[i] = p[i].norm();
  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = i + 1; k < n; k++) {
        if (j == k)
          continue;
        ld xn = (p[j].y - p[i].y) * (z[k] - z[i]) -
                (p[k].y - p[i].y) * (z[j] - z[i]);
        ld yn = (p[k].x - p[i].x) * (z[j] - z[i]) -
                (p[j].x - p[i].x) * (z[k] - z[i]);
        ld zn = (p[j].x - p[i].x) * (p[k].y - p[i].y) -
                (p[k].x - p[i].x) * (p[j].y - p[i].y);
        bool flag = zn < 0;
        for (int m = 0; flag && m < n; m++)
          flag = flag && ((p[m].x - p[i].x) * xn + (p[m].y - p[i].y) * yn +
                              (z[m] - z[i]) * zn <=
                          0);

        if (flag)
          ret.push_back({p[i], p[j], p[k]});
      }
    }
  }
  return ret;
}