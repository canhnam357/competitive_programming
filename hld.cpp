// subtree v [in[v], out[v] - 1]
int n;
vector<vector<int>> adj;
vector<int> sz(n), in(n), out(n), head(n), par(n), h(n);
function<void(int, int)> dfs_sz = [&](int u, int p)
{
	sz[u] = 1;
	for (auto& v : adj[u])
	{
		if (v == p) continue;
		dfs_sz(v, u);
		sz[u] += sz[v];
		if (sz[v] > sz[adj[u][0]])
		{
			swap(v, adj[u][0]);
		}
	}
};
//dfs_sz(0, -1);
int t = 1;
function<void(int, int)> dfs_hld = [&](int u, int p)
{
	in[u] = t++;
	for (auto v : adj[u])
	{
		if (v == p) continue;
		par[v] = u;
		h[v] = h[u] + 1;
		head[v] = (v == adj[u][0] ? head[u] : v);
		dfs_hld(v, u);
	}
	out[u] = t;
};
//dfs_hld(0, -1);
function<int(int, int)> query = [&](int u, int v)
{
	int ans = 0;
	for (; head[u] != head[v]; v = par[head[v]])
	{
		if (h[head[u]] > h[head[v]]) swap(u, v);
		//ckmax(ans, get(in[head[v]], in[v]));
	}
	if (h[u] > h[v]) swap(u, v);
	//ckmax(ans, get(in[u], in[v]));
	return ans;
};
