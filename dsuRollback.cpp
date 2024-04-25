struct DSUrb {
    vector<int> par, r, sz;
    stack<vector<int>> s;
    void init(int n)
    {
        par.resize(n);
        r.resize(n);
        sz.resize(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int get(int x) {
        if (x == par[x]) return x;
        return get(par[x]);
    }

    bool join(int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v) return false;

        if (r[u] < r[v]) swap(u, v);
        par[v] = u;

        if (r[u] == r[v]) {
            r[u]++;
            s.push({ u,v,1, sz[v] });
        }
        else s.push({ u,v,0, sz[v] });
        sz[u] += sz[v];
        return true;
    }

    void rollback(int cnt) {
        while (cnt--) {
            auto a = s.top();
            s.pop();
            par[a[1]] = a[1];
            if (a[2] == 1) r[a[0]]--;
            sz[a[0]] -= a[3];
            sz[a[1]] = a[3];
        }
    }

    int same(int a, int b)
    {
        return get(a) == get(b);
    }
};
