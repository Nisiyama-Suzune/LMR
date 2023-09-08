template <int MAXN = 1000000, int MAXC = 26>
struct suffix_array {
	int rk[MAXN], height[MAXN], sa[MAXN];
	int cmp (int *x, int a, int b, int d) {
		return x[a] == x[b] && x[a + d] == x[b + d]; }
	void doubling (int *a, int n) {
		static int sRank[MAXN], tmpA[MAXN], tmpB[MAXN];
		int m = MAXC, *x = tmpA, *y = tmpB;
		for (int i = 0; i < m; ++i) sRank[i] = 0;
		for (int i = 0; i < n; ++i) ++sRank[x[i] = a[i]];
		for (int i = 1; i < m; ++i) sRank[i] += sRank[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--sRank[x[i]]] = i;
		for (int d = 1, p = 0; p < n; m = p, d <<= 1) {
			p = 0; for (int i = n - d; i < n; ++i) y[p++] = i;
			for (int i = 0; i < n; ++i) if (sa[i] >= d) y[p++] = sa[i] - d;
			for (int i = 0; i < m; ++i) sRank[i] = 0;
			for (int i = 0; i < n; ++i) ++sRank[x[i]];
			for (int i = 1; i < m; ++i) sRank[i] += sRank[i - 1];
			for (int i = n - 1; i >= 0; --i) sa[--sRank[x[y[i]]]] = y[i];
			std::swap (x, y); x[sa[0]] = 0; p = 1; y[n] = -1;
			for (int i = 1; i < n; ++i)
				x[sa[i]] = cmp (y, sa[i], sa[i - 1], d) ? p - 1 : p++; } }
	void solve (int *a, int n) {
		a[n] = -1; doubling (a, n);
		for (int i = 0; i < n; ++i) rk[sa[i]] = i;
		int cur = 0;
		for (int i = 0; i < n; ++i)
			if (rk[i]) {
				if (cur) cur--;
				for (; a[i + cur] == a[sa[rk[i] - 1] + cur]; ++cur);
				height[rk[i]] = cur; } } };

