template <int MAXN = 1000, int MAXM = 100000>
struct minimum_cost_flow {
	struct cost_flow_edge_list {
		int size, begin[MAXN], dest[MAXM], next[MAXM], cost[MAXM], flow[MAXM];
		void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
		cost_flow_edge_list (int n = MAXN) { clear (n); }
		void add_edge (int u, int v, int c, int f) {
			dest[size] = v; next[size] = begin[u]; cost[size] = c; flow[size] = f; begin[u] = size++;
			dest[size] = u; next[size] = begin[v]; cost[size] = -c; flow[size] = 0; begin[v] = size++; } };
	int n, s, t, prev[MAXN], dist[MAXN], occur[MAXN];
	bool augment (cost_flow_edge_list &e) {
		std::vector <int> queue;
		std::fill (dist, dist + n, INF); std::fill (occur, occur + n, 0);
		dist[s] = 0; occur[s] = true; queue.push_back (s);
		for (int head = 0; head < (int)queue.size(); ++head) {
			int x = queue[head];
			for (int i = e.begin[x]; ~i; i = e.next[i]) {
				int y = e.dest[i];
				if (e.flow[i] && dist[y] > dist[x] + e.cost[i]) {
					dist[y] = dist[x] + e.cost[i]; prev[y] = i;
					if (!occur[y]) {
						occur[y] = true; queue.push_back (y); } } }
			occur[x] = false; }
		return dist[t] < INF; }
	std::pair <int, int> solve (cost_flow_edge_list &e, int n_, int s_, int t_) {
		n = n_; s = s_; t = t_; std::pair <int, int> ans = std::make_pair (0, 0);
		while (augment (e)) {
			int num = INF;
			for (int i = t; i != s; i = e.dest[prev[i] ^ 1])
				num = std::min (num, e.flow[prev[i]]);
			ans.first += num;
			for (int i = t; i != s; i = e.dest[prev[i] ^ 1]) {
				e.flow[prev[i]] -= num; e.flow[prev[i] ^ 1] += num;
				ans.second += num * e.cost[prev[i]]; } }
		return ans; } };
template <int MAXN = 1000, int MAXM = 100000>
struct zkw_flow {
	struct cost_flow_edge_list {
		int size, begin[MAXN], dest[MAXM], next[MAXM], cost[MAXM], flow[MAXM];
		void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
		cost_flow_edge_list (int n = MAXN) { clear (n); }
		void add_edge (int u, int v, int c, int f) {
			dest[size] = v; next[size] = begin[u]; cost[size] = c; flow[size] = f; begin[u] = size++;
			dest[size] = u; next[size] = begin[v]; cost[size] = -c; flow[size] = 0; begin[v] = size++; } };
	int n, s, t, tf, tc, dis[MAXN], slack[MAXN], visit[MAXN];
	int modlable() {
		int delta = INF;
		for (int i = 0; i < n; i++) {
			if (!visit[i] && slack[i] < delta) delta = slack[i];
			slack[i] = INF; }
		if (delta == INF) return 1;
		for (int i = 0; i < n; i++) if (visit[i]) dis[i] += delta;
		return 0; }
	int dfs (cost_flow_edge_list &e, int x, int flow) {
		if (x == t) { tf += flow; tc += flow * (dis[s] - dis[t]); return flow; }
		visit[x] = 1; int left = flow;
		for (int i = e.begin[x]; ~i; i = e.next[i])
			if (e.flow[i] > 0 && !visit[e.dest[i]]) {
				int y = e.dest[i];
				if (dis[y] + e.cost[i] == dis[x]) {
					int delta = dfs (e, y, std::min (left, e.flow[i]));
					e.flow[i] -= delta; e.flow[i ^ 1] += delta; left -= delta;
					if (!left) { visit[x] = false; return flow; }
				} else
					slack[y] = std::min (slack[y], dis[y] + e.cost[i] - dis[x]); }
		return flow - left; }
	std::pair <int, int> solve (cost_flow_edge_list &e, int n_, int s_, int t_) {
		n = n_; s = s_; t = t_; tf = tc = 0;
		std::fill (dis + 1, dis + n + 1, 0);
		do { do {
			std::fill (visit + 1, visit + n + 1, 0);
		} while (dfs (e, s, INF)); } while (!modlable ());
		return std::make_pair (tf, tc);
	} };
