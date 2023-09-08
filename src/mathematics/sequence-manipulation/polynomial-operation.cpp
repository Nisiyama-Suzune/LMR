template <int MAXN = 1000000>
struct polynomial {
	ntt <MAXN> tr;
	void inverse (int *a, int *b, int n, int mod, int prt) {
		static int c[MAXN]; b[0] = ::inverse (a[0], mod); b[1] = 0;
		for (int m = 2, i; m <= n; m <<= 1) {
			std::copy (a, a + m, c);
			std::fill (b + m, b + m + m, 0); std::fill (c + m, c + m + m, 0);
			tr.solve (c, m + m, 0, mod, prt); tr.solve (b, m + m, 0, mod, prt);
			for (int i = 0; i < m + m; ++i) b[i] = 1LL * b[i] * (2 - 1LL * b[i] * c[i] % mod + mod) % mod;
			tr.solve (b, m + m, 1, mod, prt); std::fill (b + m, b + m + m, 0); } }
	void sqrt (int *a, int *b, int n, int mod, int prt) {
		static int d[MAXN], ib[MAXN]; b[0] = 1; b[1] = 0;
		int i2 = ::inverse (2, mod), m, i;
		for (int m = 2; m <= n; m <<= 1) {
			std::copy (a, a + m, d);
			std::fill (d + m, d + m + m, 0); std::fill (b + m, b + m + m, 0);
			tr.solve (d, m + m, 0, mod, prt); inverse (b, ib, m, mod, prt);
			tr.solve (ib, m + m, 0, mod, prt); tr.solve (b, m + m, 0, mod, prt);
			for (int i = 0; i < m + m; ++i) b[i] = (1LL * b[i] * i2 + 1LL * i2 * d[i] % mod * ib[i]) % mod;
			tr.solve (b, m + m, 1, mod, prt); std::fill (b + m, b + m + m, 0); } }
	void divide (int *a, int n, int *b, int m, int *d, int *r, int mod, int prt) {
		static int u[MAXN], v[MAXN]; while (!b[m - 1]) --m;
		int p = 1, t = n - m + 1; while (p < t << 1) p <<= 1;
		std::fill (u, u + p, 0); std::reverse_copy (b, b + m, u); inverse (u, v, p, mod, prt);
		std::fill (v + t, v + p, 0); tr.solve (v, p, 0, mod, prt); std::reverse_copy (a, a + n, u);
		std::fill (u + t, u + p, 0); tr.solve (u, p, 0, mod, prt);
		for (int i = 0; i < p; ++i) u[i] = 1LL * u[i] * v[i] % mod;
		tr.solve (u, p, 1, mod, prt); std::reverse (u, u + t); std::copy (u, u + t, d);
		for (p = 1; p < n; p <<= 1); std::fill (u + t, u + p, 0);
		tr.solve (u, p, 0, mod, prt); std::copy (b, b + m, v);
		std::fill (v + m, v + p, 0); tr.solve (v, p, 0, mod, prt);
		for (int i = 0; i < p; ++i) u[i] = 1LL * u[i] * v[i] % mod;
		tr.solve (u, p, 1, mod, prt);
		for (int i = 0; i < m; ++i) r[i] = (a[i] - u[i] + mod) % mod;
		std::fill (r + m, r + p, 0); } };

