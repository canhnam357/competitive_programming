const int MAXN = 2e5 + 5;
vector<int> nodes[MAXN], f[MAXN];
void fakeUpdate(int u, int v) {
	for (int x = u; x < MAXN; x += x & -x)
		nodes[x].push_back(v);
}

void fakeGet(int u, int v) {
	for (int x = u; x > 0; x -= x & -x)
		nodes[x].push_back(v);
}
void update(int u, int v) {
	for (int x = u; x < MAXN; x += x & -x)
		for (int y = lower_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin() + 1; y <= nodes[x].size(); y += y & -y)
			f[x][y]++;
}

int get(int u, int v) {
	int res = 0;
	for (int x = u; x > 0; x -= x & -x)
		for (int y = upper_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin(); y > 0; y -= y & -y)
			res += f[x][y];
	return res;
}
void solve()
{
	// fake query here
	// ...
	for (int i = 1; i < MAXN; i++)
	{
		if (nodes[i].empty()) continue;
		sort(nodes[i].begin(), nodes[i].end());
		nodes[i].erase(unique(nodes[i].begin(), nodes[i].end()), nodes[i].end());
		f[i] = vector<int>(nodes[i].size() + 5);
	}
	// query here
}