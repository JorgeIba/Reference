template <typename T> struct TreapNode {
    T value;
    int key, size;
    TreapNode<T> *left, *right, *parent;

    // fields for queries
    T left_v, right_v, best_left, best_right;
    T best;

    TreapNode(T value = 0)
        : value(value), key(rand()), size(1), left(0), right(0), parent(0),
          left_v(value), right_v(value), best_left(1), best_right(1), best(1) {}
};

template <typename T> inline int nodeSize(TreapNode<T> *t) {
    return t ? t->size : 0;
}

template <typename T> void inorder(TreapNode<T> *t) {
    if (!t)
        return;
    inorder(t->left);
    cout << t->value << " ";
    inorder(t->right);
}

template <typename T>
inline void merge_nodes(TreapNode<T> *&parent, TreapNode<T> *left,
                        TreapNode<T> *right) {

    int left_v = left->left_v;
    int best_left = left->best_left;
    int right_v = right->right_v;
    int best_right = right->best_right;
    int best = max(left->best, right->best);
    int sizee = left->size + right->size;

    if (left->right_v == right->left_v) {
        best = max(best, left->best_right + right->best_left);

        bool right_full = (right->best_left == right->size);
        bool left_full = (left->best_right == left->size);

        if (left_full && right_full) {
            assert(left_v == right_v);
            best_left = left->size + right->size;
            best_right = left->size + right->size;
        } else if (left_full && !right_full) {
            best_left = left->size + right->best_left;
        } else if (!left_full && right_full) {
            best_right = left->best_right + right->size;
        }
    }

    parent->size = sizee;
    parent->left_v = left_v;
    parent->best_left = best_left;
    parent->best = best;
    parent->right_v = right_v;
    parent->best_right = best_right;

    // DO NOT TOUCH VALUE parent->value because for Reset
}

template <typename T> inline void update(TreapNode<T> *&t) {
    if (!t)
        return;

    // Reset
    t->size = 1;
    t->best_left = t->best = t->best_right = 1;
    t->left_v = t->right_v = t->value;

    if (t->left) {
        t->left->parent = t;
        merge_nodes(t, t->left, t);
    }

    if (t->right) {
        t->right->parent = t;
        merge_nodes(t, t, t->right);
    }
}

template <typename T> inline void push(TreapNode<T> *&t) {
    if (!t)
        return;
    if (t->left)
        t->left->parent = 0;
    if (t->right)
        t->right->parent = 0;
}

template <typename T>
void split(TreapNode<T> *t, int i, TreapNode<T> *&t1, TreapNode<T> *&t2) {
    if (!t)
        return void(t1 = t2 = NULL);
    push(t);

    int curr = nodeSize(t->left);

    if (i <= curr)
        split(t->left, i, t1, t->left), t2 = t;
    else
        split(t->right, i - curr - 1, t->right, t2), t1 = t;

    update(t1);
    update(t2);
    if (t1)
        t1->parent = 0;
    if (t2)
        t2->parent = 0;
}

inline int aleatorio() { return (rand() << 15) + rand(); }

template <typename T>
void merge(TreapNode<T> *&t, TreapNode<T> *t1, TreapNode<T> *t2) {
    if (!t1)
        t = t2;
    else if (!t2)
        t = t1;
    else if (aleatorio() % (nodeSize(t1) + nodeSize(t2)) < nodeSize(t1))
        merge(t1->right, t1->right, t2), t = t1;
    else
        merge(t2->left, t1, t2->left), t = t2;

    update(t);
};

template <typename T> pair<TreapNode<T> *, int> find_root(TreapNode<T> *t) {
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
