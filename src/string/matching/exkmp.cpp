void exkmp (char *s, int *a, int n) {
	a[0] = n; int p = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		a[i] = (r > i) ? std::min (r - i, a[i - p]) : 0;
		while (i + a[i] < n && s[i + a[i]] == s[a[i]]) ++a[i];
		if (r < i + a[i]) r = i + a[i], p = i; } }
void mat (char *s, char *t, int *a, int *b, int n, int m) {
	exkmp (t, b, m); int p = 0, r = 0;
	for (int i = 0; i < n; ++i) {
		a[i] = (r > i) ? std::min (r - i, b[i - p]) : 0;
		while (i + a[i] < n && a[i] < m && s[i + a[i]] == t[a[i]]) ++a[i];
		if (r < i + a[i]) r = i + a[i], p = i; } }
