// vEB tree implementation by mango_lassi
// van Emde Boas tree. Maintains a set of integers in range [0, 2^B) and
// supports operations
//	findNext(i): returns minimum j >= i in set, or 2^B if none exist
// 	findPrev(i): returns maximum j <= i in set, or -1 if none exist
//	insert(i), erase(i): insert/erase i into the set
//	empty(): returns TRUE if the set is empty
//	clear(): empties the set
// All operations except empty and clear are O(log B) = O(log log 2^B) with good
// constants VEBTree<24> sett; sett.clear();
template <int B, typename ENABLE = void> class VEBTree {
private:
  const static int K = B / 2, R = (B + 1) / 2, M = (1 << B);
  const static int S = 1 << K, MASK = (1 << R) - 1;
  VEBTree<R> ch[S];
  VEBTree<K> act;
  int mi, ma;

public:
  bool empty() const { return ma < mi; }

  int findNext(int i) const {
    if (i <= mi)
      return mi;
    if (i > ma)
      return M;

    int j = i >> R, x = i & MASK;
    int res = ch[j].findNext(x);
    if (res <= MASK)
      return (j << R) + res;

    j = act.findNext(j + 1);
    return (j >= S) ? ma : ((j << R) + ch[j].findNext(0));
  }
  int findPrev(int i) const {
    if (i >= ma)
      return ma;
    if (i < mi)
      return -1;

    int j = i >> R, x = i & MASK;
    int res = ch[j].findPrev(x);
    if (res >= 0)
      return (j << R) + res;

    j = act.findPrev(j - 1);
    return (j < 0) ? mi : ((j << R) + ch[j].findPrev(MASK));
  }
  void insert(int i) {
    if (i <= mi) {
      if (i == mi)
        return;
      std::swap(mi, i);
      if (i == M)
        ma = mi; // we were empty
      if (i >= ma)
        return; // we had mi == ma
    } else if (i >= ma) {
      if (i == ma)
        return;
      std::swap(ma, i);
      if (i <= mi)
        return; // we had mi == ma
    }
    int j = i >> R;
    if (ch[j].empty())
      act.insert(j);
    ch[j].insert(i & MASK);
  }
  void erase(int i) {
    if (i <= mi) {
      if (i < mi)
        return;
      i = mi = findNext(mi + 1);
      if (i >= ma) {
        if (i > ma)
          ma = -1; // we had mi == ma
        return;    // after erase we have mi == ma
      }
    } else if (i >= ma) {
      if (i > ma)
        return;
      i = ma = findPrev(ma - 1);
      if (i <= mi)
        return; // after erase we have mi == ma
    }
    int j = i >> R;
    ch[j].erase(i & MASK);
    if (ch[j].empty())
      act.erase(j);
  }

  void clear() {
    mi = M, ma = -1;
    act.clear();
    for (int i = 0; i < S; ++i)
      ch[i].clear();
  }
};
template <int B> class VEBTree<B, typename std::enable_if<(B <= 6)>::type> {
private:
  const static int M = (1 << B);
  ull act;

public:
  bool empty() const { return !act; }
  void clear() { act = 0; }

  int findNext(int i) const {
    if (i == M)
      return M;
    ull tmp = act >> i;
    return (tmp ? i + __builtin_ctzll(tmp) : M);
  }
  int findPrev(int i) const {
    if (i == -1)
      return -1;
    ull tmp = act << (63 - i);
    return (tmp ? i - __builtin_clzll(tmp) : -1);
  }
  void insert(int i) { act |= 1ULL << i; }
  void erase(int i) { act &= ~(1ULL << i); }
};

const int B = 24;
const int MAXA = 1 << B;
VEBTree<24> sett;