/*
Let in[u] <= in[v], p = lca(u, v)
Case 1 : p = u -> [in[u], in[v]]
Case 2 : p != u -> [out[u], in[v]] [in[p], in[p]]
*/
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow - 1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
		) : (
			(y < hpow) ? 1 : 2
			);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = { 3, 0, 0, 1 };
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
struct query
{
	int l, r, id;
	int order;
	void init(int id) {
		this->id = id;
		cin >> l >> r;
		l--, r--;
		order = hilbertOrder(l, r, 18, 0);
	}
	bool operator < (const query& t) const {
		return order < t.order;
	}
};