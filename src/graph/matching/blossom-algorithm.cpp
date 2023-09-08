template <int MAXN = 500, int MAXM = 250000>
struct blossom {
	int match[MAXN], d[MAXN], fa[MAXN], c1[MAXN], c2[MAXN], v[MAXN], q[MAXN];
	int *qhead, *qtail;
	struct {
		int fa[MAXN];
		void init (int n) { for(int i = 0; i < n; i++) fa[i] = i; }
		int find (int x) { if (fa[x] != x) fa[x] = find (fa[x]); return fa[x]; }
		void merge (int x, int y) { x = find (x); y = find (y); fa[x] = y; } } ufs;
	void solve (int x, int y) {
		if (x == y) return;
		if (d[y] == 0) {
			solve (x, fa[fa[y]]); match[fa[y]] = fa[fa[y]];
			match[fa[fa[y]]] = fa[y];
		} else if (d[y] == 1) {
			solve (match[y], c1[y]); solve (x, c2[y]);
			match[c1[y]] = c2[y]; match[c2[y]] = c1[y]; } }
	int lca (int x, int y, int root) {
		x = ufs.find (x); y = ufs.find (y);
		while (x != y && v[x] != 1 && v[y] != 0) {
			v[x] = 0; v[y] = 1;
			if (x != root) x = ufs.find (fa[x]);
			if (y != root) y = ufs.find (fa[y]); }
		if (v[y] == 0) std::swap (x, y);
		for (int i = x; i != y; i = ufs.find (fa[i])) v[i] = -1;
		v[y] = -1; return x; }
	void contract (int x, int y, int b) {
		for (int i = ufs.find (x); i != b; i = ufs.find (fa[i])) {
			ufs.merge (i, b);
			if (d[i] == 1) { c1[i] = x; c2[i] = y; *qtail++ = i; } } }
	bool bfs (int root, int n, const edge_list <MAXN, MAXM> &e) {
		ufs.init (n); std::fill (d, d + MAXN, -1); std::fill (v, v + MAXN, -1);
		qhead = qtail = q; d[root] = 0; *qtail++ = root;
		while (qhead < qtail) {
			for (int loc = *qhead++, i = e.begin[loc]; ~i; i = e.next[i]) {
				int dest = e.dest[i];
				if (match[dest] == -2 || ufs.find (loc) == ufs.find (dest)) continue;
				if (d[dest] == -1)
					if (match[dest] == -1) {
						solve (root, loc); match[loc] = dest;
						match[dest] = loc; return 1;
					} else {
						fa[dest] = loc; fa[match[dest]] = dest;
						d[dest] = 1; d[match[dest]] = 0;
						*qtail++ = match[dest];
					} else if (d[ufs.find (dest)] == 0) {
						int b = lca (loc, dest, root);
						contract (loc, dest, b); contract (dest, loc, b); } } }
		return 0; }
	int solve (int n, const edge_list <MAXN, MAXM> &e) {
		std::fill (fa, fa + n, 0); std::fill (c1, c1 + n, 0);
		std::fill (c2, c2 + n, 0); std::fill (match, match + n, -1);
		int re = 0; for (int i = 0; i < n; i++)
			if (match[i] == -1) if (bfs (i, n, e)) ++re; else match[i] = -2;
		return re; } };
