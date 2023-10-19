/*
FIFO queue struct, but it returns the minimum/maximum between the elements in
the queue max queue -> monotonic_queue<int,greater_equal<int>> maxi; min queue
-> monotonic_queue<int,less_equal<int>> mini;
*/
template <class T, class compare> struct monotonic_queue {
    deque<pair<T, int>> Q;
    int cnt_added = 0;
    int cnt_removed = 0;
    int _size = 0;
    void push(T x) {
        while (!Q.empty() && compare()(x, Q.back().first))
            Q.pop_back();
        Q.push_back({x, cnt_added});
        cnt_added++;
        _size++;
    }
    void pop() {
        if (!Q.empty() && Q.front().second == cnt_removed)
            Q.pop_front();
        cnt_removed++;
        _size--;
    }
    // returns the minimum/maximum element in the queue
    T monotonic() { return Q.front().first; }
    int size() { return _size; }
    void clear() {
        Q.clear();
        cnt_added = 0;
        cnt_removed = 0;
        _size = 0;
    }
};
