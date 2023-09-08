struct bsgs {
	int solve (int a, int b, int c) {
		std::unordered_map <int, int> bs;
		int m = (int) sqrt ((double) c) + 1, res = 1;
		for (int i = 0; i < m; ++i) {
			if (bs.find (res) == bs.end ()) bs[res] = i;
			res = int (1LL * res * a % c); }
		int mul = 1, inv = (int) inverse (a, c);
		for (int i = 0; i < m; ++i) mul = int (1LL * mul * inv % c);
		res = b % c;
		for (int i = 0; i < m; ++i) {
			if (bs.find (res) != bs.end ()) return i * m + bs[res];
			res = int (1LL * res * mul % c); }
		return -1; } };

