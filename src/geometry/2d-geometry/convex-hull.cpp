bool turn (cp a, cp b, cp c, int s) { return sgn (det (b - a, c - a)) != -s; }
std::pair <std::vector <point>, int> convex_hull (std::vector <point> a) {
	int cnt = 0; std::sort (a.begin (), a.end ());
	static std::vector <point> ret; ret.resize (a.size () << 1);
	for (int i = 0; i < (int) a.size (); ++i) {
		while (cnt > 1 && turn (ret[cnt - 2], a[i], ret[cnt - 1], 1)) --cnt;
		ret[cnt++] = a[i]; }
	int fixed = cnt;
	for (int i = (int) a.size () - 1; i >= 0; --i) {
		while (cnt > fixed && turn (ret[cnt - 2], a[i], ret[cnt - 1], 1)) --cnt;
		ret[cnt++] = a[i]; }
	return std::make_pair (std::vector <point> (ret.begin (), ret.begin () + cnt - 1), fixed - 1); }

int lb (cp x, const std::vector <point> &v, int l, int r, int s) {
	if (l > r) l = r;
	while (l != r) {
		int m = (l + r) / 2;
		if (sgn (det (v[m % v.size ()] - x, v[(m + 1) % v.size ()] - x)) == s) r = m; else l = m + 1; }
	return r % v.size (); }
std::pair <int, int> convex_tan (cp x, const std::vector <point> &v, int rp) {
	if (cmp (x.x, v[0].x) < 0) return std::make_pair (lb (x, v, rp, v.size (), -1), lb (x, v, 0, rp, 1));
	else if (cmp (x.x, v[rp].x) > 0) return std::make_pair (lb (x, v, 0, rp, -1), lb (x, v, rp, v.size (), 1));
	else {
		int id = std::lower_bound (v.begin (), v.begin () + rp, x) - v.begin ();
		if (id == 0 || sgn (det (v[id - 1] - x, v[id] - x)) < 0)
			return std::make_pair (lb (x, v, 0, id, -1), lb (x, v, id, rp, 1));
		id = std::lower_bound (v.begin () + rp, v.end (), x, std::greater <point> ()) - v.begin ();
		if (id == rp || sgn (det (v[id - 1] - x, v[id % v.size ()] - x)) < 0)
			return std::make_pair (lb (x, v, rp, id, -1), lb (x, v, id, v.size (), 1));
		return std::make_pair (-1, -1); } }
