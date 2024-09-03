auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 mt(seed);
long long get_random(long long l, long long r)
{
	assert(l <= r);
	return mt() % (r - l + 1) + l;
}
struct hash_unweighted_tree
{
	// NOTE : undirected graph
	const int mod1 = 2002577573;
	const int mod2 = 2137321811;
	int MAX_DEPTH;
	vector<int> rnd;
	void init(int MAX_DEPTH) // maybe number of vertex?
	{
		this->MAX_DEPTH = MAX_DEPTH;
		rnd.resize(MAX_DEPTH);
		for (int i = 0; i < MAX_DEPTH; i++) rnd[i] = get_random(1, min(mod1, mod2) - 1);
	}
	vector<int> Centroid(const vector<vector<int>> &adj) // get centroid, each tree have 1 or 2 centroid(s)
	{
	    int n = adj.size();
	    vector<int> centroid;
	    vector<int> sz(n);
	    function<void (int, int)> dfs = [&](int u, int p) 
	    {
            sz[u] = 1;
            bool is_centroid = true;
            for (auto v : adj[u]) if (v != p) {
                    dfs(v, u);
                    sz[u] += sz[v];
                    if (sz[v] > n / 2) is_centroid = false;
            }
            if (n - sz[u] > n / 2) is_centroid = false;
            if (is_centroid) centroid.push_back(u);
	    };
	    dfs(0, -1);
	    return centroid;
	}
	pair<int, int> get_hash(vector<vector<int>> adj, int root) // root = -1 if using centroid as root
	{
		int sz = adj.size();
		if (root == -1)
		{
			auto c = Centroid(adj);
			if (c.size() == 2)
			{
				adj[c[0]].erase(find(all(adj[c[0]]), c[1]));
				adj[c[1]].erase(find(all(adj[c[1]]), c[0]));
				adj[c[0]].push_back(sz);
				adj[c[1]].push_back(sz);
				adj.push_back({});
				adj[sz].push_back(c[0]);
				adj[sz].push_back(c[1]);
				root = sz;
				sz++;
			}
			else root = c[0];
		}
		vector<int> h1(sz, 1), h2(sz, 1), d(sz);
		function<void(int, int)> dfs = [&](int u, int p)
		{
			int has = 0;
			vector<int> z1, z2;
			for (int v : adj[u])
			{
				if (v == p) continue;
				has = 1;
				dfs(v, u);
				ckmax(d[u], d[v] + 1);
				z1.push_back(h1[v]);
				z2.push_back(h2[v]);
			}
			if (!has) return;
			sort(all(z1));
			sort(all(z2));
			for (int i = 0; i < z1.size(); i++)
			{
				h1[u] = (h1[u] * (rnd[d[u]] + z1[i])) % mod1;
				h2[u] = (h2[u] * (rnd[d[u]] + z2[i])) % mod2;
			}
		};
		dfs(root, -1);
		return {h1[root], h2[root]};
	} 
};