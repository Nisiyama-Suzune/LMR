template <int MAXN = 1000, int MAXM = 100000>
struct isap {
	struct flow_edge_list {
		int size, begin[MAXN], dest[MAXM], next[MAXM], flow[MAXM];
		void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
		flow_edge_list (int n = MAXN) { clear (n); }
		void add_edge (int u, int v, int f) {
			dest[size] = v; next[size] = begin[u]; flow[size] = f; begin[u] = size++;
			dest[size] = u; next[size] = begin[v]; flow[size] = 0; begin[v] = size++; } };
	int pre[MAXN], d[MAXN], gap[MAXN], cur[MAXN], que[MAXN], vis[MAXN];
	int solve (flow_edge_list &e, int n, int s, int t) {
		for (int i = 0; i < n; ++i) { pre[i] = d[i] = gap[i] = vis[i] = 0; cur[i] = e.begin[i]; }
		int l = 0, r = 0; que[0] = t; gap[0] = 1; vis[t] = true;
		while (l <= r) { int u = que[l++];
			for (int i = e.begin[u]; ~i; i = e.next[i])
				if (e.flow[i] == 0 && !vis[e.dest[i]]) {
					que[++r] = e.dest[i];
					vis[e.dest[i]] = true;
					d[e.dest[i]] = d[u] + 1;
					++gap[d[e.dest[i]]]; } }
		for (int i = 0; i < n; ++i) if (!vis[i]) d[i] = n, ++gap[n];
		int u = pre[s] = s, v, maxflow = 0;
		while (d[s] < n) {
			v = n; for (int i = cur[u]; ~i; i = e.next[i])
				if (e.flow[i] && d[u] == d[e.dest[i]] + 1) {
					v = e.dest[i]; cur[u] = i; break; }
			if (v < n) {
				pre[v] = u; u = v;
				if (v == t) {
					int dflow = INF, p = t; u = s;
					while (p != s) { p = pre[p]; dflow = std::min (dflow, e.flow[cur[p]]); }
					maxflow += dflow; p = t;
					while (p != s) { p = pre[p]; e.flow[cur[p]] -= dflow; e.flow[cur[p] ^ 1] += dflow; } }
			} else {
				int mindist = n + 1;
				for (int i = e.begin[u]; ~i; i = e.next[i])
					if (e.flow[i] && mindist > d[e.dest[i]]) {
						mindist = d[e.dest[i]]; cur[u] = i; }
				if (!--gap[d[u]]) return maxflow;
				gap[d[u] = mindist + 1]++; u = pre[u]; } }
		return maxflow; } };
template <int MAXN = 1000, int MAXM = 100000>
struct dinic {
	struct flow_edge_list {
		int size, begin[MAXN], dest[MAXM], next[MAXM], flow[MAXM];
		void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
		flow_edge_list (int n = MAXN) { clear (n); }
		void add_edge (int u, int v, int f) {
			dest[size] = v; next[size] = begin[u]; flow[size] = f; begin[u] = size++;
			dest[size] = u; next[size] = begin[v]; flow[size] = 0; begin[v] = size++; } };
	int n, s, t, d[MAXN], w[MAXN], q[MAXN];
	int bfs (flow_edge_list &e) {
		std::fill (d, d + n, -1);
		int l, r; q[l = r = 0] = s, d[s] = 0;
		for (; l <= r; ++l)
			for (int k = e.begin[q[l]]; ~k; k = e.next[k])
				if (!~d[e.dest[k]] && e.flow[k] > 0) d[e.dest[k]] = d[q[l]] + 1, q[++r] = e.dest[k];
		return ~d[t] ? 1 : 0; }
	int dfs (flow_edge_list &e, int u, int ext) {
		if (u == t) return ext; int k = w[u], ret = 0;
		for (; ~k; k = e.next[k], w[u] = k) {
			if (ext == 0) break;
			if (d[e.dest[k]] == d[u] + 1 && e.flow[k] > 0) {
				int flow = dfs (e, e.dest[k], std::min (e.flow[k], ext));
				if (flow > 0) {
					e.flow[k] -= flow, e.flow[k ^ 1] += flow;
					ret += flow, ext -= flow; } } }
		if (!~k) d[u] = -1; return ret; }
	int solve (flow_edge_list &e, int n_, int s_, int t_) {
		int ans = 0; n = n_; s = s_; t = t_;
		while (bfs (e)) {
			for (int i = 0; i < n; ++i) w[i] = e.begin[i];
			ans += dfs (e, s, INF); }
		return ans; } };
