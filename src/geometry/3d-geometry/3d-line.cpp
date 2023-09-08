#define cl3 const line3 &
struct line3 {
	point3 s, t;
	explicit line3 (cp3 s = point3 (), cp3 t = point3 ()) : s (s), t (t) {} };
point3 line_plane_intersection (cl3 a, cl3 b) { return a.s + (a.t - a.s) * dot (b.s - a.s, b.t - b.s) / dot (a.t - a.s, b.t - b.s); }
line3 plane_intersection (cl3 a, cl3 b) {
	point3 p = det (a.t - a.s, b.t - b.s), q = det (a.t - a.s, p), s = line_plane_intersection (line3 (a.s, a.s + q), b);
	return line3 (s, s + p); }
point3 project_to_plane (cp3 a, cl3 b) { return a + (b.t - b.s) * dot (b.t - b.s, b.s - a) / dis2 (b.t - b.s); }

