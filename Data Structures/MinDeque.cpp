struct Node {
	vi dp;
	int p, t;
	
	Node () : dp(MA), p(0), t(0) {}
	Node (const vi &dp, int p, int t) : dp(dp), p(p), t(t) {}
	
	vi add (int p, int t) const {
		vi res = dp;
		forn (i, MA - p)
			res[i + p] = max(res[i + p], dp[i] + t);
		return res;
	}
};
 
struct MinDeque {
	stack<Node> a, b;
	
	MinDeque () {
		a.push(Node());
		b.push(Node());
	}
	
	Node& front () {
		if (a.size() == 1)
			move(b, a);
		return a.top();
	}
	
	Node& back () {
		if (b.size() == 1)
			move(a, b);
		return b.top();
	}
	
	void push_front (int p, int t) {
		a.emplace(a.top().add(p, t), p, t);
	}
	
	void push_back (int p, int t) {
		b.emplace(b.top().add(p, t), p, t);
	}
	
	void pop_front () {
		if (a.size() == 1)
			move(b, a);
		assert((int)a.size() > 1);
		a.pop();
	}
	
	void pop_back () {
		if (b.size() == 1)
			move(a, b);
		assert((int)b.size() > 1);
		b.pop();
	}
	
	void move (stack<Node> &from, stack<Node> &to) {
		int sz = from.size() / 2;
		stack<Node> aux;
		
		while ((int)from.size() > 1) {
			int p = from.top().p;
			int t = from.top().t;
			from.pop();
			
			if ((int)from.size() <= sz) {
				to.emplace(to.top().add(p, t), p, t);
			} else {
				aux.emplace(vi{}, p, t);
			}
		}
		
		while (aux.size()) {
			int p = aux.top().p;
			int t = aux.top().t;
			aux.pop();
			
			from.emplace(from.top().add(p, t), p, t);
		}
	}
	
	int query (int p) {
		int res = 0;
		forr (i, 0, p)
			res = max(res, a.top().dp[i] + b.top().dp[p - i]);
		return res;
	}
}dq;