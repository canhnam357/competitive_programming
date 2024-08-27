template <typename T>
struct FenWick2D {
	int n, m;
	vector<vector<T>> bit;
	FenWick2D() {}
	FenWick2D(int n, int m)
	{
		this->n = n;
		this->m = m;
		bit.resize(n + 1, vector<T>(m + 1));
	}
	// 1 - indexed
	void add(int row, int col, T value) 
	{
		for (int i = row; i <= n; i += i & -i)
		{
			for (int j = col; j <= m; j += j & -j)
			{
				bit[i][j] += value;
			}
		}
	}
	// sum of sub-rectangle [[1, 1], [row, col]]
	T get(int row, int col)
	{
		T sum = 0;
		for (int i = row; i; i -= i & -i)
		{
			for (int j = col; j; j -= j & -j)
			{
				sum += bit[i][j];
			}
		}
		return sum;
	}
	T get(int x1, int y1, int x2, int y2)
	{
		assert(1 <= x1 && x1 <= x2 && x2 <= n);
		assert(1 <= y1 && y1 <= y2 && y2 <= m);
		return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1);
	}
};
