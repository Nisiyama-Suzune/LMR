#include <algorithm>
#include <iostream>

int rmq1[20][110000], rmq2[20][110000];

int query1 (int l, int r) {
	int len = 31 - __builtin_clz (r - l + 1);
	return std::min (rmq1[len][l], rmq1[len][r - (1 << len) + 1]);
}

int query2 (int l, int r) {
	int len = 31 - __builtin_clz (r - l + 1);
	return std::max (rmq2[len][l], rmq2[len][r - (1 << len) + 1]);
}

int main () {
	std::ios::sync_with_stdio (0);
	int N, Q; std::cin >> N >> Q;
	for (int i = 0; i < N; ++i) std::cin >> rmq1[0][i], rmq2[0][i] = rmq1[0][i];
	for (int st = 1; st < 20; ++st) for (int i = 0; i < N; ++i)
		if (i + (1 << st - 1) < N) rmq1[st][i] = std::min (rmq1[st - 1][i], rmq1[st - 1][i + (1 << st - 1)]);
	for (int st = 1; st < 20; ++st) for (int i = 0; i < N; ++i)
		if (i + (1 << st - 1) < N) rmq2[st][i] = std::max (rmq2[st - 1][i], rmq2[st - 1][i + (1 << st - 1)]);
	while (Q--) {
		int l, r; std::cin >> l >> r; --l, --r;
		std::cout << query2 (l, r) - query1 (l, r) << "\n";
	}
}
