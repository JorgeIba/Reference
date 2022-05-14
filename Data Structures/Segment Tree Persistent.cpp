template<typename T>
struct SegTreePers {
    const static T neutro = 0; // Neutro of operation
    struct Node{
        int l, r;
        T sum;
        Node *left = NULL, *right = NULL;

        Node(int l, int r, T val = neutro): l(l), r(r), sum(val) {}

        void extend(){
            int mid = l + ((r - l) >> 1);
            if(!left) {
                left = new Node(l, mid);
                right = new Node(mid+1, r);
            }
        }
    };

    int lMax, rMax;
    vector<Node*> versions;

    SegTreePers(int lMax, int rMax): lMax(lMax), rMax(rMax) {
        versions.push_back(new Node(lMax, rMax));
    }

    // Operation
    T merge(T vleft, T vright) { 
        return vleft + vright;
    }

    // Recursive Calls
    Node* updateVal(int pos, Node* curr, T val) {   
        int l = curr->l, r = curr->r;

        if(pos < l || r < pos) return curr;
        if( l == r ) return new Node(l, r, val);
        
        curr->extend();

        Node *newNode = new Node(l, r);
        newNode->left = updateVal(pos, curr->left, val);
        newNode->right = updateVal(pos, curr->right, val);
        newNode->sum = merge(newNode->left->sum, newNode->right->sum);
        
        return newNode;
    }

    T queryKthSmallest(Node* curr_l, Node* curr_r, int k) {
        int l = curr_r->l, r = curr_r->r;
        if(l == r) return l;

        T left_sum = curr_r->left->sum - curr_l->left->sum;

        if(k > left_sum)
            return queryKthSmallest(curr_l->right, curr_r->right, k - left_sum);
        else 
            return queryKthSmallest(curr_l->left, curr_r->left, k);
    }

    T querySum(int l, int r, Node* curr) {
        if( curr->l > r || curr->r < l) return 0;
        else if( l <= curr->l && curr->r <= r ) return curr->sum;

        if(!curr->left || !curr->right) return neutro; // No changes here
        return merge(querySum(l, r, curr->left), querySum(l, r, curr->right));
    }


    // Methods to call
    Node* updateVal(int idx, T val, int version = -1) {
        Node *curr = version != -1 ? versions[version] : versions.back();
        versions.push_back(updateVal(idx, curr, val));
        return versions.back();
    }

    T queryKthSmallest(int l, int r, int k) {
        return queryKthSmallest(versions[l], versions[r], k);
    }

    T querySum(int l, int r, int version) {
        return querySum(l, r, versions[version]);
    }
};