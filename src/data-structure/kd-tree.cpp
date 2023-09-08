template <int MAXN = 200000, int MAXK = 2>
struct kd_tree {
	int k, size;
	struct point { int data[MAXK], id; } p[MAXN];
	struct kd_node {
		int l, r; point p, dmin, dmax;
		kd_node() {}
		kd_node (const point &rhs) : l (-1), r (-1), p (rhs), dmin (rhs), dmax (rhs) {}
		void merge (const kd_node &rhs, int k) {
			for (register int i = 0; i < k; ++i) {
				dmin.data[i] = std::min (dmin.data[i], rhs.dmin.data[i]);
				dmax.data[i] = std::max (dmax.data[i], rhs.dmax.data[i]); } }
		long long min_dist (const point &rhs, int k) const {
			register long long ret = 0;
			for (register int i = 0; i < k; ++i) {
				if (dmin.data[i] <= rhs.data[i] && rhs.data[i] <= dmax.data[i]) continue;
				ret += std::min (1ll * (dmin.data[i] - rhs.data[i]) * (dmin.data[i] - rhs.data[i]),
								 1ll * (dmax.data[i] - rhs.data[i]) * (dmax.data[i] - rhs.data[i]));
//				ret += std::max (0, rhs.data[i] - dmax.data[i]) + std::max (0, dmin.data[i] - rhs.data[i]);
			} return ret; }
		long long max_dist (const point &rhs, int k) {
			long long ret = 0;
			for (int i = 0; i < k; ++i) {
				int tmp = std::max (std::abs (dmin.data[i] - rhs.data[i]), std::abs (dmax.data[i] - rhs.data[i]));
				ret += 1ll * tmp * tmp; }
//				ret += std::max (std::abs (rhs.data[i] - dmax.data[i]) + std::abs (rhs.data[i] - dmin.data[i])); }
			return ret; } } tree[MAXN * 4];
	struct result {
		long long dist; point d; result() {}
		result (const long long &dist, const point &d) : dist (dist), d (d) {}
		bool operator > (const result &rhs) const { return dist > rhs.dist || (dist == rhs.dist && d.id > rhs.d.id); }
		bool operator < (const result &rhs) const { return dist < rhs.dist || (dist == rhs.dist && d.id < rhs.d.id); } };
	long long sqrdist (const point &a, const point &b) {
		long long ret = 0;
		for (int i = 0; i < k; ++i) ret += 1ll * (a.data[i] - b.data[i]) * (a.data[i] - b.data[i]);
//		for (int i = 0; i < k; ++i) ret += std::abs (a.data[i] - b.data[i]);
		return ret; }
	int alloc() { tree[size].l = tree[size].r = -1; return size++; }
	void build (const int &depth, int &rt, const int &l, const int &r) {
		if (l > r) return;
		register int middle = (l + r) >> 1;
		std::nth_element (p + l, p + middle, p + r + 1, [=] (const point & a, const point & b) { return a.data[depth] < b.data[depth]; });
		tree[rt = alloc()] = kd_node (p[middle]);
		if (l == r) return;
		build ((depth + 1) % k, tree[rt].l, l, middle - 1);
		build ((depth + 1) % k, tree[rt].r, middle + 1, r);
		if (~tree[rt].l) tree[rt].merge (tree[tree[rt].l], k);
		if (~tree[rt].r) tree[rt].merge (tree[tree[rt].r], k); }
	std::priority_queue<result, std::vector<result>, std::less <result>> heap_l;
	std::priority_queue<result, std::vector<result>, std::greater <result>> heap_r;
	void _min_kth (const int &depth, const int &rt, const int &m, const point &d) {
		result tmp = result (sqrdist (tree[rt].p, d), tree[rt].p);
		if ((int)heap_l.size() < m) heap_l.push (tmp);
		else if (tmp < heap_l.top()) {
			heap_l.pop();
			heap_l.push (tmp); }
		int x = tree[rt].l, y = tree[rt].r;
		if (~x && ~y && sqrdist (d, tree[x].p) > sqrdist (d, tree[y].p)) std::swap (x, y);
		if (~x && ((int)heap_l.size() < m || tree[x].min_dist (d, k) < heap_l.top().dist))
			_min_kth ((depth + 1) % k, x, m, d);
		if (~y && ((int)heap_l.size() < m || tree[y].min_dist (d, k) < heap_l.top().dist))
			_min_kth ((depth + 1) % k, y, m, d); }
	void _max_kth (const int &depth, const int &rt, const int &m, const point &d) {
		result tmp = result (sqrdist (tree[rt].p, d), tree[rt].p);
			if ((int)heap_r.size() < m) heap_r.push (tmp);
			else if (tmp > heap_r.top()) {
				heap_r.pop();
				heap_r.push (tmp); }
			int x = tree[rt].l, y = tree[rt].r;
			if (~x && ~y && sqrdist (d, tree[x].p) < sqrdist (d, tree[y].p)) std::swap (x, y);
			if (~x && ((int)heap_r.size() < m || tree[x].max_dist (d, k) >= heap_r.top().dist))
				_max_kth ((depth + 1) % k, x, m, d);
			if (~y && ((int)heap_r.size() < m || tree[y].max_dist (d, k) >= heap_r.top().dist))
				_max_kth ((depth + 1) % k, y, m, d); }
	void init (int n, int k) { this -> k = k; size = 0; int rt = 0; build (0, rt, 0, n - 1); }
	result min_kth (const point &d, const int &m) { heap_l = decltype (heap_l) (); _min_kth (0, 0, m, d); return heap_l.top (); }
	result max_kth (const point &d, const int &m) { heap_r = decltype (heap_r) (); _max_kth (0, 0, m, d); return heap_r.top (); } }; 

