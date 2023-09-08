point incenter (cp a, cp b, cp c) {
	double p = dis (a, b) + dis (b, c) + dis (c, a);
	return (a * dis (b, c) + b * dis (c, a) + c * dis (a, b)) / p; }
point circumcenter (cp a, cp b, cp c) {
	point p = b - a, q = c - a, s (dot (p, p) / 2, dot (q, q) / 2);
	return a + point (det (s, point (p.y, q.y)), det (point (p.x, q.x), s)) / det (p, q); }
point orthocenter (cp a, cp b, cp c) { return a + b + c - circumcenter (a, b, c) * 2; }

