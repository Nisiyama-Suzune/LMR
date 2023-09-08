template <int CUBEN = 3000>
struct prefix_mul {
	typedef long long (*func) (long long);
	func p_f, p_g, p_c;
	long long mod, th, inv, n, mem[CUBEN];
	prefix_mul (func p_f, func p_g, func p_c, long long th, long long mod, long long inv) :
		p_f (p_f), p_g (p_g), p_c (p_c), th (th), mod (mod), inv (inv) {}
	void init (long long n) {
		prefix_mul::n = n;
		for (long long i = 1, la; i <= n; i = la + 1) {
			if ((la = n / (n / i)) < th) continue;
			long long &ans = mem[n / la] = p_c (la);
			for (long long j = 2, ne; j <= la; j = ne + 1) {
				ne = la / (la / j);
				ans = (ans + mod - (p_g (ne) - p_g (j - 1) + mod) *
					(la / j < th ? p_f (la / j) : mem[n / (la / j)]) % mod);
				if (ans >= mod) ans -= mod; }
			if (inv != 1) ans = ans * inv % mod; } }
	long long ans (long long x) {
		if (n / x < th) return p_f (n / x);
		return mem[n / (n / x)]; } };
