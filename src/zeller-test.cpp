#include <bits/stdc++.h>

int get_id (int y, int m, int d) {
	if (m < 3) { --y; m += 12; }
	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307; }
std::tuple <int, int, int> date (int id) {
	int x = id + 1789995, n, i, j, y, m, d;
	n = 4 * x / 146097; x -= (146097 * n + 3) / 4;
	i = (4000 * (x + 1)) / 1461001; x -= 1461 * i / 4 - 31;
	j = 80 * x / 2447; d = x - 2447 * j / 80;
	x = j / 11;
	m = j + 2 - 12 * x; y = 100 * (n - 49) + i + x;
	return std::make_tuple (y, m, d); }

int main () {
	std::cout << get_id (1, 1, 1) << "\n";
}

