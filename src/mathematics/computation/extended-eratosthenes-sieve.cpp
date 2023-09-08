template <int SN = 110000, int D = 2>
struct ees {
	int co[SN], prime[SN], psize, sn;
	long long powa[D + 1][SN], powb[D + 1][SN];
	long long funca[SN], funcb[SN];
	long long pow (long long x, int n) {
		long long res = 1;
		for (int i = 0; i < n; ++i) res *= x;
		return res; }
	long long pre_pow (long long x, int n) {
		if (n == 0) return x;
		if (n == 1) return (1 + x) * x / 2;
		if (n == 2) return (1 + 2 * x) * (1 + x) * x / 6;
		return 0; }
	long long pfunc (long long p) { return -1; }
	long long cfunc (long long k, long long p) { return 0; }
	void assemble () {
		for (int i = 1; i <= sn; ++i) {
			funca[i] = -powa[0][i];
			funcb[i] = -powb[0][i]; } }
	void init (long long n) {
		sn = std::max ((int) (ceil (sqrt (n)) + 1), 2);
		psize = 0; for (int i = 2; i <= sn; ++i) {
			if (!co[i]) prime[psize++] = i;
			for (int j = 0; 1LL * i * prime[j] <= sn; ++j) {
				co[i * prime[j]] = 1;
				if (i % prime[j] == 0) break; } }
		for (int d = 0; d <= D; ++d) {
			long long *pa = powa[d], *pb = powb[d];
			for (int i = 1; i <= sn; ++i) pa[i] = pre_pow (i, d) - 1; 
			for (int i = 1; i <= sn; ++i) pb[i] = pre_pow (n / i, d) - 1;
			for (int i = 0; i < psize; ++i) { int &pi = prime[i];
				for (int j = 1; j <= sn; ++j) if (n / j >= 1LL * pi * pi) {
					long long ch = n / j / pi;
					pb[j] -= ((ch <= sn ? pa[ch] : pb[j * pi]) - pa[pi - 1]) * pow (pi, d);
				} else break;
				for (int j = sn; j >= 1; --j) if (j >= 1LL * pi * pi)
					pa[j] -= (pa[j / pi] - pa[pi - 1]) * pow (pi, d);
				else break; } }
		assemble (); }
	void dfs (int x, int f, long long mul, long long val, long long n, long long &res) {
		for (; x < psize && mul * prime[x] * prime[x] <= n; ++x) {
			long long nmul = mul * prime[x], nval = val * pfunc (prime[x]);
			for (; nmul <= n; nmul *= prime[x], nval = cfunc (nval, prime[x]))
				dfs (x + 1, prime[x], nmul, nval, n, res); }
		if (n / mul > f) res += val * ((n / mul <= sn ? funca[n / mul] : funcb[mul]) - funca[f]);
		if (f > 1 && mul % (f * f) == 0) res += val; }
	long long solve (long long n) {
		if (n == 0) return 0;
		long long res = 1;
		init (n); dfs (0, 1, 1, 1, n, res);
		return res; } };

