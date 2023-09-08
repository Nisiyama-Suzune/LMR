template <int MAXN = 1000000, int MAXC = 26>
struct palindromic_tree {
	struct node {
		node *child[MAXC], *fail; int len;
		node (int len) : fail (NULL), len (len) {
			memset (child, NULL, sizeof (child)); }
	} node_pool[MAXN * 2], *tot_node;
	int size, text[MAXN];
	node *odd, *even, *last;
	node *match (node *now) {
		for (; text[size - now -> len - 1] != text[size]; now = now -> fail);
		return now; }
	bool extend (int token) {
		text[++size] = token; node *now = match (last);
		if (now -> child[token])
			return last = now -> child[token], false;
		last = now -> child[token] = new (tot_node++) node (now -> len + 2);
		if (now == odd) last -> fail = even;
		else {
			now = match (now -> fail);
			last -> fail = now -> child[token]; }
		return true; }
	void init() {
		text[size = 0] = -1; tot_node = node_pool;
		last = even = new (tot_node++) node (0); odd = new (tot_node++) node (-1);
		even -> fail = odd; }
	palindromic_tree () { init (); } };

