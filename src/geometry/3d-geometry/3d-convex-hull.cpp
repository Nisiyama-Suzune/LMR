template <int MAXN = 500>
struct convex_hull3 {
	double mix (cp3 a, cp3 b, cp3 c) { return dot (det (a, b), c); }
	double volume (cp3 a, cp3 b, cp3 c, cp3 d) { return mix (b - a, c - a, d - a); }
	struct tri {
		int a, b, c; tri() {}
		tri(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
		double area() const { return dis (det (p[b] - p[a], p[c] - p[a])) / 2; }
		point3 normal() const { return det (p[b] - p[a], p[c] - p[a]).unit (); }
		double dis (cp3 p0) const { return dot (normal (), p0 - p[a]); } };
	int n; std::vector <point3> p;
	std::vector <tri> face, tmp;
	int mark[MAXN][MAXN], time;
	void add (int v) {
		++time; tmp.clear ();
		for (int i = 0; i < (int) face.size (); ++i) {
			int a = face[i].a, b = face[i].b, c = face[i].c;
			if (sgn (volume (p[v], p[a], p[b], p[c])) > 0)
				mark[a][b] = mark[b][a] = mark[a][c] = mark[c][a] = mark[b][c] = mark[c][b] = time;
			else tmp.push_back (face[i]); }
		face.clear (); face = tmp;
		for (int i = 0; i < (int) tmp.size (); ++i) {
			int a = face[i].a, b = face[i].b, c = face[i].c;
			if (mark[a][b] == time) face.emplace_back (v, b, a);
			if (mark[b][c] == time) face.emplace_back (v, c, b);
			if (mark[c][a] == time) face.emplace_back (v, a, c); } }
	void reorder () {
		for (int i = 2; i < n; ++i) {
			point3 tmp = det (p[i] - p[0], p[i] - p[1]);
			if (sgn (dis (tmp))) {
				std::swap (p[i], p[2]);
				for (int j = 3; j < n; ++j)
					if (sgn (volume (p[0], p[1], p[2], p[j]))) {
						std::swap (p[j], p[3]); return; } } } }
	void build_convex () {
		reorder (); face.clear ();
		face.emplace_back (0, 1, 2);
		face.emplace_back (0, 2, 1);
		for (int i = 3; i < n; ++i) add(i); } };
