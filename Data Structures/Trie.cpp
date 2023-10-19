struct TrieNode {
    map<char, TrieNode *> dictionary;
    int howMuchWords = 0;
    int isWord = 0;
};

struct Trie {
    TrieNode *root = new TrieNode;

    bool exist(TrieNode *curr, char c) { return curr->dictionary.count(c); }

    void insert(const string &s) {
        TrieNode *curr = root;
        curr->howMuchWords++;
        for (auto c : s) {
            if (!exist(curr, c))
                curr->dictionary[c] = new TrieNode();
            curr = curr->dictionary[c];
            curr->howMuchWords++;
        }
        curr->isWord++;
    }

    lli search(const string &word) {
        TrieNode *curr = root;
        lli ans = -1;
        for (auto c : word) {
            if (!exist(curr, c)) {
                return 0;
            }
            curr = curr->dictionary[c];
            ans = curr->howMuchWords;
        }
        return ans;
    }

    // Assume word exists
    void remove(TrieNode *curr, const string &word, int idx = 0) {
        curr->howMuchWords--;

        if (idx == SZ(word)) {
            curr->isWord--;
            return;
        }

        auto c = word[idx];
        auto next = curr->dictionary[c];
        remove(next, word, idx + 1);

        if (!next->howMuchWords) {
            delete (next);
            next = NULL;
            curr->dictionary.erase(c);
        }
    }

    void Rec(TrieNode *root, const string &s) {
        for (auto c : root->dictionary) {
            string aux = s;
            aux.push_back(c.first);
            Rec(c.second, aux);
        }
        if (root->isWord)
            cout << s << endl;
    }

    void printWords() {
        string aux;
        Rec(root, aux);
    }
};

// BINARY
const int maxLOG = 31;

struct TrieNode {
    TrieNode *dict[2] = {NULL, NULL};
    int howMuchWords = 0;
    int isWord = 0;
};

struct Trie {
    TrieNode *root = new TrieNode;

    bool exist(TrieNode *curr, int c) { return curr->dict[c] != NULL; }

    // s = bitset.to_string
    void insert(const string &s) {
        TrieNode *curr = root;
        curr->howMuchWords++;
        for (auto ch : s) {
            int c = (ch == '1');
            if (!exist(curr, c))
                curr->dict[c] = new TrieNode();
            curr = curr->dict[c];
            curr->howMuchWords++;
        }
        curr->isWord++;
    }

    // Assume word exists
    void remove(TrieNode *curr, const string &word, int idx = 0) {
        curr->howMuchWords--;

        if (idx == SZ(word)) {
            curr->isWord--;
            return;
        }

        auto c = (word[idx] == '1');
        auto next = curr->dict[c];
        remove(next, word, idx + 1);

        if (!next->howMuchWords) {
            delete (next);
            next = NULL;
            curr->dict[c] = NULL;
        }
    }

    // Numbers lower-equal than LimitL
    int query(const string limitL) {
        int ans = 0;
        TrieNode *curr = root;
        for (int i = 0; i < maxLOG; i++) {
            int bit_l = (limitL[i] == '1' ? 1 : 0);

            if (bit_l) {
                auto left = curr->dict[0];
                auto right = curr->dict[1];

                ans += (left ? left->howMuchWords : 0);

                if (!right)
                    break;
                curr = right;
            } else {
                auto left = curr->dict[0];
                auto right = curr->dict[1];

                if (!left)
                    break;
                curr = left;
            }
        }
        // remove this line if only strictly-lower
        ans += curr->isWord;
        return ans;
    }

    void Rec(TrieNode *root, const string &s) {
        for (int c = 0; c <= 1; c++) {
            if (!exist(root, c))
                continue;

            string aux = s;
            auto ch = (c == 1 ? '1' : '0');
            aux.push_back(ch);

            assert(root->dict[c] != NULL);
            Rec(root->dict[c], aux);
        }
        if (root->isWord)
            cout << s << endl;
    }

    void printWords() {
        string aux;
        Rec(root, aux);
    }
};
