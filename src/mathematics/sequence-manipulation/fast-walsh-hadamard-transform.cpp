void fwt (int *a, int n, int w) {
	for (int i = 1; i < n; i <<= 1)
		for(int j = 0; j < n; j += i << 1) {
			for(int k = 0; k < i; ++k) {
				int x = a[j + k], y = a[i + j + k];
				if (w) {
				/*	xor : a[j + k] = (x + y) / 2, a[i + j + k] = (x - y) / 2; and : a[j + k] = x - y; or : a[i + j + k] = y - x; */
				}else{
				/*	xor : a[j + k] = x + y, a[i + j + k] = x - y; and : a[j + k] = x + y; or : a[i + j + k] = x + y; */
				} } } }

