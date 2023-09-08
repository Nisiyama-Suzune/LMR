#include <bits/stdc++.h>

const double EPS = 1E-8, INF = 1E300;
template <int MAXN = 100, int MAXM = 100>
struct simplex {
	int n, m; double a[MAXM][MAXN], b[MAXM], c[MAXN];
	bool infeasible, unbounded;
	double v, an[MAXN + MAXM]; int q[MAXN + MAXM];
	void pivot (int l, int e) {
		std::swap (q[e], q[l + n]); 
		double t = a[l][e]; a[l][e] = 1; b[l] /= t;
		for (int i = 0; i < n; ++i) a[l][i] /= t;
		for (int i = 0; i < m; ++i) if (i != l && std::abs (a[i][e]) > EPS) {
			t = a[i][e]; a[i][e] = 0; b[i] -= t * b[l];	
			for (int j = 0; j < n; ++j) a[i][j] -= t * a[l][j]; }
		if (std::abs (c[e]) > EPS) {
			t = c[e]; c[e] = 0; v += t * b[l];	
			for (int j = 0; j < n; ++j) c[j] -= t * a[l][j]; } }
	bool pre () {
		for (int l, e; ; ) {
			l = e = -1;
			for (int i = 0; i < m; ++i) if (b[i] < -EPS && (!~l || rand () & 1)) l = i;
			if (!~l) break;
			for (int i = 0; i < n; ++i) if (a[l][i] < -EPS && (!~e || rand () & 1)) e = i;
			if (!~e) return infeasible = true;
			pivot (l, e); }
		return false; }
	double solve () {
		double p; std::fill (q, q + n + m, -1);
		for (int i = 0; i < n; ++i) q[i] = i;
		v = 0; infeasible = unbounded = false;
		if (pre ()) return 0;
		for (int l, e; ; pivot (l, e)) {
			l = e = -1; for (int i = 0; i < n; ++i) if (c[i] > EPS) { e = i; break; }
			if (!~e) break; p = INF; 
			for (int i = 0; i < m; ++i) if (a[i][e] > EPS && p > b[i] / a[i][e])
				p = b[i] / a[i][e], l = i;
			if (!~l) return unbounded = true, 0; }
		for (int i = n; i < n + m; ++i) if (~q[i]) an[q[i]] = b[i - n];
		return v;
	} };

simplex <> s;
int t;

int main () {
	std::ios::sync_with_stdio (0);
	std::cin >> s.n >> s.m >> t;
	for (int i = 0; i < s.n; ++i) std::cin >> s.c[i];
	for (int i = 0; i < s.m; ++i) {
		for (int j = 0; j < s.n; ++j) std::cin >> s.a[i][j];
		std::cin >> s.b[i];
	}
	for (int i = 0; i < s.n; ++i) s.a[s.m++][i] = -1;
	double res = s.solve ();
	if (s.infeasible) std::cout << "Infeasible\n";
	else if (s.unbounded) std::cout << "Unbounded\n";
	else {
		std::cout << std::fixed << std::setprecision (10) << res << "\n";
		if (t) for (int i = 0; i < s.n; ++i) std::cout << s.an[i] << " \n"[i + 1 == s.n];
	}
	return 0;
}

