#define cp const point &
struct point {
	double x, y;
	explicit point (cd x = 0, cd y = 0) : x (x), y (y) {}
	int dim () const { return sgn (y) == 0 ? sgn (x) > 0 : sgn (y) > 0; }
	point unit () const { double l = msqrt (x * x + y * y); return point (x / l, y / l); }
	point rot90 () const { return point (-y, x); }
	point _rot90 () const { return point (y, -x); }
	point rot (cd t) const {
		double c = cos (t), s = sin (t);
		return point (x * c - y * s, x * s + y * c); } };
bool operator == (cp a, cp b) { return cmp (a.x, b.x) == 0 && cmp (a.y, b.y) == 0; }
bool operator != (cp a, cp b) { return cmp (a.x, b.x) != 0 || cmp (a.y, b.y) != 0; }
bool operator < (cp a, cp b) { return cmp (a.x, b.x) == 0 ? cmp (a.y, b.y) < 0 : cmp (a.x, b.x) < 0; }
point operator - (cp a) { return point (-a.x, -a.y); }
point operator + (cp a, cp b) { return point (a.x + b.x, a.y + b.y); }
point operator - (cp a, cp b) { return point (a.x - b.x, a.y - b.y); }
point operator * (cp a, cd b) { return point (a.x * b, a.y * b); }
point operator / (cp a, cd b) { return point (a.x / b, a.y / b); }
double dot (cp a, cp b) { return a.x * b.x + a.y * b.y; }
double det (cp a, cp b) { return a.x * b.y - a.y * b.x; }
double dis2 (cp a, cp b = point ()) { return sqr (a.x - b.x) + sqr (a.y - b.y); }
double dis (cp a, cp b = point ()) { return msqrt (dis2 (a, b)); }
#define cl const line &
struct line {
	point s, t;
	explicit line (cp s = point (), cp t = point ()) : s (s), t (t) {} };
bool point_on_segment (cp a, cl b) { return sgn (det (a - b.s, b.t - b.s)) == 0 && sgn (dot (b.s - a, b.t - a)) <= 0; }
bool two_side (cp a, cp b, cl c) { return sgn (det (a - c.s, c.t - c.s)) * sgn (det (b - c.s, c.t - c.s)) < 0; }
bool intersect_judgment (cl a, cl b) {
	if (point_on_segment (b.s, a) || point_on_segment (b.t, a)) return true;
	if (point_on_segment (a.s, b) || point_on_segment (a.t, b)) return true;
	return two_side (a.s, a.t, b) && two_side (b.s, b.t, a); }
