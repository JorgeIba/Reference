#include <bits/stdc++.h>
#define lli long long int
using namespace std;

struct state {
  int len, link;
  map<int, int> child;
  state(int len = 0, int link = -1) : len(len), link(link) {}
  state(int len, int link, map<int, int> child)
      : len(len), link(link), child(child) {}
};

struct SuffixAutomaton {
  vector<state> st;
  int last = 0;

  // It's used to store info about the automaton, for example, the number of
  // paths that pass through a node, which can be used to get the number of
  // different strings
  vector<lli> dp;

  SuffixAutomaton() { st.emplace_back(); }

  void extend(char c) {
    int curr = st.size(), p;
    st.emplace_back(st[last].len + 1);
    for (p = last; p != -1 && !st[p].child.count(c); p = st[p].link)
      st[p].child[c] = curr;

    if (p == -1)
      st[curr].link = 0;
    else {
      int q = st[p].child[c];
      if (st[p].len + 1 == st[q].len)
        st[curr].link = q;
      else {
        int w = st.size();
        st.emplace_back(st[p].len + 1, st[q].link, st[q].child);
        for (; p != -1 && st[p].child[c] == q; p = st[p].link)
          st[p].child[c] = w;
        st[q].link = st[curr].link = w;
      }
    }
    last = curr;
  }
};

int main() {
  string s;
  cin >> s;
  SuffixAutomaton sa;
  for (char c : s)
    sa.extend(c);
  return 0;
}
