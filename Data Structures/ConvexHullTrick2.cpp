
const lli INF = 1e15;
struct Line{
    lli m, b;
    Line(){}
    Line(lli m, lli b): m(m), b(b) {}
    lli eval(lli x){ return m*x + b; }
};
 
// Assuming slopes are non-decreasing
struct CHTrick{
    vector<Line> CH;
 
    lli inter(const Line &a, const Line &b){
        lli num = b.b - a.b, den = a.m - b.m;
        return num / den + (num % den ? !((num > 0) ^ ( den > 0)) : 0);
    }
 
    void add(lli m, lli b){
        Line l(m, b);
 
        if(SZ(CH) && m == CH.back().m){
            l.b = min(  b, CH.back().b  ); 
            CH.pop_back();
        }
 
        while( 2 <= SZ(CH) && inter(CH.back(), l) <= inter( CH[ CH.size() - 2 ], CH.back()  ))
            CH.pop_back();
 
        CH.push_back(l);
    }
 
    lli query(lli x){
        int l = 0, r = CH.size();
        while(r-l > 1) {
            int mid = l + (r-l)/2;
            if( inter(CH[mid], CH[mid-1]) > x)
                r = mid;
            else 
                l = mid;
        }
        return CH[l].eval(x);
    }
};