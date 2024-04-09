struct RollingHash {
    lli hash = 0, mod, p, magic, inverse_p, size = 0;
    deque<char> curr;
    RollingHash(lli p, lli mod) : p(p), mod(mod) {
        inverse_p = getInverse();
        magic = 1;
    }
    void push_back(char newAdd) {
        hash = (hash * p + newAdd * p) % mod;
        magic = (magic * p) % mod;
        curr.push_back(newAdd);
    }
    void push_front(char newAdd) {
        magic = (magic * p) % mod;
        hash = (hash + newAdd * magic) % mod;
        curr.push_front(newAdd);
    }
    char pop_front() {
        char oldErase = curr.front();
        hash = (hash - oldErase * magic) % mod;
        if (hash < 0)
            hash += mod;
        magic = (magic * inverse_p) % mod;
        curr.pop_front();
        return oldErase;
    }
    char pop_back() {
        char last = curr.back();
        hash = (hash - curr.back() * p) % mod;
        if (hash < 0)
            hash += mod;
        hash = (hash * inverse_p) % mod;
        magic = (magic * inverse_p) % mod;
        curr.pop_back();
        return last;
    }

    void shiftRight() { push_front(pop_back()); }

    void shiftLeft() { push_back(pop_front()); }

    char getLast() { return curr.back(); }
    lli getHash() { return hash; }
    lli getInverse() {
        lli b = mod - 2; // If mod is prime, p^(mod-2) = 1 (mod m)
        lli res = 1, aux = p;
        while (b) {
            if (b & 1)
                res = (res * aux) % mod;
            b >>= 1;
            aux = (aux * aux) % mod;
        }
        return res;
    }
};
