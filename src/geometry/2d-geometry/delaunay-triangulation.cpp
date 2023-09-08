const int N = 100000 + 5, MAX_TRIS = N * 6;
bool in_circumcircle (cp p1, cp p2, cp p3, cp p4) {
	double u11 = p1.x - p4.x, u21 = p2.x - p4.x, u31 = p3.x - p4.x;
	double u12 = p1.y - p4.y, u22 = p2.y - p4.y, u32 = p3.y - p4.y;
	double u13 = sqr (p1.x) - sqr (p4.x) + sqr (p1.y) - sqr (p4.y);
	double u23 = sqr (p2.x) - sqr (p4.x) + sqr (p2.y) - sqr (p4.y);
	double u33 = sqr (p3.x) - sqr (p4.x) + sqr (p3.y) - sqr (p4.y);
	double det = -u13 * u22 * u31 + u12 * u23 * u31 + u13 * u21 * u32 - u11 * u23 * u32 - u12 * u21 * u33 + u11 * u22 * u33;
	return sgn (det) > 0; }
double side (cp a, cp b, cp p) { return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x); }
typedef int side_t; struct tri; typedef tri* tri_r;
struct edge {
	tri_r t; side_t side;
	edge (tri_r t = 0, side_t side = 0) : t(t), side(side) {} };
struct tri {
	point p[3]; edge e[3]; tri_r child[3]; tri () {}
	tri (cp p0, cp p1, cp p2) { p[0] = p0; p[1] = p1; p[2] = p2;
		child[0] = child[1] = child[2] = 0; }
	bool has_child() const { return child[0] != 0; }
	int num_child() const { return child[0] == 0 ? 0 : child[1] == 0 ? 1 : child[2] == 0 ? 2 : 3; }
	bool contains (cp q) const {
		double a = side (p[0], p[1], q), b = side(p[1], p[2], q), c = side(p[2], p[0], q);
		return sgn (a) >= 0 && sgn (b) >= 0 && sgn (c) >= 0; } };
void set_edge (edge a, edge b) {
	if (a.t) a.t -> e[a.side] = b;
	if (b.t) b.t -> e[b.side] = a; }
class trig {
	public:
		tri tpool[MAX_TRIS], *tot;
		trig() { const double LOTS = 1E6;
			the_root = new (tot++) tri (point (-LOTS, -LOTS), point (LOTS, -LOTS), point (0, LOTS)); }
		tri_r find (cp p) const { return find (the_root, p); }
		void add_point (cp p) { add_point (find (the_root, p), p); }
	private:
		tri_r the_root;
		static tri_r find (tri_r root, cp p) {
			for(; ; ) { if (!root -> has_child ()) return root;
				else for (int i = 0; i < 3 && root -> child[i]; ++i)
					if (root -> child[i] -> contains (p))
						{ root = root->child[i]; break; } } }
		void add_point (tri_r root, cp p) {
			tri_r tab, tbc, tca;
			tab = new (tot++) tri (root -> p[0], root -> p[1], p);
			tbc = new (tot++) tri (root -> p[1], root -> p[2], p);
			tca = new (tot++) tri (root -> p[2], root -> p[0], p);
			set_edge (edge (tab, 0), edge (tbc, 1)); set_edge (edge (tbc, 0), edge (tca, 1));
			set_edge (edge (tca, 0), edge (tab, 1)); set_edge (edge (tab, 2), root -> e[2]);
			set_edge (edge (tbc, 2), root -> e[0]); set_edge (edge (tca, 2), root -> e[1]);
			root -> child[0] = tab; root -> child[1] = tbc; root -> child[2] = tca;
			flip (tab, 2); flip (tbc, 2); flip (tca, 2); }
		void flip (tri_r t, side_t pi) {
			tri_r trj = t -> e[pi].t; int pj = t -> e[pi].side;
			if(!trj || !in_circumcircle (t -> p[0], t -> p[1], t -> p[2], trj -> p[pj])) return;
			tri_r trk = new (tot++) tri (t -> p[(pi + 1) % 3], trj -> p[pj], t -> p[pi]);
			tri_r trl = new (tot++) tri (trj -> p[(pj + 1) % 3], t -> p[pi], trj -> p[pj]);
			set_edge (edge (trk, 0), edge (trl, 0));
			set_edge (edge (trk, 1), t -> e[(pi + 2) % 3]); set_edge (edge (trk, 2), trj -> e[(pj + 1) % 3]);
			set_edge (edge (trl, 1), trj -> e[(pj + 2) % 3]); set_edge (edge (trl, 2), t -> e[(pi + 1) % 3]);
			t -> child[0] = trk; t -> child[1] = trl; t -> child[2] = 0;
			trj -> child[0] = trk; trj -> child[1] = trl; trj -> child[2] = 0;
			flip (trk, 1); flip (trk, 2); flip (trl, 1); flip (trl, 2); } };
void build (std::vector <point> ps, trig &t) {
	t.tot = t.tpool; std::random_shuffle (ps.begin (), ps.end ());
	for (point &p : ps) t.add_point (p); }

