template<typename T>
struct Poly{
    vector<T> P;
    const int p = 1; //!! change for MOD

    Poly(){}
    Poly(int n, int value = 0): P(n, value) {}
    Poly(vector<T> A) {P = A;}

    void normalize(){ while(!P.empty() && !P.back()) P.pop_back();} // get rid of leading zeroes

    inline int size() const{return P.size();}
    inline void resize(int n) {P.resize(n);}

    T &operator[] (int i){ return P[i]; }
    const T &operator[] (int i) const{ return P[i]; } // To get access without dot

    void operator=(vector<T> A){this->P=A;}
    void operator=(Poly<T> A){this->P=A.P;}

    T add(T a, T b)
    {
		if(p == 1) return a+b;
	    return a+b<p? a+b: a+b-p;
    }

    T sub(T a, T b)
	{
		if(p == 1) return a-b;
		return a-b<0?a-b+p:a-b;
	}

    T mul(T a, T b)
    {
		if(p == 1) return a*b;
        return (a*b)%p;
    }

	T inv(T n)
    {
        if(p == 1) return 1 / n;
        return powerMod(n, p-2, p); //!!MOD
    }


    Poly operator+(const Poly<T> &A) { 
        Poly<T> ans(max(SZ(P), SZ(A.P)));
        for(int i = 0; i < SZ(ans); i++){
            T a = 0, b = 0;
            if(i<SZ(P)) a = P[i];
            if(i<SZ(A)) b = A[i];
            ans[i] = add(a,b);
        }
        ans.normalize();
        return ans;
    }

    Poly operator-(const Poly<T> &A) { 
        Poly<T> ans(max(SZ(P), SZ(A.P)));
        for(int i = 0; i < SZ(ans); i++){
            T a = 0, b = 0;
            if(i<SZ(P)) a = P[i];
            if(i<SZ(A)) b = A[i];
            ans[i] = sub(a,b);
        }
        ans.normalize();
        return ans;
    }

    Poly operator*(int k) { 
        Poly<T> ans( SZ(P) );
        for(int i = 0; i < SZ(ans); i++){
            ans[i] = mul(P[i], k);
        }
        return ans;
    }

    Poly operator*(const Poly<T> &A) { 
        return multiply(A.P, P);
    }
     
    Poly invert(int d = -1) //Returns 1 / F, with d coeffs
    {
        if(d==-1) d = SZ(P);
        Poly<T> R_n = vector<T>{ inv(P[0]) }; //equivalent to: 1 / F[0]
        while(SZ(R_n) <= d)
        {
            int j = 2*SZ(R_n);
            Poly<T> FF = P; FF.resize(j);
            Poly<T> RnF = R_n*FF;
            for(auto &x: RnF.P) x = sub(0,x);
            RnF[0] = add(RnF[0], 2);
            R_n = R_n * RnF;
            R_n.resize(j);
        }
        R_n.resize(d+1);
        return R_n;
    }

    Poly operator/(Poly<T> B) { //Returns Q -> A = Q*B + R
        Poly<T> A = *this;
        int n = SZ(A), m = SZ(B);
        if(n < m) return vector<T>{0};
        reverse(all(A.P)); reverse(all(B.P));
        A.resize(n-m+1); B.resize(n-m+1);
        Poly<T> Q =  A * B.invert();
        Q.resize(n-m+1);
        reverse(all(Q.P));
        return Q;
    }

    Poly operator%(const Poly<T> &B) { //Return R = A - Q*B
        Poly<T> A = *this;
        int n = SZ(A),  m = SZ(B);
        if(n >= m){
            Poly<T> R = (A/B)*B;
            A.resize(m-1);
            for(int i = 0; i<m-1; i++){
                A[i] = sub(A[i], R[i]);
            }
        }
        return A;
    }


    vector< Poly > STE; //Segment Tree - Evaluate
    void buildSTE(vector<T>&x){ //(x-x_0)(x-x_1)(x-x_2)...(x-x_n)
        int n = SZ(x);
        STE.resize(2*n);
        for(int i = n; i<2*n; i++) STE[i] = vector<T>{sub(0, x[i-n]), 1}; //Ojo: MOD
        for(int i = n-1; i; i--) STE[i] = STE[i<<1] * STE[i<<1 | 1];
    }

    vector<T> multiEvaluate(vector<T> &x){
        buildSTE(x);
        int m = SZ(x);
        vector< Poly<T> > ans(2*m);
        ans[1] = (*this) % STE[1];
        for(int i = 2; i<2*m; i++) ans[i] = ans[i>>1] % STE[i];
        vector<T> evals(m);
        for(int i = m; i<2*m; i++) evals[i-m] = ans[i][0];
        return evals;
    }

	Poly derivate(){
		int n = SZ(P);
		Poly<T> ans(n-1);
		for(int i = 1; i<n; i++)
			ans[i-1] = mul(P[i],i);
		return ans;
	}
    

	Poly interpolate(vector<T> &x, vector<T> &y)
	{
		buildSTE(x);
		int n = SZ(x);
		Poly<T> pp = STE[1].derivate();
		vector<T> d = pp.multiEvaluate(x);
		vector< Poly<T> > inTree(2*n);
		STE = pp.STE;
		for(int i = n; i<2*n; i++)
            inTree[i] = vector<T>{ mul(y[i-n], inv(d[i-n])) }; //y_i / d_i
		for(int i = n-1; i; i--)
			inTree[i] =  inTree[i<<1] * STE[i<<1|1] + inTree[i<<1|1] * STE[i<<1];
		return inTree[1];
	}

    Poly integrate(){
        Poly<T> A(SZ(P) + 1);
        for(int i = 1; i<=SZ(P); i++)
            A[i] = mul(P[i-1], inv(i));
        return A;
    }

    Poly logn(){
        assert(P[0] == 1);
        int n = SZ(P);
        Poly<T> A = ((*this).derivate()) * ((*this).invert());
        A.resize(n);
        A = A.integrate();
        A.resize(n);
        return A;
    }

    Poly exp(int d = -1){ //E(x) = E(x)(1-ln(E(x))+A(x))
        if(d == -1) d = SZ(P);
        assert(P[0] == 0);
        Poly<T> E = vector<T>{1};
        while(SZ(E) < d){
            int c = 2*SZ(E);
            E.resize(c);
            Poly<T> S = E.logn();
            S = (*this)-S;
            S[0] = 1;
            E = E * S;
            E.resize(c);
        }
        E.resize(d);
        return E;
    }

    Poly sqrt()
    {
        T r0 = 1; //! r0^2 == P[0] mod p
        T inv2 = inv(2);
        Poly<T> R(1, r0); 
        while(SZ(R) < SZ(P))
        {
            int c = 2*SZ(R);
            R.resize(c);
            Poly<T> F = P;
            F.resize( min(c, SZ(P)) );
            F = F * (R.invert());
            for(int i = 0; i<c; i++)
                R[i] = (R[i] + F[i])*inv2 % p;
        }
        R.resize(SZ(P));
        return R;
    }

    T eval(T a){
        T sum = 0, x = 1;
        for(int i = 0; i<SZ(P); i++){
            sum = add(sum, mul(x, P[i]));
            x = mul(x, a);
        }
        return sum;
    }
};

template<typename T>
ostream& operator<<(ostream &so, const Poly<T> &A)
{
    for(auto x: A.P) so<<x<<" ";
    return so;
}