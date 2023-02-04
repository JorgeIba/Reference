// Offline queries. Runs on O(n*sqrt(n))
struct Query{
    const static int BLOCK = 300;
	int l, r, indx;
	bool operator<(const Query& q) const{
		if(l/BLOCK != q.l/BLOCK) return l/BLOCK < q.l/BLOCK;
		if(l/BLOCK & 1) return r < q.r;
		return r > q.r;
	}
};
// Change the 2 functions below deppending on the problem
void add(int i){
	if(!rep[num[i]]) difNum++;
	rep[num[i]]++;
}
void remove(int i){
	if(rep[num[i]] == 1) difNum--;
	rep[num[i]]--;
}
int getAns(){
	return difNum;
}
// Be careful of return type
vector<int> mosAlgo(vector<Query> Q){
    int n = SZ(Q);
	vector<int> ans(n);
	sort(all(Q));
	int L = 0; // If 1-indexed L = 1, R = 0
	int R = -1;
	for(int i = 0; i < n; i++){
		Query q = Q[i];
        while(L > q.l) add(--L);
		while(R < q.r) add(++R);
		
        while(L < q.l) remove(L++);
		while(R > q.r) remove(R--);
		
		ans[q.indx] = getAns();
	}
	return ans;
}

// You can change this Query struct and comparator
// To speed up (Hilbert Curves)
struct Query{
	int l, r, indx;
    lli order;
	bool operator<(const Query& q) const{
		return order < q.order;
	}
};

// pow -> 2^k >= maxQ
inline lli hilbertOrder(int x, int y, int pow = 21, int rotate = 0) {
	if (pow == 0) return 0;

	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;

	lli subSquareSize = 1LL << (2*pow - 2);
	lli ans = seg * subSquareSize;
	lli add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}