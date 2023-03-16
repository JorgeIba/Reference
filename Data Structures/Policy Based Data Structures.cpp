//20
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set<int> s;
*s.find_by_order(k); //To get the i-th element, 0-indexed

s.order_of_key(k); //The number of items strictly smaller than n
//For multiset, use T = pair
//in second parameter a global counter
// s.order_of_key({k, -INF}) will return
// how many elements < k