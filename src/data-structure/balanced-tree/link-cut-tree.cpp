struct Node { int son[2], fa, num, pos, rev; } node[maxn];
int n, m, ans, top, q[maxn];
inline bool root (int x) { return node[node[x].fa].son[0] != x && node[node[x].fa].son[1] != x; }
void update (int x) {
	int left = node[x].son[0], right = node[x].son[1]; node[x].pos = x;
	if (node[node[left].pos].num > node[node[x].pos].num) node[x].pos = node[left].pos;
	if (node[node[right].pos].num > node[node[x].pos].num) node[x].pos = node[right].pos; }
void down (int x) {
	int left = node[x].son[0], right = node[x].son[1];
	if (node[x].rev) { node[x].rev ^= 1; node[left].rev ^= 1; node[right].rev ^= 1;
		std::swap (node[x].son[0], node[x].son[1]); } }
void rotate (int x) {
	int y = node[x].fa, z = node[y].fa, left, right;
	if (node[y].son[0] == x) left = 0; else left = 1;
	right = left ^ 1; if (!root (y)) {
		if (node[z].son[0] == y) node[z].son[0] = x; else node[z].son[1] = x; }
	node[x].fa = z; node[y].fa = x;
	if (node[x].son[right] != 0) node[node[x].son[right]].fa = y;
	node[y].son[left] = node[x].son[right]; node[x].son[right] = y;
	update (y); update (x); }
void splay (int x) {
	top = 0; q[++top] = x;
	for (int i = x; !root (i); i = node[i].fa) q[++top] = node[i].fa;
	for (int i = top; i; i--) down (q[i]);
	while (!root (x)) { int y = node[x].fa, z = node[y].fa; if (!root (y)) {
		if (node[y].son[0] == x ^ node[z].son[0] == y) rotate (x);
		else rotate (y); } rotate (x); } update (x); }
void access (int x) { int t = 0; while (x) { splay (x); node[x].son[1] = t; t = x; x = node[x].fa; } }
void makeroot (int x) { access (x); splay (x); node[x].rev ^= 1; }
void link (int x, int y) { makeroot (x); node[x].fa = y; }
void cut (int x, int y) { makeroot (x); access (y); splay (y); node[node[y].son[0]].fa = 0; node[y].son[0] = 0; update (y); }
