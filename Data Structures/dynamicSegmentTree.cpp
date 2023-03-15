struct ST{
	int l, r;
	lli val, lazy;
	ST *left, *right;

	ST(int _l, int _r): l(_l), r(_r), val(0), lazy(0), left(NULL), right(NULL){}
	lli combine(){
		lli ret = 0;
		if(left){
			ret += left -> val;
		}
		if(right)
			ret += right -> val; 
		return ret;
	}
	void update(int a, int b, lli u){
		if(r < a || l > b) return;
		if(a <= l && r <= b){
			val += u*(r-l+1);
			lazy += u;
			return;
		}
		push();
		left -> update(a, b , u);
		right -> update(a, b, u);
		val = combine();
	}
	lli query(int a, int b){
		if(r < a || l > b) return 0;
		if(a <= l && r <= b) return val;
		push();
		return left -> query(a,b) + right -> query(a,b);
	}
	void push(){
		if(left == NULL){
			int mid = (l+r)>>1;
			left = new ST(l, mid);
			right = new ST(mid+1, r);
		}
		if(lazy){
			left -> val += lazy*(left -> r - left->l + 1);
			right -> val += lazy*(right -> r - right->l + 1);
			left -> lazy += lazy;
			right -> lazy += lazy;
			lazy = 0;
		}
	}
};
