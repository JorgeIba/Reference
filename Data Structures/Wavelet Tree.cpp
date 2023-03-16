/*-----Wavelet Tree-----*/
/*
 * Sample use
 * vi a;
 * WaveletTree wv( a.begin(), a.end(), *min_element(a.begin(), a.end()), *max_element(a.begin(),a.end()) );
 */
struct WaveletTree{
	int low,high;
	WaveletTree *left, *right;
	vi mapLeft;

	WaveletTree( vi::iterator from, vi::iterator to, int x, int y ): low(x), high(y){
		if(from >= to) return;
		int m = (low+high)/2;
		auto f = [m](int x){ return x <= m; };
		mapLeft.reserve( to-from+1 );
		mapLeft.pb(0);
		for(auto it=from; it!=to; it++){
			auto leq = f(*it);
			mapLeft.pb( mapLeft.back()+ leq );
		}
		if(high != low){
			auto pivot = stable_partition(from,to,f);
			left = new WaveletTree(from,pivot,low,m);
			right = new WaveletTree(pivot,to,m+1,high);
		}
	}
	//returns the number of elements lesser than or equal to x int then subarray [l,..,r]
	int lessThanOrEqual(int l, int r, int x){
		if(l > r || low > x) return 0;
		if(high <= x) return r-l+1;
		int izq,der;
		izq = mapLeft[l-1];
		der = mapLeft[r];
		return left->lessThanOrEqual(izq+1,der,x) + right->lessThanOrEqual(l-izq,r-der,x);
	}
	//returns the k-th element in the range [l,r] if the subarray were sorted
	int kth(int l, int r, int k){
		if(l > r)//if no element exists
			return -1;
		if(low == high)
			return low;
		int lb = mapLeft[l - 1], rb = mapLeft[r];
		int inLeft = rb - lb;
		if(k <= inLeft)
			return left->kth(lb + 1, rb, k);
		else 
			return right->kth(l - lb, r - rb, k - inLeft);
	}
	//counts the elements in the range[l,r] such that its value is in the range [a,b]
	int elementsInRange(int l, int r, int a,int b){
		if(l > r || (a < low && b < low) || (a > high && b > high))
			return 0;
		if(a <= low && b >= high)
			return r - l + 1;
		int lb = mapLeft[l - 1], rb = mapLeft[r];
		return left->elementsInRange(lb + 1, rb, a, b) + right->elementsInRange(l - lb, r - rb, a, b);
	}
	//number of elements equal to k in [l, r]
	int equalTo(int l, int r, int k){
		if(l > r || k < low || k > high)
			return 0;
		if(low == high)
			return r - l + 1;
		int lb = mapLeft[l - 1], rb = mapLeft[r];
		int m = (low + high) / 2;
		if(k <= m)
			return left->equalTo(lb + 1, rb, k);
		else 
			return right->equalTo(l - lb, r - rb, k);
	}
};