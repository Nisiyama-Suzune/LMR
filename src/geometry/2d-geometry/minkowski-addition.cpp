// Two clockwise convex hull with the first point equal to the last each.
int i[2] = {0, 0}, len[2] = { (int) cv[0].size () - 1, (int) cv[1].size () - 1 };
std::vector <point> mnk;
mnk.push_back (cv[0][0] + cv[1][0]);
do {
	int d = dot (cv[0][i[0] + 1] - cv[0][i[0]], cv[1][i[1] + 1] - cv[1][i[1]]) >= 0;
	mnk.push_back (cv[d][i[d] + 1] - cv[d][i[d]] + mnk.back ());
	i[d] = (i[d] + 1) % len[d];
} while (i[0] || i[1]);
