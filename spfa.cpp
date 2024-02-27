const int INF = 1e18;
int main()
{
	int n, m, s, t;
	vector<vector<pair<int, int>>> adj(n);
	int inque_dist_sum = 0;
	vector<int> dist(n, INF);
	vector<int> trace(n, -1);
	vector<bool> inqueue(n, false);
	deque<int> que;
	que.push_back(s);
	dist[s] = 0;
	inqueue[s] = true;
	while (que.size()) {
		auto i = que.front();
		que.pop_front();
		inque_dist_sum -= dist[i];
		inqueue[i] = false;
		while (que.size() && dist[que.front()] * que.size() > inque_dist_sum) que.push_back(que.front()), que.pop_front();
		for (auto j : adj[i]) if (dist[j.first] > dist[i] + j.second) {
			if (inqueue[j.first]) inque_dist_sum -= dist[j.first];
			dist[j.first] = dist[i] + j.second;
			trace[j.first] = i;
			inque_dist_sum += dist[j.first];
			if (!inqueue[j.first]) {
				inqueue[j.first] = true;
				if (dist[j.first] * que.size() > inque_dist_sum) que.push_back(j.first);
				else que.push_front(j.first);
			}
		}
	}   
}