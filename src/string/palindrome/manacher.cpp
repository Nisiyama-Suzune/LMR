char s[0..n] = '*#1#2#3#';
int p[n], id, mx;
for (int i = 1; i <= n; ++i) {
	if (mx > i) p[i] = std::min (p[2 * id - i], mx - i); else p[i] = 1;
	while (s[i - p[i]] == s[i + p[i]]) ++p[i];
	if (i + p[i] > mx) {
		mx = i + p[i]; id = i; } }
