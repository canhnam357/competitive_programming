const int mod1 = 1035972859;
const int mod2 = 1704760909;
const int mod3 = 2137321811;
const int mod4 = 2002577573;
const int mod5 = 2143922441;
const int base = 256;
struct hashing
{
	int mod;
	vector<int> h, p, inv;
	hashing() {}
	hashing(int mod, string s)
	{
		int n = s.length();
		this->mod = mod;
		h.resize(n);
		p.resize(n);
		inv.resize(n);
		h[0] = s[0];
		p[0] = 1;
		for (int i = 1; i < n; i++)
		{
			p[i] = (p[i - 1] * base) % mod;
			h[i] = (h[i - 1] + s[i] * p[i]) % mod;
		}
		inv[n - 1] = power(p[n - 1], mod - 2);
		for (int i = n - 2; i >= 0; i--) inv[i] = (inv[i + 1] * base) % mod;
	}
	int power(int a, int b)
	{
		int ans = 1;
		while (b)
		{
			if (b & 1) ans = (ans * a) % mod;
			(a *= a) %= mod;
			b >>= 1;
		}
		return ans;
	}
	int get(int l, int r)
	{
		if (l > r) return 0;
		return l ? ((h[r] - h[l - 1] + mod) * inv[l]) % mod : h[r];
	}
	bool same(int l1, int r1, int l2, int r2)
	{
		return get(l1, r1) == get(l2, r2);
	}
};
