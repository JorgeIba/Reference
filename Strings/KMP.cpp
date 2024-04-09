vector<int> preffix_function(string &patt) {
    int length = patt.size();
    vector<int> lps(length, 0);
    int j = 0;
    for (int i = 1; i < length; i++) {
        j = lps[i - 1];
        while (j > 0 && patt[i] != patt[j])
            j = lps[j - 1];
        lps[i] = j + (patt[i] == patt[j]);
    }
    return lps;
}
vector<int> kmp(string text, string pattern) {
    vector<int> indexes;
    int j = 0;
    vector<int> lps = preffix_function(pattern);
    for (int i = 0; i < text.size(); i++) {
        while (j > 0 && pattern[j] != text[i])
            j = lps[j - 1];
        if (text[i] == pattern[j]) {
            j++;
            if (j == pattern.size()) {
                indexes.push_back(i - j + 1);
                j = lps[j - 1];
            }
        }
    }
    return indexes;
}
/*
 * Returns an array of size |s| + 1, the i-th position of this array conains
 * the number of occurrences of preffix s[1,...,i] in the string s (1-based).
 * Position 0 doesn't contain relevant information.
 */
vector<int> number_of_occ_preff(string s) {
    vector<int> pi = preffix_function(s);
    int len = s.size();
    vector<int> ans(len + 1);
    for (int i = 0; i < len; i++)
        ans[pi[i]]++;
    for (int i = len - 1; i > 0; i--)
        ans[pi[i - 1]] += ans[i];
    for (int i = 0; i <= len; i++)
        ans[i]++;
    return ans;
}
int length_of_min_compression(string s) {
    vector<int> pi = preffix_function(s);
    int n = s.size();
    int k = n - pi[n - 1];
    if (n % k == 0)
        return k;
    return n;
}
void compute_automaton(string s, vector<vector<int>> &aut) {
    s += '#';
    int n = s.size();
    vector<int> pi = prefix_function(s);
    aut.assign(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i - 1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}
