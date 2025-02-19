// Taken from https://github.com/mhunicken/icpc-team-notebook-el-vasito/blob/master/geometry/kdtree.cpp

const lli EPS = 0;

struct pt { 
	lli x,y;
	pt(lli x, lli y):x(x),y(y){}
	pt(){}
	lli norm2(){return *this * *this;}
	bool operator==(pt p){return x == p.x && y == p.y;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(lli t){return pt(x*t,y*t);}
	lli operator*(pt p){return x*p.x+y*p.y;}

	lli operator%(pt p){return x*p.y-y*p.x;}

	bool operator<(pt p)const{ 
        if(x != p.x) return x < p.x;
        return y < p.y;
    }
};

const lli INF = (1LL << 63) - 1;
// given a set of points, answer queries of nearest point in O(log(n))
bool onx(pt a, pt b){return a.x<b.x;}
bool ony(pt a, pt b){return a.y<b.y;}
struct Node {
	pt pp;
	lli x0=INF, x1=-INF, y0=INF, y1=-INF;
	Node *first=0, *second=0;
	lli distance(pt p){
		lli x=min(max(x0,p.x),x1);
		lli y=min(max(y0,p.y),y1);
		return (pt(x,y)-p).norm2();
	}
	Node(vector<pt>&& vp):pp(vp[0]){
		for(pt p:vp){
			x0=min(x0,p.x); x1=max(x1,p.x);
			y0=min(y0,p.y); y1=max(y1,p.y);
		}
		if(SZ(vp)>1){
			sort(all(vp),x1-x0>=y1-y0?onx:ony);
			int m=SZ(vp)/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<pt>& vp):root(new Node({all(vp)})) {}
	pair<lli,pt> search(pt p, Node *node){
		if(!node->first){
			//avoid query point as answer
			if(p==node->pp) return {INF,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		lli bf=f->distance(p), bs=s->distance(p);
		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);
		if(bs<best.fst) best=min(best,search(p,s));
		return best;
	}
	pair<lli,pt> nearest(pt p){return search(p,root);}
};