point line_intersect (cl a, cl b) {
	double s1 = det (a.t - a.s, b.s - a.s), s2 = det (a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
double point_to_line (cp a, cl b) { return std::abs (det (b.t - b.s, a - b.s)) / dis (b.s, b.t); }
point project_to_line (cp a, cl b) { return b.s + (b.t - b.s) * (dot (a - b.s, b.t - b.s) / dis2 (b.t, b.s)); }
double point_to_segment (cp a, cl b) {
	if (sgn (dot (b.s - a, b.t - b.s) * dot (b.t - a, b.t - b.s)) <= 0) return std::abs (det (b.t - b.s, a - b.s)) / dis (b.s, b.t);
	return std::min (dis (a, b.s), dis (a, b.t)); }
bool in_polygon (cp p, const std::vector <point> & po) {
	int n = (int) po.size (), counter = 0;
	for (int i = 0; i < n; ++i) {
		point a = po[i], b = po[(i + 1) % n];
		// Modify the next line if necessary.
		if (point_on_segment (p, line (a, b))) return true;
		int x = sgn (det (p - a, b - a)), y = sgn (a.y - p.y), z = sgn (b.y - p.y);
		if (x > 0 && y <= 0 && z > 0) counter++;
		if (x < 0 && z <= 0 && y > 0) counter--; }
	return counter != 0; }
double polygon_area (const std::vector <point> &a) {
	double ans = 0.0;
	for (int i = 0; i < (int) a.size (); ++i) ans += det (a[i], a[ (i + 1) % a.size ()]) / 2.0;
	return ans; }
#define cc const circle &
struct circle {
	point c; double r;
	explicit circle (point c = point (), double r = 0) : c (c), r (r) {} };
bool operator == (cc a, cc b) { return a.c == b.c && cmp (a.r, b.r) == 0; }
bool operator != (cc a, cc b) { return !(a == b); }
bool in_circle (cp a, cc b) { return cmp (dis (a, b.c), b.r) <= 0; }
circle make_circle (cp a, cp b) { return circle ((a + b) / 2, dis (a, b) / 2); }
circle make_circle (cp a, cp b, cp c) { point p = circumcenter (a, b, c); return circle (p, dis (p, a)); }
std::vector <point> line_circle_intersect (cl a, cc b) {
	if (cmp (point_to_line (b.c, a), b.r) > 0) return std::vector <point> ();
	double x = msqrt (sqr (b.r) - sqr (point_to_line (b.c, a)));
	point s = project_to_line (b.c, a), u = (a.t - a.s).unit ();
	if (sgn (x) == 0) return std::vector <point> ({s});
	return std::vector <point> ({s - u * x, s + u * x}); }
double circle_intersect_area (cc a, cc b) {
	double d = dis (a.c, b.c);
	if (sgn (d - (a.r + b.r)) >= 0) return 0;
	if (sgn (d - std::abs(a.r - b.r)) <= 0) {
		double r = std::min (a.r, b.r); return r * r * PI; }
	double x = (d * d + a.r * a.r - b.r * b.r) / (2 * d), t1 = acos (std::min (1., std::max (-1., x / a.r))), t2 = acos (std::min (1., std::max (-1., (d - x) / b.r)));
	return a.r * a.r * t1 + b.r * b.r * t2 - d * a.r * sin (t1); }
std::vector <point> circle_intersect (cc a, cc b) {
	if (a.c == b.c || cmp (dis (a.c, b.c), a.r + b.r) > 0 || cmp (dis (a.c, b.c), std::abs (a.r - b.r)) < 0) return std::vector <point> ();
	point r = (b.c - a.c).unit (); double d = dis (a.c, b.c);
	double x = ((sqr (a.r) - sqr (b.r)) / d + d) / 2, h = msqrt (sqr (a.r) - sqr (x));
	if (sgn (h) == 0) return std::vector <point> ({a.c + r * x});
	return std::vector <point> ({a.c + r * x - r.rot90 () * h, a.c + r * x + r.rot90 () * h}); }
std::vector <point> tangent (cp a, cc b) { circle p = make_circle (a, b.c); return circle_intersect (p, b); }
std::vector <line> extangent (cc a, cc b) {
	std::vector <line> ret;
	if (cmp (dis (a.c, b.c), std::abs (a.r - b.r)) <= 0) return ret;
	if (sgn (a.r - b.r) == 0) {
		point dir = b.c - a.c; dir = (dir * a.r / dis (dir)).rot90 ();
		ret.push_back (line (a.c - dir, b.c - dir));
		ret.push_back (line (a.c + dir, b.c + dir));
	} else {
		point p = (b.c * a.r - a.c * b.r) / (a.r - b.r);
		std::vector <point> pp = tangent (p, a), qq = tangent (p, b);
		if (pp.size () == 2 && qq.size () == 2) {
			if (cmp (a.r, b.r) < 0) std::swap (pp[0], pp[1]), std::swap (qq[0], qq[1]);
			ret.push_back (line (pp[0], qq[0]));
			ret.push_back (line (pp[1], qq[1])); } }
	return ret; }
std::vector <line> intangent (cc a, cc b) {
	std::vector <line> ret;
	point p = (b.c * a.r + a.c * b.r) / (a.r + b.r);
	std::vector <point> pp = tangent (p, a), qq = tangent (p, b);
	if (pp.size () == 2 && qq.size () == 2) {
		ret.push_back (line (pp[0], qq[0]));
		ret.push_back (line (pp[1], qq[1])); }
	return ret; }
