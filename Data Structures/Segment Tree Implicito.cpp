struct Node {
  lli value_range = 0;
  // lli neutro_lazy = 0, lazy = neutro_lazy; // FOR LAZY
  int l_range, r_range;
  Node *left_node = NULL, *right_node = NULL;

  Node() {}
  Node(int l_range, int r_range) : l_range(l_range), r_range(r_range) {}

  void extend() {
    int mid = l_range + ((r_range - l_range) >> 1);
    if (!left_node)
      left_node = new Node(l_range, mid);
    if (!right_node)
      right_node = new Node(mid + 1, r_range);
  }

  /* FOR LAZY
  void apply_lazy(){
      if(lazy != neutro_lazy){
          propagate(lazy);
          lazy = neutro_lazy;
      }
  }
  void propagate(lli value){
      value_range += (r_range-l_range+1) * value;

      if(!left_node || !right_node) extend();
      left_node->lazy += value;
      right_node->lazy += value;
  }
  */
};

void update(Node *curr, int left_query, int right_query, lli value) {
  // curr->apply_lazy(); // FOR LAZY

  if (curr->l_range > right_query || curr->r_range < left_query)
    return;
  else if (left_query <= curr->l_range && curr->r_range <= right_query) {
    // curr->propagate(value); // CHANGE FOR LAZY
    curr->value_range = value;
    return;
  }
  curr->extend();

  update(curr->left_node, left_query, right_query, value);
  update(curr->right_node, left_query, right_query, value);

  curr->value_range =
      curr->left_node->value_range + curr->right_node->value_range; // merge
}

lli query(Node *curr, int left_query, int right_query) {
  // curr->apply_lazy(); // FOR LAZY

  if (curr->l_range > right_query || curr->r_range < left_query)
    return 0;
  else if (left_query <= curr->l_range && curr->r_range <= right_query) {
    return curr->value_range;
  }
  if (!curr->left_node || !curr->right_node)
    return 0; // No changes here
  return query(curr->left_node, left_query, right_query) +
         query(curr->right_node, left_query, right_query); // merge
}
