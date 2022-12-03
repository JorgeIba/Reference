// Build on O(n log n) time and space, queries in O(1) for any operation
// Initialize OP and NEUTRO
// 0 - indexed
template<typename T>
struct DisjointSparseTable{
	vector<vector<T>> left, right;
	int K, N;

    typedef function<T(T, T)> typeFun;
    T NEUTRO;
    typeFun OP; // Default -> sum of 2 numbers

	DisjointSparseTable(const vector<T> &arr, T neutro = 0, typeFun op = plus<T>()): NEUTRO(neutro), OP(op){
		N = arr.size();
		K = log2(N) + 2;
		left.assign(K + 1, vector<T>(N));
		right.assign(K + 1, vector<T>(N));
		for(int j = 0; (1 << j) <= N; ++j){
			int mask = (1 << j) - 1;
			T acum = NEUTRO;
			for(int i = 0; i < N; ++i){
                acum = OP(acum, arr[i]);
				left[j][i] = acum;
				if((i & mask) == mask) acum = NEUTRO;
			}
			acum = NEUTRO; 
			for(int i = N-1; i >= 0; --i){
				acum = OP(acum, arr[i]);
				right[j][i] = acum;
				if((i & mask) == 0) acum = NEUTRO; 
			}
		}
	}

	T query(int l, int r){
		if(l == r) return left[0][l];
		int i = 31 - __builtin_clz(l^r);
		return OP(left[i][r], right[i][l]);
	}
};
