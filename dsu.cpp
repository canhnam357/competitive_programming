struct dsu
{
    vector<int> par;
    int cc;
    dsu() : cc(0) {}
    dsu(int n)
    {
        cc = n;
        par.resize(n + 5);
        iota(par.begin(), par.end(), 0);
    }
    int find(int u)
    {
        return u == par[u] ? u : par[u] = find(par[u]);
    }
    void join(int a, int b)
    {
        a = find(a), b = find(b);
        if (a != b) par[a] = b, cc--;
    }
    bool same(int a, int b)
    {
        return find(a) == find(b);
    }
};
