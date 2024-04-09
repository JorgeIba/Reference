// 15
template <typename T> int LIS(const vector<T> &a) {
  vector<T> u;
  for (auto T &x : a) {
    auto it = lower_bound(all(u), x);
    if (it == u.end()) {
      u.push_back(x);
    } else {
      *it = x;
    }
  }
  return int(u.size());
}

// 15
typedef vector<lli> VLL;
typedef vector<int> VI;
int CeilIndex(VLL &nums, VI &tail, lli buscar, int r) {
  int l = 0, res = 0;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    if (buscar <= nums[tail[mid]])
      res = mid, r = mid - 1;
    else
      l = mid + 1;
  }
  return res;
}

// 23
VLL LIS(VLL &nums) {
  int n = SZ(nums), last = 0;
  VI tail(n, 0), prev(n, -1);

  for (int i = 1; i < n; i++) {
    if (nums[i] <= nums[tail[0]]) // Strictly? <
      tail[0] = i;
    else if (nums[i] >= nums[tail[last]]) // Strictly? <
      prev[i] = tail[last], tail[++last] = i;
    else {
      int index = CeilIndex(nums, tail, nums[i], last);
      prev[i] = tail[index - 1];
      tail[index] = i;
    }
  }
  VLL ans;
  for (int i = tail[last]; i != -1; i = prev[i])
    ans.push_back(nums[i]);
  reverse(all(ans));
  return ans;
}