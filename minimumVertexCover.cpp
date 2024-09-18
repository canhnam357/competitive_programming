vector<vector<int>> minimumVertexCover(int L, int R, const vector<pair<int, int>>& edges)
{
	vector<vector<int>> adjl(L), adjr(R);
	vector<int> in_maxMatch(L);
	auto p = maxMatch(L, R, edges);
	for (auto x : edges)
	{
		if (find(all(p), x) != p.end())
		{
			in_maxMatch[x.first] = 1;
			adjr[x.second].push_back(x.first);
		}
		else
		{
			adjl[x.first].push_back(x.second);
		}
	}
	vector<int> visl(L), visr(R);
	function<void(int, int)> dfs = [&](int u, int p)
	{
		if (p) 
		{
			visr[u] = 1;
			for (int v : adjr[u])
			{
				if (!visl[v]) dfs(v, 0);
			}
		}
		else 
		{
			visl[u] = 1;
			for (int v : adjl[u])
			{
				if (!visr[v]) dfs(v, 1);
			}
		}
	};
	for (int i = 0; i < L; i++)
	{
		if (!in_maxMatch[i] && !visl[i]) dfs(i, 0);
	}
	vector<vector<int>> ans(2);
	for (int i = 0; i < L; i++) if (!visl[i]) ans[0].push_back(i);
	for (int i = 0; i < R; i++) if (visr[i]) ans[1].push_back(i);
	return ans;
}