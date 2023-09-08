struct miller_rabin {
	int BASE[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	bool check (const long long &p, const long long &b) {
		long long n = p - 1;
		for (; ~n & 1; n >>= 1);
		long long res = llfpm (b, n, p);
		for (; n != p - 1 && res != 1 && res != p - 1; n <<= 1)
			res = mul_mod (res, res, p);
		return res == p - 1 || (n & 1) == 1; }
	bool solve (const long long &n) {
		if (n < 2) return false;
		if (n < 4) return true;
		if (~n & 1) return false;
		for (int i = 0; i < 12 && BASE[i] < n; ++i) if (!check (n, BASE[i])) return false;
		return true; } };

