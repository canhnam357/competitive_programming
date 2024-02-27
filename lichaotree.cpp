struct Line {
    int a, b;
    int get(int x) {
        return a * x + b;
    }
};

struct Node {
    int l, r; //child id
    int s, e; //range
    Line line;
};
struct Li_Chao {
    vector<Node> tree;
    const int inf = 2e18; // double of max_value possible
    // inf if Li_Chao_min
    // -inf if Li_Chao max
    void init(int s, int e) {
        tree.push_back({ -1, -1, s, e, { 0, inf } });
    }

    void update(int node, Line v) {
        int s = tree[node].s, e = tree[node].e;
        int m = (s + e) >> 1;

        Line low = tree[node].line, high = v;
        if (low.get(s) < high.get(s)) swap(low, high);

        if (low.get(e) >= high.get(e)) {
            tree[node].line = high; return;
        }

        if (low.get(m) > high.get(m)) {
            tree[node].line = high;
            if (tree[node].r == -1) {
                tree[node].r = tree.size();
                tree.push_back({ -1, -1, m + 1, e, { 0, inf } });
            }
            update(tree[node].r, low);
        }
        else {
            tree[node].line = low;
            if (tree[node].l == -1) {
                tree[node].l = tree.size();
                tree.push_back({ -1, -1, s, m, { 0, inf } });
            }
            update(tree[node].l, high);
        }
    }
    void update(Line v)
    {
        update(0, v);
    }
    int query(int node, int x) {
        if (node == -1) return inf;
        int s = tree[node].s, e = tree[node].e;
        int m = (s + e) >> 1;
        if (x <= m) return min(tree[node].line.get(x), query(tree[node].l, x));
        else return min(tree[node].line.get(x), query(tree[node].r, x));
    }
    int query(int x)
    {
        return query(0, x);
    }
};
// seg.init(-2e9, 2e9); // min_range, max_range x in queries