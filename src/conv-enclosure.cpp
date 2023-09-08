#include <bits/stdc++.h>

#define cd const long long &
const long long EPS = 0;
int sgn (cd x) { return x < -EPS ? -1 : x > EPS; }
int cmp (cd x, cd y) { return sgn (x - y); }
long long sqr (cd x) { return x * x; }

#define cp const point &
struct point {
	long long x, y;
	explicit point (cd x = 0, cd y = 0) : x (x), y (y) {}
	int dim () const { return sgn (y) == 0 ? sgn (x) > 0 : sgn (y) > 0; }
	point rot90 () const { return point (-y, x); }
	point _rot90 () const { return point (y, -x); } };
bool operator == (cp a, cp b) { return cmp (a.x, b.x) == 0 && cmp (a.y, b.y) == 0; }
bool operator != (cp a, cp b) { return cmp (a.x, b.x) != 0 || cmp (a.y, b.y) != 0; }
bool operator < (cp a, cp b) { return cmp (a.x, b.x) == 0 ? cmp (a.y, b.y) < 0 : cmp (a.x, b.x) < 0; }
bool operator > (cp a, cp b) { return cmp (a.x, b.x) == 0 ? cmp (a.y, b.y) > 0 : cmp (a.x, b.x) > 0; }
point operator - (cp a) { return point (-a.x, -a.y); }
point operator + (cp a, cp b) { return point (a.x + b.x, a.y + b.y); }
point operator - (cp a, cp b) { return point (a.x - b.x, a.y - b.y); }
point operator * (cp a, cd b) { return point (a.x * b, a.y * b); }
point operator / (cp a, cd b) { return point (a.x / b, a.y / b); }
long long dot (cp a, cp b) { return a.x * b.x + a.y * b.y; }
long long det (cp a, cp b) { return a.x * b.y - a.y * b.x; }
long long dis2 (cp a, cp b = point ()) { return sqr (a.x - b.x) + sqr (a.y - b.y); }

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

int n, m; std::vector <point> b;
long long sum[100010];
long long ans, S;

int main () {
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		long long x, y;
		scanf("%lld%lld", &x, &y);
		b.push_back (point (x, y));
	}
	auto it = convex_hull (b); std::vector <point> &a = it.first;
	for (int i = 1; i < a.size (); ++i)
		sum[i] = sum[i - 1] + det (a[i - 1], a[i]);
	S = ans = sum[a.size () - 1] + det (a[a.size () - 1], a[0]);
	for (int i = 1; i <= n - m; ++i) {
		long long x, y;
		scanf("%lld%lld", &x, &y);
		auto res = convex_tan (point (x, y), a, it.second);
		int d1 = res.second, d2 = res.first;
		if (d1 != -1) {
			long long tmp = 0;
			if (d1 > d2) {
				tmp = -(sum[d1] - sum[d2] + det(a[d1], a[d2]));
				tmp += det (a[d2], point(x, y)) + det (point (x, y), a[d1]) + det (a[d1], a[d2]);
			} else {
				tmp = -(S - (sum[d2] - sum[d1] + det(a[d2], a[d1])));
				tmp += det (a[d2], point(x, y)) + det (point (x, y), a[d1]) + det (a[d1], a[d2]);
			}
			if (ans < tmp + S) ans = tmp + S;
		}
	}
	printf ("%lld", ans / 2);
	if (ans % 2 == 0) printf(".0\n"); else printf(".5\n");
	return 0;
}
