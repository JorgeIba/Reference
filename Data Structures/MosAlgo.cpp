// Offline queries. Runs on O(n*sqrt(n))
struct Query{
	int l, r, indx;
	bool operator<(const Query& q) const{
		return make_pair(l/blck,r) < make_pair(q.l/blck, q.r);
	}
}Q[MXN];
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
vector<int> mosAlgo(int n){
	vector<int> ans(n);
	blck = sqrt(n+.0) + 1;
	sort(Q,Q+m);
	int L = 0;
	int R = -1;
	for(int i = 0; i < m; i++){
		Query q = Q[i];
		while(R < q.l) add(++R);
		while(L > q.l) add(--L);
		while(R > q.r) remove(R--);
		while(L < q.l) remove(L++);
		ans[q.indx] = getAns();
	}
	return ans;
}
