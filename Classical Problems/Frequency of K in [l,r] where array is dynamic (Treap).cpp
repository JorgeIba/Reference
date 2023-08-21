#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


template<typename T>
struct TreapNode{
	T value = 0;
	int key, size;
    TreapNode<T> *left, *right, *parent;

	TreapNode<T> *original;
	int idx = -1;
	TreapNode(T value = 0): value(value), key(rand()), size(1), left(0), right(0), parent(0), original(0){}
	TreapNode(TreapNode<T> *ori, int idx): value(ori->value), key(rand()), size(1), left(0), right(0), parent(0), original(ori), idx(idx) {}
};

template<typename T = TreapNode<int>>
struct Treap{
	T *root;

	Treap(): root(NULL) {}

	static inline int nodeSize (T* t) { return t ? t->size : 0; }

	static void inorder(T* t){
		if(!t) return;
		inorder(t->left);
		cout << t->value << "-" << t->idx << " ";
		inorder(t->right);
	}

	static inline void merge_nodes(T* &parent, T* left, T* right) {
		int sizee = left->size + right->size;
		parent->size = sizee;
	}

	static inline void update(T* &t){
		if(!t) return;
		t->size = 1;
		if(t->left) {
			t->left->parent = t;
			merge_nodes(t, t->left, t);
		}
		if(t->right) {
			t->right->parent = t;
			merge_nodes(t, t, t->right);
		}
	}

	static void split (T* t, int i, T* &t1, T* &t2) {
		if (!t) return void(t1 = t2 = NULL);

		int curr = nodeSize(t->left);
	
		if (i <= curr)
			split(t->left, i, t1, t->left), t2 = t;
		else
			split(t->right, i - curr - 1, t->right, t2), t1 = t;
	
		update(t1);
		update(t2);
		if (t1) t1->parent = 0;
		if (t2) t2->parent = 0;
	}

	int nth(T* t, int i){
		assert(0 <= i && i < nodeSize(t));
		int curr = nodeSize(t->left);
		if(i == curr)
			return t->value;		
		else if(i < curr)
			return nth(t->left, i);
		else
			return nth(t->right, i - curr - 1);
	}

	// Split depending of the index in original array (not in Treap array)
	static void split2 (T* t, int i, T* &t1, T* &t2) {
		if (!t) return void(t1 = t2 = NULL);
		auto [root, curr] = find_root(t->original);
		if (i <= curr)
			split2(t->left, i, t1, t->left), t2 = t;
		else
			split2(t->right, i, t->right, t2), t1 = t;
	
		update(t1);
		update(t2);
		if (t1) t1->parent = 0;
		if (t2) t2->parent = 0;
	}
	
	static inline int aleatorio() {
		return (rand() << 15) + rand();
	}
	
	static void merge (T* &t, T* t1, T* t2) {
		if (!t1) t = t2;
		else if (!t2) t = t1;
		else if (aleatorio() % (nodeSize(t1) + nodeSize(t2)) < nodeSize(t1))
			merge(t1->right, t1->right, t2), t = t1;
		else
			merge(t2->left, t1, t2->left), t = t2;
	
		update(t);
	};
	
	static pair<T*, int> find_root (T *t) {
		int izq = nodeSize(t->left);
		while (t->parent) {
			T *ant = t;
			t = t->parent;
			if (ant == t->right) {
				izq += nodeSize(t->left) + 1;
			}
		}
		return {t, izq};
	}

	T* insert(int num){
		T *node = new T(num);
		merge(root, root, node);
		return node;
	}

	T* insert(T *node, int idx){
		T *nnode = new T(node, idx);
		merge(root, root, nnode);
		return nnode;
	}

};

using TNode = TreapNode<int>;

const int MAXN = 1e5 + 100;

int main () {
	fastIO();

    int n; cin>>n;
    vector<int> nums(n);    
    for(auto &x: nums) cin>>x;


	Treap<TNode> *General = new Treap<TNode>();
	vector< TNode* > Nodes(n);
	forn(i, n){
		auto x = nums[i];
		auto node = General->insert(x);
		Nodes[i] = node;
	}


	vector< Treap<TNode> * > Treaps(MAXN, NULL);
	forn(i, n){
		auto x = nums[i];
		if(Treaps[x] == NULL) Treaps[x] = new Treap<TNode>();
		Treaps[x]->insert(Nodes[i], i);
	}

    // Answers frequency of K in range [l, r]
	auto query = [&](int l, int r, int k){
		if(!Treaps[k]) return 0;
		TNode *left = NULL, *middle = NULL, *right = NULL;

		Treaps[k]->split2(Treaps[k]->root, r, left, right);
		Treaps[k]->split2(left, l-1, left, middle);

		auto ans = middle ?  middle->size : 0;

		Treaps[k]->merge(Treaps[k]->root, left, middle);
		Treaps[k]->merge(Treaps[k]->root, Treaps[k]->root, right);

		return ans;
	};

    // Here changes the array
	auto update = [&](int l, int r) -> void {
		auto k = General->nth(General->root, r-1);
		TNode *left_k = NULL, *middle_k = NULL, *single_k = NULL, *right_k = NULL;
		Treaps[k]->split2(Treaps[k]->root, r, left_k, right_k);
		Treaps[k]->split2(left_k, r-1, left_k, single_k);
		Treaps[k]->split2(left_k, l-1, left_k, middle_k);

		Treaps[k]->merge(left_k, left_k, single_k);
		Treaps[k]->merge(left_k, left_k, middle_k);
		Treaps[k]->merge(Treaps[k]->root, left_k, right_k);


		TNode *left = NULL, *middle = NULL, *single = NULL, *right = NULL;
		General->split(General->root, r, left, right);
		General->split(left, r-1, left, single);
		General->split(left, l-1, left, middle);

		General->merge(left, left, single);
		General->merge(left, left, middle);
		General->merge(General->root, left, right);
	};


	int q; cin>>q;
	int last = 0;
	while(q--){
		int t, l, r; cin>>t>>l>>r;
		l = (l + last - 1) % n + 1;
		r = (r + last - 1) % n + 1;
		if(l > r) swap(l, r);

		if(t == 1){
			update(l, r);
		} else{
			int k; cin>>k;
			k = (k + last - 1) % n + 1;
			auto ans = query(l, r, k);
		
			cout << ans << endl;
			last = ans;
		}
	}


	return 0;
}

