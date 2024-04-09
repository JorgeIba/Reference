/*-----Treap-----*/
struct Node {
  int key, priority, value;
  Node *left, *right;
  Node(int key, int priority)
      : key(key), priority(priority), value(key), left(NULL), right(NULL) {}
};

// modify this funciton depending on the query that you want
void update(Node *T) {
  if (T) {
    T->value = T->key;
    if (T->left)
      T->value += T->left->value;
    if (T->right)
      T->value += T->right->value;
  }
}

// returns the root of the union of treaps T1 and T2
Node *merge(Node *T1, Node *T2) {
  if (T1 == NULL)
    return T2;
  if (T2 == NULL)
    return T1;
  if (T1->priority > T2->priority) {
    T1->right = merge(T1->right, T2);
    update(T1);
    return T1;
  } else {
    T2->left = merge(T1, T2->left);
    update(T2);
    return T2;
  }
}

// returns the roots the division of the treap T with parameter x
pair<Node *, Node *> split(Node *T, int x) {
  if (T == NULL)
    return {NULL, NULL};
  Node *T1, *T2;
  if (T->key < x) {
    tie(T1, T2) = split(T->right, x);
    T->right = T1;
    update(T2);
    update(T);
    return {T, T2};
  } else {
    tie(T1, T2) = split(T->left, x);
    T->left = T2;
    update(T1);
    update(T);
    return {T1, T};
  }
}

// seed to generate random numbers
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// generates random numbers
uniform_int_distribution<> dis(numeric_limits<int>::min(),
                               numeric_limits<int>::max());

// inserts a new node with key = x in the treap T, returns the new root
Node *insert(Node *T, int x) {
  Node *TN = new Node(x, dis(rng));
  Node *L, *R;
  tie(L, R) = split(T, x);
  TN = merge(L, TN);
  TN = merge(TN, R);
  return TN;
}

// returns a treap with all the elements in a
Node *create(vi &a) {
  Node *T = NULL;
  forn(i, (int)a.size()) T = insert(T, a[i]);
  return T;
}

// erases the key x from the treap T
Node *erase(Node *T, int x) {
  Node *L, *R, *AUX;
  tie(L, R) = split(T, x);
  tie(AUX, R) = split(R, x + 1);
  return merge(L, R);
}

// returns the sum of all the keys in te range [l,r]
int query(Node **T, int l, int r) {
  Node *L, *X, *R;
  tie(L, X) = split(*T, l);
  tie(X, R) = split(X, r + 1);
  int ans = (X) ? X->value : 0;
  X = merge(L, X);
  *T = merge(X, R);
  return ans;
}

// returns the k-th node of the sorted nodes in the treap
Node *findKth(Node *T, int k) {
  if (T == NULL)
    return NULL;
  int aux = T->left ? T->left->value : 0;
  if (aux >= k)
    return findKth(T->left, k);
  else if (aux + 1 == k)
    return T;
  else
    return findKth(T->right, k - aux - 1);
}

/*-----Implicit Treap-----*/
/*
 * 1 indexed
 */

struct Node {
  int key, priority, size, rev;
  Node *left, *right;
  Node(int key, int priority)
      : key(key), priority(priority), size(1), /*value(key),*/ left(NULL),
        right(NULL) {}
};

// pushes the lazy updates
void push(Node *T) {
  if (T) {
    if (T->rev) {
      swap(T->left, T->right);
      if (T->left)
        T->left->rev ^= 1;
      if (T->right)
        T->right->rev ^= 1;
      T->rev = 0;
    }
  }
}

// modify this funciton depending on the query that you want
void update(Node *T) {
  //	push(T);
  if (T) {
    T->size = 1;
    if (T->left) {
      T->size += T->left->size;
    }
    if (T->right) {
      T->size += T->right->size;
    }
  }
}

// returns the root of the union of treaps T1 and T2
Node *merge(Node *T1, Node *T2) {
  push(T1), push(T2);
  if (T1 == NULL)
    return T2;
  if (T2 == NULL)
    return T1;
  if (T1->priority > T2->priority) {
    T1->right = merge(T1->right, T2);
    update(T1);
    return T1;
  } else {
    T2->left = merge(T1, T2->left);
    update(T2);
    return T2;
  }
}

// returns the roots the division of the treap T with parameter x
// T1 contains all nodes from [1,x), T2 contains all nodes from [x,T->size]
pair<Node *, Node *> split(Node *T, int x) {
  push(T);
  if (T == NULL)
    return {NULL, NULL};
  int index;
  if (T->left)
    index = T->left->size + 1;
  else
    index = 1;
  if (index < x) {
    Node *T1, *T2;
    tie(T1, T2) = split(T->right, x - index);
    T->right = T1;
    update(T);
    update(T2);
    return {T, T2};
  } else {
    Node *T1, *T2;
    tie(T1, T2) = split(T->left, x);
    T->left = T2;
    update(T1);
    update(T);
    return {T1, T};
  }
}

// seed to generate random numbers
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// generates random numbers
uniform_int_distribution<> dis(numeric_limits<int>::min(),
                               numeric_limits<int>::max());

// inserts a new node with key = x in the position ind of the treap T, returns
// the new root
Node *insert(Node *T, int x, int ind) {
  Node *TN = new Node(x, dis(rng));
  Node *L, *R;
  tie(L, R) = split(T, ind);
  TN = merge(L, TN);
  TN = merge(TN, R);
  return TN;
}

// returns a treap with all the elements in a
Node *create(vi a) {
  Node *T = NULL;
  forn(i, a.size()) T = insert(T, a[i], i + 1);
  return T;
}

// erases the key x from the treap T
Node *erase(Node *T, int ind) {
  Node *L, *R, *AUX;
  tie(L, R) = split(T, ind + 1);
  tie(L, AUX) = split(L, ind);
  return merge(L, R);
}

/*
//returns the sum of all the keys in te range [l,r]
int query(Node* T, int l, int r){
        Node *L,*X,*R;
        tie(L,X) = split(T,l);
        tie(X,R) = split(X,r+1);
        int ans  = (X) ? X->value : 0;
        X = merge(L,X);
        T = merge(X,R);
        return ans;
}
*/

// returns the k-th node of the treap
Node *findKth(Node *T, int k) {
  if (T == NULL)
    return NULL;
  int ind = T->left ? T->left->size + 1 : 1;
  if (ind > k)
    return findKth(T->left, k);
  else if (ind == k)
    return T;
  else
    return findKth(T->right, k - ind);
}

// reverser the treap from [l,r]
Node *reverse(Node *T, int l, int r) {
  Node *L, *R, *AUX;
  tie(L, R) = split(T, r + 1);
  tie(L, AUX) = split(L, l);
  if (AUX)
    AUX->rev ^= 1;
  L = merge(L, AUX);
  T = merge(L, R);
  return T;
}

// prints the Treap inorder
void inorder(Node *T) {
  if (T) {
    push(T);
    inorder(T->left);
    cout << T->key << " ";
    inorder(T->right);
  }
}
