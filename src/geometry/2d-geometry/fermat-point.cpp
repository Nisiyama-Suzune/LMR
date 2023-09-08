point fermat_point (cp a, cp b, cp c) {
	if (a == b) return a; if (b == c) return b; if (c == a) return c;
	double ab = dis (a, b), bc = dis (b, c), ca = dis (c, a);
	double cosa = dot (b - a, c - a) / ab / ca;
	double cosb = dot (a - b, c - b) / ab / bc;
	double cosc = dot (b - c, a - c) / ca / bc;
	double sq3 = PI / 3.0; point mid;
	if (sgn (cosa + 0.5) < 0) mid = a;
	else if (sgn (cosb + 0.5) < 0) mid = b;
	else if (sgn (cosc + 0.5) < 0) mid = c;
	else if (sgn (det (b - a, c - a)) < 0) mid = line_intersect (line (a, b + (c - b).rot (sq3)), line (b, c + (a - c).rot (sq3)));
	else mid = line_intersect (line (a, c + (b - c).rot (sq3)), line (c, b + (a - b).rot (sq3)));
	return mid; }

