struct linear_rec {
	const int LOG = 30, MOD = 1E9 + 7; int n;
	std::vector <int> first, trans;
	std::vector <std::vector <int>> bin;
	std::vector <int> add (std::vector <int> &a, std::vector <int> &b) {
		std::vector <int> result(n * 2 + 1, 0);
		for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) 
			if ((result[i + j] += 1LL * a[i] * b[j] % MOD) >= MOD) result[i + j] -= MOD;
		for (int i = 2 * n; i > n; --i) {
			for (int j = 0; j < n; ++j)
				if ((result[i - 1 - j] += 1LL * result[i] * trans[j] % MOD) >= MOD) result[i - 1 - j] -= MOD;
			result[i] = 0; }
		result.erase(result.begin() + n + 1, result.end());
		return result; }
	linear_rec (const std::vector <int> &first, const std::vector <int> &trans) : first(first), trans(trans) {
			n = first.size(); std::vector <int> a(n + 1, 0); a[1] = 1; bin.push_back(a);
			for (int i = 1; i < LOG; ++i) bin.push_back(add(bin[i - 1], bin[i - 1])); }
	int solve (int k) {
		std::vector <int> a(n + 1, 0); a[0] = 1;
		for (int i = 0; i < LOG; ++i) if (k >> i & 1) a = add(a, bin[i]);
		int ret = 0;
		for (int i = 0; i < n; ++i) if ((ret += (long long) a[i + 1] * first[i] % MOD) >= MOD) ret -= MOD;
		return ret; } };

