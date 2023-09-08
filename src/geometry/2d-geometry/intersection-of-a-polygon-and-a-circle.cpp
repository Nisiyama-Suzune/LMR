struct polygon_circle_intersect {
	double sector_area (cp a, cp b, const double &r) {
		double c = (2.0 * r * r - dis2 (a, b)) / (2.0 * r * r);
		return r * r * acos (c) / 2.0; }
	double area (cp a, cp b, const double &r) {
		double dA = dot (a, a), dB = dot (b, b), dC = point_to_segment (point (), line (a, b));
		if (sgn (dA - r * r) <= 0 && sgn (dB - r * r) <= 0) return det (a, b) / 2.0;
		point tA = a.unit () * r, tB = b.unit () * r;
		if (sgn (dC - r) > 0) return sector_area (tA, tB, r);
		std::vector <point> ret = line_circle_intersect (line (a, b), circle (point (), r));
		if (sgn (dA - r * r) > 0 && sgn (dB - r * r) > 0) 
			return sector_area (tA, ret[0], r) + det (ret[0], ret[1]) / 2.0 + sector_area (ret[1], tB, r);
		if (sgn (dA - r * r) > 0) return det (ret[0], b) / 2.0 + sector_area (tA, ret[0], r);
		else return det (a, ret[1]) / 2.0 + sector_area (ret[1], tB, r); }
	double solve (const std::vector <point> &p, cc c) {
		double ret = 0.0;
		for (int i = 0; i < (int) p.size (); ++i) {
			int s = sgn (det (p[i] - c.c, p[(i + 1) % p.size ()] - c.c));
			if (s > 0) ret += area (p[i] - c.c, p[(i + 1) % p.size ()] - c.c, c.r);
			else ret -= area (p[(i + 1) % p.size ()] - c.c, p[i] - c.c, c.r); }
		return std::abs (ret); } };

