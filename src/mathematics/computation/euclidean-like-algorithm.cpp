long long solve(long long n, long long a, long long b, long long m){
	if (b == 0) return n * (a / m);
	if (a >= m) return n * (a / m) + solve (n, a % m, b, m);
	if (b >= m) return (n - 1) * n / 2 * (b / m) + solve (n, a, b % m, m);
	return solve ((a + b * n) / m, (a + b * n) % m, m, b); }

