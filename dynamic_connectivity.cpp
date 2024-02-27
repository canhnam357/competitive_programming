#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define MASK(i) (1LL << (i))
#define all(x) x.begin(), x.end()
void ckmin(int& f, int s)
{
    f = (f < s ? f : s);
}
void ckmax(int& f, int s)
{
    f = (f > s ? f : s);
}
const int inf = 1e9;
const int MAXN = 1e5 + 5;
struct DSUrb {
    vector<int> par, r;
    stack<vector<int>> s;
    void init(int n)
    {
        par.resize(n);
        r.resize(n);
        iota(par.begin(), par.end(), 0);
    }
    int get(int x) {
        if (x == par[x]) return x;
        return get(par[x]);
    }

    bool join(int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v) return false;

        if (r[u] < r[v]) swap(u, v);
        par[v] = u;

        if (r[u] == r[v]) {
            r[u]++;
            s.push({ u,v,1 });
        }
        else s.push({ u,v,0 });
        return true;
    }

    void rollback(int cnt) {
        while (cnt--) {
            auto a = s.top();
            s.pop();
            par[a[1]] = a[1];
            if (a[2] == 1) r[a[0]]--;
        }
    }

    int same(int a, int b)
    {
        return get(a) == get(b);
    }
};
pair<int, int> q[MAXN];
int cnt = 1, nq;
map<pair<int, int>, int> mp;
vector<vector<int>> e;
vector<vector<pair<int, int>>> st(1 << 18);
void update(int u, int v, int f, int s, int id = 1, int l = 1, int r = 1 << 17)
{
    if (r < u || l > v) return;
    if (l >= u && r <= v)
    {
        st[id].emplace_back(f, s);
        return;
    }
    int mid = (l + r) >> 1;
    update(u, v, f, s, id << 1, l, mid);
    update(u, v, f, s, id << 1 | 1, mid + 1, r);
}
DSUrb s;
void divide(int id = 1, int l = 1, int r = 1 << 17)
{
    int z = 0;
    for (auto x : st[id])
    {
        z += (int)s.join(x.first, x.second);
    }
    if (l == r)
    {
        if (l < cnt)
        {
            cout << s.same(q[l].first, q[l].second) << '\n';
        }
        s.rollback(z);
        return;
    }
    int mid = (l + r) >> 1;
    divide(id << 1, l, mid);
    divide(id << 1 | 1, mid + 1, r);
    s.rollback(z);
}
void solve()
{
    int n;
    cin >> n >> nq;
    s.init(n);
    for (int i = 0; i < nq; i++)
    {
        int t, a, b;
        cin >> t >> a >> b;
        a--, b--;
        if (a > b) swap(a, b);
        if (t == 1) mp[{a, b}] = cnt;
        else if (t == 2)
        {
            e.push_back({ a,b,mp[{a,b}],cnt - 1 });
            mp.erase(make_pair(a, b));
        }
        else
        {
            q[cnt++] = { a,b };
        }
    }
    for (auto x : mp)
    {
        e.push_back({ x.first.first, x.first.second, x.second, cnt - 1 });
    }
    for (int i = 0; i < e.size(); i++) update(e[i][2], e[i][3], e[i][0], e[i][1]);
    divide();
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}