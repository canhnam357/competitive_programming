const int inf = (int)1e9;
// 1-indexed Centroid Decomposition
struct CentroidDecomposition {
#define MASK(i) (1LL << (i))
    vector<set<int>> G;
    vector<int> sz, par_centroid, h;
    vector<int> ans; // for query
    vector<vector<int>> par;
    CentroidDecomposition() {}
    CentroidDecomposition(vector<pair<int, int>>& edges) // vector edges, size n - 1
    {
        int n = edges.size() + 1;
        sz.resize(n + 1);
        ans.resize(n + 1, inf);
        par.resize(n + 1, vector<int>(__lg(n) + 1));
        G.resize(n + 1);
        h.resize(n + 1);
        par_centroid.resize(n + 1);
        for (int i = 0; i < n - 1; i++)
        {
            G[edges[i].first].insert(edges[i].second);
            G[edges[i].second].insert(edges[i].first);
        }
        first_dfs(1, 0); // calculate h, par for lca
        // RMQ for lca
        {
            int lg = __lg(n);
            for (int i = 1; i <= lg; i++)
            {
                for (int j = 1; j <= n; j++) par[j][i] = par[par[j][i - 1]][i - 1];
            }
        }
        build(1, 0);
        // par_centroid[root] = 0
    }
    int dfs(int u, int p) {
        sz[u] = 1;
        for (auto v : G[u]) if (v != p) {
            sz[u] += dfs(v, u);
        }
        return sz[u];
    }
    int centroid(int u, int p, int n) {
        for (auto v : G[u]) if (v != p) {
            if (sz[v] > n / 2) return centroid(v, u, n);
        }
        return u;
    }
    void build(int u, int p) {
        int n = dfs(u, p);
        int c = centroid(u, p, n);
        par_centroid[c] = p;
        vector<int> adj(G[c].begin(), G[c].end());
        for (auto v : adj) {
            G[c].erase(v); G[v].erase(c);
            build(v, c);
        }
    }
    void first_dfs(int u, int p) {
        for (auto v : G[u]) if (v != p) {
            h[v] = h[u] + 1;
            par[v][0] = u;
            first_dfs(v, u);
        }
    }
    int lca(int u, int v)
    {
        if (h[u] > h[v]) swap(u, v);
        int k = h[v] - h[u];
        int lg = (k == 0 ? -1 : __lg(k));
        for (int i = 0; i <= lg; i++) if (k & MASK(i)) v = par[v][i];
        if (v == u) return v;
        lg = (h[v] == 0 ? -1 : __lg(h[v]));
        for (int i = lg; i >= 0; i--)
        {
            if (par[v][i] != par[u][i])
            {
                v = par[v][i];
                u = par[u][i];
            }
        }
        return par[v][0];
    }
    int dis(int u, int v)
    {
        return h[v] + h[u] - 2 * h[lca(u, v)];
    }
    void modify(int u) {
        for (int v = u; v != 0; v = par_centroid[v]) ans[v] = min(ans[v], dis(v, u));
    }
    int query(int u) {
        int mn = inf;
        for (int v = u; v != 0; v = par_centroid[v]) mn = min(mn, ans[v] + dis(v, u));
        return mn;
    }
};  