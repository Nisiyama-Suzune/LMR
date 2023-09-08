template <int MAXN = 1000000, int MAXM = 1000000>
struct tarjan {
	int comp[MAXN], size;
	int dfn[MAXN], ind, low[MAXN], ins[MAXN], stk[MAXN], stks;
	void dfs (const edge_list <MAXN, MAXM> &e, int i) {
		dfn[i] = low[i] = ind++;
		ins[i] = 1; stk[stks++] = i;
		for (int x = e.begin[i]; ~x; x = e.next[x]) {
			int j = e.dest[x]; if (!~dfn[j]) {
				dfs (e, j);
				if (low[i] > low[j]) low[i] = low[j];
			} else if (ins[j] && low[i] > dfn[j])
				low[i] = dfn[j]; }
		if (dfn[i] == low[i]) {
			for (int j = -1; j != i; j = stk[--stks], ins[j] = 0, comp[j] = size);
			++size; } }
	void solve (const edge_list <MAXN, MAXM> &e, int n) {
		size = ind = stks = 0;
		std::fill (dfn, dfn + n, -1);
		for (int i = 0; i < n; ++i) if (!~dfn[i])
			dfs (e, i); } };
template <int MAXN = 1000000, int MAXM = 1000000>
struct vb_component {
	int comp[MAXM], size;
	int dfn[MAXN], ind, low[MAXN], stk[MAXM], stks;
	void dfs (const edge_list <MAXN, MAXM> &e, int i, int fa) {
		dfn[i] = low[i] = ind++;
		for (int x = e.begin[i]; ~x; x = e.next[x]) {
			int j = e.dest[x]; if (!~dfn[j]) {
				stk[stks++] = x;
				dfs (e, j, i);
				if (low[i] > low[j]) low[i] = low[j];
				if (low[j] >= dfn[i]) {
					for (int j = -1; j != x;
						j = stk[--stks], comp[j] = comp[j ^ 1] = size);
					++size; }
			} else if (j != fa && dfn[j] < dfn[i]) {
				stk[stks++] = x;
				if (low[i] > dfn[j]) low[i] = dfn[j]; } } }
	void solve (const edge_list <MAXN, MAXM> &e, int n) {
		size = ind = stks = 0;
		std::fill (dfn, dfn + n, -1);
		for (int i = 0; i < n; ++i) if (!~dfn[i])
			dfs (e, i, -1); } };
template <int MAXN = 1000000, int MAXM = 1000000>
struct eb_component {
	int comp[MAXN], size;
	int dfn[MAXN], ind, low[MAXN], stk[MAXM], stks;
	void dfs (const edge_list <MAXN, MAXM> &e, int i, int fa) {
		dfn[i] = low[i] = ind++; stk[stks++] = i;
		for (int x = e.begin[i]; ~x; x = e.next[x]) {
			int j = e.dest[x]; if (!~dfn[j]) {
				dfs (e, j, i);
				if (low[i] > low[j]) low[i] = low[j];
			} else if (j != fa && low[i] > dfn[j]) low[i] = dfn[j]; }
		if (dfn[i] <= low[i]) {
			for (int j = -1; j != i; j = stk[--stks], comp[j] = size);
			++size; } }
	void solve (const edge_list <MAXN, MAXM> &e, int n) {
		size = ind = stks = 0;
		std::fill (dfn, dfn + n, -1);
		for (int i = 0; i < n; ++i) if (!~dfn[i])
			dfs (e, i, -1); } };
