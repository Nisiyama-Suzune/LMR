int fpm (int x, int n, int mod) {
	int ans = 1, mul = x; while (n) {
		if (n & 1) ans = int (1ll * ans * mul % mod);
		mul = int (1ll * mul * mul % mod); n >>= 1; }
	return ans; }
long long mul_mod (long long x, long long y, long long mod) {
	long long t = (x * y - (long long) ((long double) x / mod * y + 1E-3) * mod) % mod;
	return t < 0 ? t + mod : t; }
long long llfpm (long long x, long long n, long long mod) {
	long long ans = 1, mul = x; while (n) {
		if (n & 1) ans = mul_mod (ans, mul, mod);
		mul = mul_mod (mul, mul, mod); n >>= 1; }
	return ans; }

