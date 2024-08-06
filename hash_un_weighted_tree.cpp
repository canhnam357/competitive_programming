#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define int long long
#define MASK(i) (1LL << (i))
void ckmax(int& f, int s)
{
	f = (f > s ? f : s);
}
void ckmin(int& f, int s)
{
	f = (f < s ? f : s);
}
vector<int> Centroid(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> centroid;
    vector<int> sz(n);
    function<void (int, int)> dfs = [&](int u, int prev) {
            sz[u] = 1;
            bool is_centroid = true;
            for (auto v : g[u]) if (v != prev) {
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
const int mod2 = 2137321811;
const int mod3 = 2143922441;
const int mod1 = 2002577573;
set<tuple<int, int, int>> st;
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 mt(seed);
long long get_random(long long l, long long r, bool non_zero = 0)
{
	assert(l <= r);
	long long res;
	while (true)
	{
		res = mt() % (r - l + 1) + l;
		if (non_zero && !res) continue;
		break;
	}
	return res;
}
vector<int> rnd(31);
void solve()
{
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int sz = n;
	auto c = Centroid(adj);
	int root;
	if (c.size() == 2)
	{
		adj[c[0]].erase(find(all(adj[c[0]]), c[1]));
		adj[c[1]].erase(find(all(adj[c[1]]), c[0]));
		adj[c[0]].push_back(n);
		adj[c[1]].push_back(n);
		adj.push_back({});
		adj[n].push_back(c[0]);
		adj[n].push_back(c[1]);
		root = n;
		n++;
	}
	else root = c[0];
	vector<int> h1(n, 1), h2(n, 1), d(n);
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
	st.insert({sz, h1[root], h2[root]});
}
int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	for (int i = 0; i <= 30; i++)
	{
		rnd[i] = get_random(1, 1e9);
	}
	int t;
	cin >> t;
	while (t--) solve();
	cout << st.size() << '\n';
	return 0;
}
