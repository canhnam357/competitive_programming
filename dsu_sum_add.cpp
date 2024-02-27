// update (sum, v.v)
int par[MAXN], add[MAXN] = {};
pair<int, int> find(int u) // first : root, second : sum_group
{
    if (u == par[u]) return make_pair(u, add[u]);
    auto p = find(par[u]);
    par[u] = p.first;
    add[u] += p.second - add[par[u]];
    return make_pair(par[u], add[u] + add[par[u]]);
}
void join(int a, int b)
{
    a = find(a).first, b = find(b).first;
    if (a != b)
    {
        par[a] = b;
        add[a] -= add[b];
    }
}