template <int MAXN = 500>
struct stoer_wagner {
	int n, edge[MAXN][MAXN];
	int dist[MAXN];
	bool vis[MAXN], bin[MAXN];
	stoer_wagner () {
		memset (edge, 0, sizeof (edge));
		memset (bin, false, sizeof (bin)); }
	int contract (int &s, int &t)  {
		memset (dist, 0, sizeof (dist));
		memset (vis, false, sizeof (vis));
		int i, j, k, mincut, maxc;
		for (i = 1; i <= n; i++) {
			k = -1; maxc = -1;
			for (j = 1; j <= n; j++)
				if (!bin[j] && !vis[j] && dist[j] > maxc) {
					k = j; maxc = dist[j]; }
			if (k == -1) return mincut;
			s = t; t = k; mincut = maxc; vis[k] = true;
			for (j = 1; j <= n; j++) if (!bin[j] && !vis[j])
				dist[j] += edge[k][j]; }
		return mincut; }
	int solve () {
		int mincut, i, j, s, t, ans;
		for (mincut = INF, i = 1; i < n; i++) {
			ans = contract (s, t); bin[t] = true;
			if (mincut > ans) mincut = ans;
			if (mincut == 0) return 0;
			for (j = 1; j <= n; j++) if (!bin[j])
				edge[s][j] = (edge[j][s] += edge[j][t]); }
		return mincut; } };

