template <int MAXN = 100000, int MAXM = 100000>
struct edge_list {
	int size, begin[MAXN], dest[MAXM], next[MAXM];
	void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
	edge_list (int n = MAXN) { clear (n); }
	void add_edge (int u, int v) { dest[size] = v; next[size] = begin[u]; begin[u] = size++; } };
template <int MAXN = 100000, int MAXM = 100000>
struct cost_edge_list {
	int size, begin[MAXN], dest[MAXM], next[MAXM], cost[MAXM];
	void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
	cost_edge_list (int n = MAXN) { clear (n); }
	void add_edge (int u, int v, int c) { dest[size] = v; next[size] = begin[u]; cost[size] = c; begin[u] = size++; } };

