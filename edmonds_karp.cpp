// O(VE^2)
struct edmonds_karp
{
    int n;
    vector<vector<int>> cap;
    vector<vector<int>> adj;

    edmonds_karp() {}

    edmonds_karp(int n)
    {
        cap.resize(n + 2, vector<int>(n + 2));
        adj.resize(n + 2, vector<int>(n + 2));
        this->n = n + 2;
        // 0 is source
        // n + 1 is destination
    }

    int bfs(int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({ s, inf });

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && cap[cur][next]) {
                    parent[next] = cur;
                    int new_flow = min(flow, cap[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({ next, new_flow });
                }
            }
        }

        return 0;
    }

    int maxflow(int s, int t) {
        int flow = 0;
        vector<int> parent(n);
        int new_flow;

        while (new_flow = bfs(s, t, parent)) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                cap[prev][cur] -= new_flow;
                cap[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return flow;
    }

    void add_dir_edge(int u, int v, int c)
    {
        cap[u][v] += c;
        adj[u].push_back(v);
    }

    void add_undir_edge(int u, int v, int c)
    {
        cap[u][v] += c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};