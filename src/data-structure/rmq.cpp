for (int st = 1; st < 20; ++st) for (int i = 0; i < N; ++i)
	if (i + (1 << st - 1) < N) rmq[st][i] = std::min (rmq[st - 1][i], rmq[st - 1][i + (1 << st - 1)]);

int len = 31 - __builtin_clz (r - l + 1);
return std::min (rmq[len][l], rmq[len][r - (1 << len) + 1]);
