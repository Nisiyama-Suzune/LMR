template <int MAXN = 1000000, int LOGN = 20>
struct ntt {
	int MOD[3] = {1045430273, 1051721729, 1053818881}, PRT[3] = {3, 6, 7};
	int exp[LOGN][MAXN][2];
	void init (int n, int mod = 998244353, int prt = 3) {
		for (int i = 2, cnt = 0; i <= n; i <<= 1, ++cnt) {
			exp[cnt][0][0] = exp[cnt][0][1] = 1; exp[cnt][1][0] = fpm (prt, (mod - 1) / i, mod);
			exp[cnt][1][1] = fpm (exp[cnt][1][0], mod - 2, mod);
			for (int k = 2; k < (i >> 1); ++k) for (int t = 0; t < 2; ++t)
				exp[cnt][k][t] = int (1ll * exp[cnt][k - 1][t] * exp[cnt][1][t] % mod); } }
	void solve (int *a, int n, int f = 0, int mod = 998244353) {
		for (int i = 0, j = 0; i < n; ++i) {
			if (i > j) std::swap (a[i], a[j]);
			for (int t = n >> 1; (j ^= t) < t; t >>= 1); }
		for (int i = 2, cnt = 0; i <= n; i <<= 1, ++cnt)
			for (int j = 0; j < n; j += i) for (int k = 0; k < (i >> 1); ++k) {
				int &pA = a[j + k], &pB = a[j + k + (i >> 1)];
				int A = pA, B = int (1ll * pB * exp[cnt][k][f] % mod);
				pA = A + B < mod ? A + B : A + B - mod;
				pB = A - B >= 0 ? A - B : A - B + mod; }
		if (f == 1) {
			int rev = fpm (n, mod - 2, mod);
			for (int i = 0; i < n; ++i) a[i] = int (1ll * a[i] * rev % mod); } } };
