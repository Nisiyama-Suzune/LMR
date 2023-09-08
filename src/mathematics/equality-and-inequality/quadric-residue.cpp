struct quadric {
	void multiply(long long &c, long long &d, long long a, long long b, long long w, long long p) {
		int cc = (a * c + b * d % p * w) % p;
		int dd = (a * d + b * c) % p; c = cc, d = dd; }
	bool solve(int n, int p, int &x) {
		if (n == 0) return x = 0, true; if (p == 2) return x = 1, true;
		if (power (n, p / 2, p) == p - 1) return false;
		long long c = 1, d = 0, b = 1, a, w;
		do { a = rand() % p; w = (a * a - n + p) % p;
			if (w == 0) return x = a, true;
		} while (power (w, p / 2, p) != p - 1);
		for (int times = (p + 1) / 2; times; times >>= 1) {
			if (times & 1) multiply (c, d, a, b, w, p);
			multiply (a, b, a, b, w, p); }
		return x = c, true; } };

