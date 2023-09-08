template <int MAXN = 100000, int MAXM = 100000>
struct hopcoft_karp {
	int mx[MAXN], my[MAXM], lv[MAXN];
	bool dfs (edge_list <MAXN, MAXM> &e, int x) {
		for (int i = e.begin[x]; ~i; i = e.next[i]) {
			int y = e.dest[i], w = my[y];
			if (!~w || (lv[x] + 1 == lv[w] && dfs (e, w))) {
				mx[x] = y; my[y] = x; return true; } }
		lv[x] = -1; return false; }
	int solve (edge_list <MAXN, MAXM> &e, int n, int m) {
		std::fill (mx, mx + n, -1); std::fill (my, my + m, -1);
		for (int ans = 0; ; ) {
			std::vector <int> q;
			for (int i = 0; i < n; ++i)
				if (mx[i] == -1) {
					lv[i] = 0; q.push_back (i);
				} else lv[i] = -1;
			for (int head = 0; head < (int) q.size(); ++head) {
				int x = q[head];
				for (int i = e.begin[x]; ~i; i = e.next[i]) {
					int y = e.dest[i], w = my[y];
					if (~w && lv[w] < 0) { lv[w] = lv[x] + 1; q.push_back (w); } } }
			int d = 0; for (int i = 0; i < n; ++i) if (!~mx[i] && dfs (e, i)) ++d;
			if (d == 0) return ans; else ans += d; } } };

