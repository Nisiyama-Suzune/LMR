const int maxn = 1005, maxe = 10005, maxm = maxe * 30;
struct A {
	int x, d;
	A (int x, int d) : x (x), d (d) {}
	bool operator < (const A &a) const { return d > a.d; } };
struct node {
	int w, i, d;
	node *lc, *rc;
	node () {}
	node (int w, int i) : w (w), i (i), d (0) {}
	void refresh () { d = rc -> d + 1; }
} null[maxm], *ptr = null, *root[maxn];
struct B {
	int x, w;
	node *rt;
	B (int x, node *rt, int w) : x (x), w (w), rt (rt) {}
	bool operator < (const B &a) const { return w + rt -> w > a.w + a.rt -> w; } };
std::vector <int> G[maxn], W[maxn], id[maxn]; // Store reversed graph & clear G at the beginning.
bool vis[maxn], used[maxe];
int u[maxe], v[maxe], w[maxe]; // Store every edge (uni-directional).
int d[maxn], p[maxn];
int n, m, k, s, t; // s, t - beginning and end.
// main
for (int i = 0; i <= n; i++) root[i] = null;
//Read & build the reversed graph.
Dijkstra ();
// Clear G, W, id.
for (int i = 1; i <= n; i++)
	if (p[i]) { used[p[i]] = true; G[v[p[i]]].push_back (i); }
for (int i = 1; i <= m; i++) {
	w[i] -= d[u[i]] - d[v[i]];
	if (!used[i]) root[u[i]] = merge (root[u[i]], newnode (w[i], i)); }
dfs (t);
std::priority_queue <B> heap;
heap.push (B (s, root[s], 0));
printf ("%d\n", d[s]); // The shortest path.
while (--k) {
	if (heap.empty ()) printf("-1\n");
	else {
		int x = heap.top ().x, w = heap.top ().w;
		node *rt = heap.top ().rt; heap.pop ();
		printf ("%d\n", d[s] + w + rt -> w);
		if (rt -> lc != null || rt -> rc != null)
			heap.push (B (x, merge (rt -> lc, rt -> rc), w));
		if (root[v[rt -> i]] != null)
			heap.push (B (v[rt -> i], root[v[rt -> i]], w + rt -> w)); } }
void Dijkstra () {
	memset (d, 63, sizeof (d)); d[t] = 0;
	std::priority_queue <A> heap;
	heap.push (A (t, 0));
	while (!heap.empty ()) {
		int x = heap.top ().x; heap.pop ();
		if (vis[x]) continue; vis[x] = true;
		for (int i = 0; i < (int) G[x].size (); i++)
			if (!vis[G[x][i]] && d[G[x][i]] > d[x] + W[x][i]) {
				d[G[x][i]] = d[x] + W[x][i];
				p[G[x][i]] = id[x][i];
				heap.push (A (G[x][i], d[G[x][i]])); } } }
void dfs (int x) {
	root[x] = merge (root[x], root[v[p[x]]]);
	for (int i = 0; i < (int) G[x].size (); i++) dfs (G[x][i]); }
node *newnode (int w, int i) {
	*++ptr = node (w, i);
	ptr -> lc = ptr -> rc = null;
	return ptr; }
node *merge (node *x, node *y) {
	if (x == null) return y;
	if (y == null) return x;
	if (x -> w > y -> w) swap (x, y);
	node *z = newnode (x -> w, x -> i);
	z -> lc = x -> lc; z -> rc = merge (x -> rc, y);
	if (z -> lc -> d > z -> rc -> d) swap (z -> lc, z -> rc);
	z -> refresh (); return z; }
