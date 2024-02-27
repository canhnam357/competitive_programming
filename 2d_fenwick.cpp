struct FenWick2D {
	int n, m;
	vector<vector<int>> bit;
	FenWick2D() {}
	FenWick2D(int n, int m)
	{
		this->n = n;
		this->m = m;
		bit.resize(n + 5, vector<int>(m + 5));
	}
	// 1 - indexed
	void update(int row, int col, int value) 
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
	int get(int row, int col)
	{
		int sum = 0;
		for (int i = row; i; i -= i & -i)
		{
			for (int j = col; j; j -= j & -j)
			{
				sum += bit[i][j];
			}
		}
		return sum;
	}
};