template <int MAXN = 1000000>
struct dft {
	typedef std::complex <double> complex;
	complex e[2][MAXN];
	int init (int n) {
		int len = 1; for (; len <= 2 * n; len <<= 1);
		for (int i = 0; i < len; ++i) {
			e[0][i] = complex (cos (2 * PI * i / len), sin (2 * PI * i / len));
			e[1][i] = complex (cos (2 * PI * i / len), -sin (2 * PI * i / len)); }
		return len; }
	void solve (complex *a, int n, int f) {
		for (int i = 0, j = 0; i < n; ++i) {
			if (i > j) std::swap (a[i], a[j]);
			for (int t = n >> 1; (j ^= t) < t; t >>= 1); }
		for (int i = 2; i <= n; i <<= 1)
			for (int j = 0; j < n; j += i)
				for (int k = 0; k < (i >> 1); ++k) {
					complex A = a[j + k];
					complex B = e[f][n / i * k] * a[j + k + (i >> 1)];
					a[j + k] = A + B;
					a[j + k + (i >> 1)] = A - B; }
		if (f == 1) {
				for (int i = 0; i < n; ++i) a[i] = complex (a[i].real () / n, a[i].imag ()); } }
	void multiply (int *a, int *b, int *c, int n, int mod) {
		const int L = 15, MASK = (1 << L) - 1;
		static complex A[MAXN], B[MAXN], C[MAXN], D[MAXN];
		for (int i = 0; i < n; ++i) {
			A[i] = complex (a[i] >> L, a[i] & MASK);
			B[i] = complex (b[i] >> L, b[i] & MASK); }
		solve (A, n, 0), solve (B, n, 0);
		for (int i = 0; i < n; ++i) {
			int j = (n - i) % n;
			complex da = (A[i] - std::conj(A[j])) * complex(0, -0.5),
				db = (A[i] + std::conj(A[j])) * complex(0.5, 0),
				dc = (B[i] - std::conj(B[j])) * complex(0, -0.5),
				dd = (B[i] + std::conj(B[j])) * complex(0.5, 0);
			C[j] = da * dd + da * dc * complex(0, 1);
			D[j] = db * dd + db * dc * complex(0, 1); }
		solve (C, n, 0), solve (D, n, 0);
		for (int i = 0; i < n; ++i) {
			long long da = (long long) (C[i].imag () / n + 0.5) % mod,
				db = (long long) (C[i].real () / n + 0.5) % mod,
				dc = (long long) (D[i].imag () / n + 0.5) % mod,
				dd = (long long) (D[i].real () / n + 0.5) % mod;
		c[i] = ((dd << (L * 2)) + ((db + dc) << L) + da) % mod; } } };
