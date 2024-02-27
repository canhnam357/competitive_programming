// 0 - indexed
vector<pair<int, int>> maxMatch(int L, int R, const vector<pair<int, int>>& edges) {
	vector<vector<int>> adj = vector<vector<int>>(L);
	vector<int> nxt(L, -1), prv(R, -1), lev, ptr;
	for (int i = 0; i < edges.size(); i++) adj.at(edges[i].first).push_back(edges[i].second);
	while (true) {
		lev = ptr = vector<int>(L); int max_lev = 0;
		queue<int> q; for (int i = 0; i < L; i++) if (nxt[i] == -1) lev[i] = 1, q.push(i);
		while (q.size()) {
			int x = q.front(); q.pop();
			for (int y : adj[x]) {
				int z = prv[y];
				if (z == -1) max_lev = lev[x];
				else if (!lev[z]) lev[z] = lev[x] + 1, q.push(z);
			}
			if (max_lev) break;
		}
		if (!max_lev) break;
		for (int i = 0; i < L; i++) if (lev[i] > max_lev) lev[i] = 0;
		auto dfs = [&](auto self, int x) -> bool {
			for (; ptr[x] < adj[x].size(); ++ptr[x]) {
				int y = adj[x][ptr[x]], z = prv[y];
				if (z == -1 || (lev[z] == lev[x] + 1 && self(self, z)))
					return nxt[x] = y, prv[y] = x, ptr[x] = adj[x].size(), 1;
			}
			return 0;
		};
		for (int i = 0; i < L; i++) if (nxt[i] == -1) dfs(dfs, i);
	}
	vector<pair<int, int>> ans; for (int i = 0; i < L; i++) if (nxt[i] != -1) ans.push_back({ i,nxt[i] });
	return ans;
}