struct perm {
	std::vector <int> P; perm () {} perm (int n) { P.resize (n); }
	perm inv () const {
		perm ret (P.size ()); for (int i = 0; i < int (P.size ()); ++i) ret.P[P[i]] = i;
		return ret; }
	int &operator [] (const int &dn) { return P[dn]; }
	void resize (const size_t &sz) { P.resize (sz); }
	size_t size () const { return P.size (); }
	const int &operator [] (const int &dn) const { return P[dn]; } };
perm operator * (const perm &a, const perm &b) {
	perm ret (a.size ()); for (int i = 0; i < (int) a.size (); ++i) ret[i] = b[a[i]];
	return ret; }
typedef std::vector <perm> bucket;
typedef std::vector <int> table;
typedef std::pair <int, int> pii;
int n, m;
std::vector <bucket> buckets, buckets_i; std::vector <table> lookup_table;
int fast_filter (const perm &g, bool add = true) {
	int n = buckets.size (); perm p (g);
	for (int i = 0; i < n; ++i) {
		int res = lookup_table[i][p[i]];
		if (res == -1) {
			if (add) {
				buckets[i].push_back (p);
				buckets_i[i].push_back (p.inv ());
				lookup_table[i][p[i]] = (int) buckets[i].size () - 1; }
			return i; }
		p = p * buckets_i[i][res]; }
	return -1; }
long long calc_total_size () { long long res = 1; for (int i = 0; i < n; ++i) res *= buckets[i].size (); return res; }
bool in_group (const perm &g) { return fast_filter (g, false) == -1; }
void solve (const bucket &gen, int _n) {
	n = _n, m = gen.size ();
	std::vector <bucket>  _buckets (n); std::swap (buckets, _buckets);
	std::vector <bucket>  _buckets_i (n); std::swap (buckets_i, _buckets_i);
	std::vector <table>  _lookup_table (n); std::swap (lookup_table, _lookup_table);
	for (int i = 0; i < n; ++i) {
		lookup_table[i].resize (n);
		std::fill (lookup_table[i].begin (), lookup_table[i].end (), -1); }
	perm id (n);
	for (int i = 0; i < n; ++i) id[i] = i;
	for (int i = 0; i < n; ++i) {
		buckets[i].push_back (id); buckets_i[i].push_back (id);
		lookup_table[i][i] = 0; }
	for (int i = 0; i < m; ++i) fast_filter (gen[i]);
	std::queue <std::pair <pii, pii>> toUpdate;
	for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j)
		for (int k = 0; k < (int) buckets[i].size (); ++k) for (int l = 0; l < (int) buckets[j].size (); ++l)
			toUpdate.push (std::make_pair (pii (i, k), pii (j, l)));
	while (!toUpdate.empty ()) {
		pii a = toUpdate.front ().first, b = toUpdate.front ().second; toUpdate.pop ();
		int res = fast_filter (buckets[a.first][a.second] * buckets[b.first][b.second]);
		if (res == -1) continue;
		pii newPair (res, (int) buckets[res].size () - 1);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < (int) buckets[i].size (); ++j) {
				if (i <= res) toUpdate.push (std::make_pair (pii (i, j), newPair));
				if (res <= i) toUpdate.push (std::make_pair (newPair, pii (i, j))); } } }
