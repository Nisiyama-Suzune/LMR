void euclid (const long long &a, const long long &b, long long &x, long long &y) {
	if (b == 0) x = 1, y = 0;
	else euclid (b, a % b, y, x), y -= a / b * x; }
long long inverse (long long x, long long m) {
	long long a, b; euclid (x, m, a, b); return (a % m + m) % m; }

