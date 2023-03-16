template<typename T = int>
struct TreapNode {
	TreapNode<T> *left, *right, *parent;
	T value;
	int key, size;
 
	TreapNode (T value = 0) : left(0), right(0), parent(0), value(value), key(rand()), size(1) {}
};

using Node = TreapNode<int>;
 
template<typename T>
inline int nodeSize (TreapNode<T>* t) { return t ? t->size : 0; }
 
template<typename T>
inline void update (TreapNode<T>* &t) {
	if (!t) return;
	t->size = 1 + nodeSize(t->left) + nodeSize(t->right);
	if (t->left) t->left->parent = t;
	if (t->right) t->right->parent = t;
}
 
template<typename T>
inline void push (TreapNode<T>* &t) {
	if (!t) return;
	if (t->left) t->left->parent = 0;
	if (t->right) t->right->parent = 0;
}
 
template<typename T>
void split (TreapNode<T>* t, int i, TreapNode<T>* &t1, TreapNode<T>* &t2) {
	if (!t) return void(t1 = t2 = NULL);
	push(t);
 
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
 
inline int aleatorio() {
	return (rand() << 15) + rand();
}
 
template<typename T>
void merge (TreapNode<T>* &t, TreapNode<T>* t1, TreapNode<T>* t2) {
	if (!t1) t = t2;
	else if (!t2) t = t1;
	else if (aleatorio() % (nodeSize(t1) + nodeSize(t2)) < nodeSize(t1))
		merge(t1->right, t1->right, t2), t = t1;
	else
		merge(t2->left, t1, t2->left), t = t2;
 
	update(t);
};
 
template<typename T>
pair<TreapNode<T>*, int> find_root (TreapNode<T> *t) {
	int izq = nodeSize(t->left);
	while (t->parent) {
		TreapNode<T> *ant = t;
		t = t->parent;
		if (ant == t->right) {
			izq += nodeSize(t->left) + 1;
		}
	}
	return {t, izq};
}
