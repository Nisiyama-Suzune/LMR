#include <bits/stdc++.h>

template <int MAXN = 100000, int MAXM = 200000>
struct edge_list {
	int size, begin[MAXN], dest[MAXM], next[MAXM];
	void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
	edge_list (int n = MAXN) { clear (n); }
	void add_edge (int u, int v) { dest[size] = v; next[size] = begin[u]; begin[u] = size++; } };

void euclid (const long long &a, const long long &b, long long &x, long long &y) {
	if (b == 0) x = 1, y = 0;
	else euclid (b, a % b, y, x), y -= a / b * x; }
long long inverse (long long x, long long m) {
	long long a, b; euclid (x, m, a, b); return (a % m + m) % m; }

long long mul_mod (long long x, long long y, long long mod) {
	long long t = (x * y - (long long) ((long double) x / mod * y + 1E-3) * mod) % mod;
	return t < 0 ? t + mod : t; }

template <int MAXN = 100000, int MAXM = 200000, long long MOD = 1000000000000000003ll>
struct tree_hash {
	static long long ra[MAXN];
	tree_hash () {
		std::mt19937_64 mt (time (0));
		std::uniform_int_distribution <long long> uid (0, MOD - 1);
		for (int i = 0; i < MAXN; ++i) ra[i] = uid (mt); }
	struct node {
		std::vector <long long> s; int d1, d2; long long h1, h2;
		node () { d1 = d2 = 0; }
		void add (int d, long long v) {
			s.push_back (v);
			if (d > d1) d2 = d1, d1 = d; else if (d > d2) d2 = d; }
		long long hash () {
			h1 = h2 = 1; for (long long i : s) {
				h1 = mul_mod (h1, ra[d1] + i, MOD);
				h2 = mul_mod (h2, ra[d2] + i, MOD); } return h1; }
	std::pair <int, long long> del (int d, long long v) {
		if (d == d1) return { d2 + 1, mul_mod (h2, inverse (ra[d2] + v, MOD), MOD) };
		return { d1 + 1, mul_mod (h1, inverse (ra[d1] + v, MOD), MOD) }; } };
	std::pair <int, long long> u[MAXN]; node tree[MAXN];
	long long A[MAXN], B[MAXN];
	void dfs1 (const edge_list <MAXN, MAXM> &e, int x, int p = -1) {
		tree[x] = node ();
    	for (int i = e.begin[x]; ~i; i = e.next[i]) {
			int c = e.dest[i]; if (c != p) {
				dfs1 (e, c, x); tree[x].add (tree[c].d1 + 1, tree[c].h1); } }
			A[x] = tree[x].hash (); }
	void dfs2 (const edge_list <MAXN, MAXM> &e, int x, int p = -1) {
		if (~p) tree[x].add (u[x].first, u[x].second);
		B[x] = tree[x].hash ();
  	for (int i = e.begin[x]; ~i; i = e.next[i]) {
			int c = e.dest[i]; if (c != p) {
				u[c] = tree[x].del (tree[c].d1 + 1, tree[c].h1);
				dfs2 (e, c, x); } } }
	void solve (const edge_list <MAXN, MAXM> &e, int root) {
		dfs1 (e, root); dfs2 (e, root); } };
template <int MAXN, int MAXM, long long MOD>
long long tree_hash <MAXN, MAXM, MOD>::ra[MAXN];

edge_list <510000, 1100000> e;
tree_hash <510000, 1100000> th;

const int MOD = 1E9 + 7;

int main () {
	int N; scanf ("%d", &N);
	for (int i = 0; i < N - 1; ++i) {
		int u, v; scanf ("%d%d", &u, &v);
		e.add_edge (u, v); e.add_edge (v, u); }
	th.solve (e, 1);
	int res = 1;
	for (int i = 1; i <= N; ++i) {
		static long long hash[510000]; int size = 0;
		for (int j = e.begin[i]; ~j; j = e.next[j]) { int u = e.dest[j];
			if (th.B[i] == th.B[u] && i < u) res = res * 2 % MOD;
			hash[size++] = th.B[u];
		}
		std::sort (hash, hash + size);
		for (int i = 1, lst = 1; i < size; ++i)
			if (hash[i] == hash[i - 1]) res = 1ll * res * ++lst % MOD;
			else lst = 1;
	}
	printf ("%d\n", res);
}
