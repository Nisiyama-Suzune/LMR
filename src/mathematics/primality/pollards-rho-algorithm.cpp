struct pollard_rho {
	miller_rabin is_prime; const long long thr = 13E9;
	long long factor (const long long &n, const long long &seed) {
		long long x = rand () % (n - 1) + 1, y = x;
		for (int head = 1, tail = 2; ; ) {
			x = mul_mod (x, x, n);
			x = (x + seed) % n;
			if (x == y) return n;
			long long ans = std::__gcd (std::abs (x - y), n);
			if (ans > 1 && ans < n) return ans;
			if (++head == tail) { y = x; tail <<= 1; } } }
	void search (const long long &n, std::vector <long long> &div) {
		if (n > 1)  {
			if (is_prime.solve (n)) div.push_back (n);
			else {
				long long fac = n;
				for (; fac >= n; fac = factor (n, rand () % (n - 1) + 1));
				search (n / fac, div); search (fac, div); } } }
	std::vector <long long> solve (const long long &n) {
		std::vector <long long> ans;
		if (n > thr) search (n, ans);
		else {
			long long rem = n;
			for (long long i = 2; i * i <= rem; ++i)
				while (!(rem % i)) { ans.push_back (i); rem /= i; }
			if (rem > 1) ans.push_back (rem); }
		return ans; } };

