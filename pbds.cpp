#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset; // like multiset
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> order_set; // can use .erase(x) (x is value)
.insert(x); // insert x
.order_of_key(val + 1) - .order_of_key(val) > 0; // check val exists
.erase(.find_by_order(.order_of_key(c))) // erase c , should check exists before
.find_by_oder(pos) // s[pos] : 0-indexed
.order_of_key(x) // n.o element less than x
