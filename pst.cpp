struct Node {
    int l, r;
    int val;
    Node() : l(0), r(0), val(0) {};
    Node(int l_, int r_, int val_) : l(l_), r(r_), val(val_) {};
};
struct PST
{
    vector<Node> tree;
    vector<int> id_root;
    int n, N, sz; // sz is power_of_2
    PST() : n(0), N(0), sz(0) {}
    PST(int n) : n(n)
    {
        N = 0;
        sz = 1;
        while (sz / 2 < n + 5) sz *= 2;
        tree.resize(sz);
        id_root.resize(n + 5);
        id_root[0] = 1;
        build();
    }
    void build()
    {
        for (int i = 1; i < sz / 2; i++)
        {
            tree[i].l = i << 1;
            tree[i].r = i << 1 | 1;
        }
    }
    void update(int id, int l, int r, int x)
    {
        tree[id].val++;
        if (l != r)
        {
            int mid = (l + r) >> 1;
            int u = tree[id].l, v = tree[id].r;
            if (x <= mid)
            {
                tree[id].l = tree.size();
                tree.push_back(tree[u]);
                update(tree[id].l, l, mid, x);
            }
            else
            {
                tree[id].r = tree.size();
                tree.push_back(tree[v]);
                update(tree[id].r, mid + 1, r, x);
            }
        }
    }
    int get_kth(int u, int v, int k, int l, int r) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int sz = tree[tree[v].l].val - tree[tree[u].l].val;
        if (sz >= k) return get_kth(tree[u].l, tree[v].l, k, l, mid);
        return get_kth(tree[u].r, tree[v].r, k - sz, mid + 1, r);
    }
    int get_kth(int l, int r, int k)
    {
        return get_kth(id_root[l - 1], id_root[r], k, 1, sz / 2);
    }
    void create_node(int val)
    {
        id_root[++N] = tree.size(); 
        // N is pos_update
        // if use on tree, change ++N with current vertex, so N - 1 equal parent of this vertex
        tree.push_back(tree[id_root[N - 1]]);
        update(id_root[N], 1, sz / 2, val);
    }
};
