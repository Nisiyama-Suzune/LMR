double solve (std::vector <point> &p, int l, int r) { 
	if (l + 1 >= r) return INF;
	int m = (l + r) / 2; double mx = p[m].x; std::vector <point> v;
	double ret = std::min (solve(p, l, m), solve(p, m, r));
	for (int i = l; i < r; ++i)
		if (sqr (p[i].x - mx) < ret) v.push_back (p[i]);
	sort (v.begin (), v.end (), [&] (cp a, cp b) { return a.y < b.y; } );
	for (int i = 0; i < v.size (); ++i)
		for (int j = i + 1; j < v.size (); ++j) {
			if (sqr (v[i].y - v[j].y) > ret) break;
			ret = min (ret, dis2 (v[i] - v[j])); }
	return ret; }
