struct fenwick
{
	int n;
	vector<int> bit;
	fenwick() {}
	fenwick(int n)
	{
		this->n = n + 5;
		bit.resize(n + 5);
	}
	void add(int pos, int val)
	{
		while (pos < n)
		{
			bit[pos] += val;
			pos += pos & -pos;
		}
	}
	int get(int pos)
	{
		int ans = 0;
		while (pos)
		{
			ans += bit[pos];
			pos -= pos & -pos;
		}
		return ans;
	}
	int get(int l, int r)
	{
		return get(r) - get(l - 1);
	}
	int find(int k)
	{
		int sum = 0, pos = 0;
		for (int i = __lg(n); i >= 0; i--)
		{
			if (pos + (1 << i) < n && sum + bit[pos + (1 << i)] < k)
			{
				sum += bit[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos + 1;
	}
};
