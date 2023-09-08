template <int MAXN = 100000, int MAXM = 100000>
struct dominator_tree {
	int dfn[MAXN], sdom[MAXN], idom[MAXN], id[MAXN], f[MAXN], fa[MAXN], smin[MAXN], stamp;
	void predfs (int x, const edge_list <MAXN, MAXM> &succ) {
		id[dfn[x] = stamp++] = x;
		for (int i = succ.begin[x]; ~i; i = succ.next[i]) {
			int y = succ.dest[i];
			if (dfn[y] < 0) { f[y] = x; predfs (y, succ); } } }
	int getfa (int x) {
		if (fa[x] == x) return x;
		int ret = getfa (fa[x]);
		if (dfn[sdom[smin[fa[x]]]] < dfn[sdom[smin[x]]]) smin[x] = smin[fa[x]];
		return fa[x] = ret; }
	void solve (int s, int n, const edge_list <MAXN, MAXM> &succ) {
		std::fill (dfn, dfn + n, -1); std::fill (idom, idom + n, -1);
		static edge_list <MAXN, MAXM> pred, tmp; pred.clear (n);
		for (int i = 0; i < n; ++i) for (int j = succ.begin[i]; ~j; j = succ.next[j])
			pred.add_edge (succ.dest[j], i);
		stamp = 0; tmp.clear (n); predfs (s, succ);
		for (int i = 0; i < stamp; ++i) fa[id[i]] = smin[id[i]] = id[i];
		for (int o = stamp - 1; o >= 0; --o) {
			int x = id[o];
			if (o) {
				sdom[x] = f[x];
				for (int i = pred.begin[x]; ~i; i = pred.next[i]) {
					int p = pred.dest[i];
					if (dfn[p] < 0) continue;
					if (dfn[p] > dfn[x]) { getfa (p); p = sdom[smin[p]]; }
					if (dfn[sdom[x]] > dfn[p]) sdom[x] = p; }
				tmp.add_edge (sdom[x], x); }
			while (~tmp.begin[x]) {
				int y = tmp.dest[tmp.begin[x]];
				tmp.begin[x] = tmp.next[tmp.begin[x]]; getfa (y);
				if (x != sdom[smin[y]]) idom[y] = smin[y];
				else idom[y] = x; }
			for (int v : succ[x]) if (f[v] == x) fa[v] = x; }
		idom[s] = s; for (int i = 1; i < stamp; ++i) {
			int x = id[i]; if (idom[x] != sdom[x]) idom[x] = idom[idom[x]]; } } };

