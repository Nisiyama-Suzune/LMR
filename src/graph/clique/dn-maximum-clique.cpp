typedef bool BB[N]; struct max_clique {
const BB *e; int pk, level; const float Tlimit;
struct vertex { int i, d; vertex (int i) : i(i), d(0) {} };
typedef std::vector <vertex> vertices; vertices V;
typedef std::vector <int> colors; colors QMAX, Q;
std::vector <colors> C;
static bool desc_degree (const vertex &vi,const vertex &vj) { return vi.d > vj.d; }
void init_colors (vertices &v) {
	const int max_degree = v[0].d;
	for (int i = 0; i < (int) v.size(); ++i) v[i].d = std::min (i, max_degree) + 1; }
void set_degrees (vertices &v) {
	for (int i = 0, j; i < (int) v.size (); ++i)
		for (v[i].d = j = 0; j < (int) v.size (); ++j)
			v[i].d += e[v[i].i][v[j].i]; }
struct steps { int i1, i2; steps (): i1 (0), i2 (0) {} };
std::vector <steps> S;
bool cut1 (const int pi, const colors &A) {
	for (int i = 0; i < (int) A.size (); ++i)
		if (e[pi][A[i]]) return true; return false; }
void cut2 (const vertices &A, vertices & B) {
	for (int i = 0; i < (int) A.size () - 1; ++i)
		if (e[A.back().i][A[i].i]) B.push_back(A[i].i); }
void color_sort (vertices & R) {
	int j = 0, maxno = 1, min_k = std::max ((int) QMAX.size () - (int) Q.size() + 1, 1);
	C[1].clear (); C[2].clear ();
	for (int i = 0; i < (int) R.size (); ++i) {
		int pi = R[i].i, k = 1; while (cut1(pi, C[k])) ++k;
		if (k > maxno) maxno = k, C[maxno + 1].clear();
		C[k].push_back (pi); if (k < min_k) R[j++].i = pi; }
	if (j > 0) R[j - 1].d = 0;
	for (int k = min_k; k <= maxno; ++k)
		for (int i = 0; i < (int) C[k].size (); ++i)
			R[j].i = C[k][i], R[j++].d = k; }
void expand_dyn (vertices &R) {
	S[level].i1 = S[level].i1 + S[level - 1].i1 - S[level].i2;
	S[level].i2 = S[level - 1].i1;
	while ((int) R.size ()) {
		if ((int) Q.size () + R.back ().d > (int) QMAX.size ()) {
			Q.push_back (R.back ().i); vertices Rp; cut2 (R, Rp);
			if ((int) Rp.size ()) {
				if((float) S[level].i1 / ++pk < Tlimit) degree_sort (Rp);
				color_sort (Rp); ++S[level].i1, ++level;
				expand_dyn (Rp); --level;
			} else if ((int) Q.size () > (int) QMAX.size ()) QMAX = Q;
			Q.pop_back (); } else return; R.pop_back (); } }
void mcqdyn (int *maxclique, int &sz) {
	set_degrees (V); std::sort(V.begin (), V.end (), desc_degree); init_colors (V);
	for (int i = 0; i < (int) V.size () + 1; ++i) S[i].i1 = S[i].i2 = 0;
	expand_dyn (V); sz = (int) QMAX.size ();
	for (int i = 0; i < (int) QMAX.size (); i++) maxclique[i] = QMAX[i]; }
void degree_sort (vertices & R) {
	set_degrees(R); std::sort(R.begin(), R.end(), desc_degree); }
max_clique (const BB *conn, const int sz, const float tt = .025) : pk (0), level (1), Tlimit (tt) {
	for(int i = 0; i < sz; i++) V.push_back (vertex (i));
	e = conn, C.resize (sz + 1), S.resize (sz + 1); } };
