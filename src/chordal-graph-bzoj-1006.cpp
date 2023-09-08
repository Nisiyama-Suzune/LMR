#include <bits/stdc++.h>

template <int MAXN = 100000, int MAXM = 100000>
struct edge_list {
	int size, begin[MAXN], dest[MAXM], next[MAXM];
	void clear (int n) { size = 0; std::fill (begin, begin + n, -1); }
	edge_list (int n = MAXN) { clear (n); }
	void add_edge (int u, int v) { dest[size] = v; next[size] = begin[u]; begin[u] = size++; } };

struct point {
	int lab, u;
	point (int lab = 0, int u = 0) : lab (lab), u (u) {}
	bool operator < (const point &a) const { return lab < a.lab; } };

template <int MAXN = 100000, int MAXM = 100000>
struct chordal_graph {
	int n; edge_list <MAXN, MAXM> e;
	int id[MAXN], seq[MAXN];
	void init () {
		std::fill (id, id + n, -1);
		static int label[MAXN]; std::fill (label, label + n, 0);
		std::priority_queue <point> q;
		for (int i = 0; i < n; ++i) q.push (point (0, i));
		for (int i = n - 1; i >= 0; --i) {
			for (; ~id[q.top ().u]; ) q.pop ();
			int u = q.top ().u; q.pop (); id[u] = i;
			for (int j = e.begin[u], v; ~j; j = e.next[j])
				if (v = e.dest[j], !~id[v]) ++label[v], q.push (point (label[v], v)); }
		for (int i = 0; i < n; ++i) seq[id[i]] = i; }
	bool is_chordal () {
		static int vis[MAXN], q[MAXN]; std::fill (vis, vis + n, -1);
		for (int i = n - 1; i >= 0; --i) {
			int u = seq[i], t = 0, v;
			for (int j = e.begin[u]; ~j; j = e.next[j])
				if (v = e.dest[j], id[v] > id[u]) q[t++] = v;
			if (!t) continue; int w = q[0];
			for (int j = 0; j < t; ++j) if (id[q[j]] < id[w]) w = q[j];
			for (int j = e.begin[w]; ~j; j = e.next[j]) vis[e.dest[j]] = i;
			for (int j = 0; j < t; ++j) if (q[j] != w && vis[q[j]] != i) return 0;
		}
		return 1; }
	int min_color () {
		int res = 0;
		static int vis[MAXN], c[MAXN];
		std::fill (vis, vis + n, -1);
		std::fill (c, c + n, n);
		for (int i = n - 1; i >= 0; --i) {
			int u = seq[i];
			for (int j = e.begin[u]; ~j; j = e.next[j]) vis[c[e.dest[j]]] = i;
			int k; for (k = 0; vis[k] == i; ++k);
			c[u] = k; res = std::max (res, k + 1);
		}
		return res; } };

int N, M;
chordal_graph <11000, 2100000> ch;

int main () {
	std::ios::sync_with_stdio (0);
	std::cin >> N >> M;
	ch.n = N;
	for (int i = 0; i < M; ++i) {
		int u, v; std::cin >> u >> v;
		ch.e.add_edge (u - 1, v - 1);
		ch.e.add_edge (v - 1, u - 1);
	}
	ch.init ();
	assert (ch.is_chordal ());
	std::cout << ch.min_color () << "\n";
}
