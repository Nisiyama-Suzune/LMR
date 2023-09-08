template <int ft = 3, int n = 2, int m = 3, int MAXDATA = 100000>
struct network {
	double wp[n][m][ft/* or m, if larger */], bp[n][m], w[m], b, val[n][m], del[n][m], avg[ft + 1], sig[ft + 1];
	network () {
		std::mt19937_64 mt (time (0));
		std::uniform_real_distribution <double> urdn (0, 2 * sqrt (m));
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < (i ? m : ft); ++k)
			wp[i][j][k] = urdn (mt);
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) bp[i][j] = urdn (mt);
		for (int i = 0; i < m; ++i) w[i] = urdn (mt); b = urdn (mt);
		for (int i = 0; i < ft + 1; ++i) avg[i] = sig[i] = 0; }
	double compute (double *x) {
		for (int j = 0; j < m; ++j) {
			val[0][j] = bp[0][j]; for (int k = 0; k < ft; ++k) val[0][j] += wp[0][j][k] * x[k];
			val[0][j] = 1 / (1 + exp (-val[0][j]));
		}
		for (int i = 1; i < n; ++i) for (int j = 0; j < m; ++j) {
			val[i][j] = bp[i][j]; for (int k = 0; k < m; ++k) val[i][j] += wp[i][j][k] * val[i - 1][k];
			val[i][j] = 1 / (1 + exp (-val[i][j]));
		}
		double res = b; for (int i = 0; i < m; ++i) res += val[n - 1][i] * w[i];
//		return 1 / (1 + exp (-res));
		return res; }
	void desc (double *x, double t, double eta) {
		double o = compute (x), delo = (o - t); // * o * (1 - o)
		for (int j = 0; j < m; ++j) del[n - 1][j] = w[j] * delo * val[n - 1][j] * (1 - val[n - 1][j]);
		for (int i = n - 2; i >= 0; --i) for (int j = 0; j < m; ++j) {
			del[i][j] = 0; for (int k = 0; k < m; ++k)
				del[i][j] += wp[i + 1][k][j] * del[i + 1][k] * val[i][j] * (1 - val[i][j]);
		}
		for (int j = 0; j < m; ++j) bp[0][j] -= eta * del[0][j];
		for (int j = 0; j < m; ++j) for (int k = 0; k < ft; ++k) wp[0][j][k] -= eta * del[0][j] * x[k];
		for (int i = 1; i < n; ++i) for (int j = 0; j < m; ++j) bp[i][j] -= eta * del[i][j];
		for (int i = 1; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < m; ++k)
			wp[i][j][k] -= eta * del[i][j] * val[i - 1][k];
		b -= eta * delo;
//		for (int i = 0; i < m; ++i) w[i] -= eta * delo * o * (1 - o) * val[i];
		for (int i = 0; i < m; ++i) w[i] -= eta * delo * val[n - 1][i]; } 
	void train (double data[MAXDATA][ft + 1], int dn, int epoch, double eta) {
		for (int i = 0; i < ft + 1; ++i) for (int j = 0; j < dn; ++j) avg[i] += data[j][i];
		for (int i = 0; i < ft + 1; ++i) avg[i] /= dn; 
		for (int i = 0; i < ft + 1; ++i) for (int j = 0; j < dn; ++j)
			sig[i] += (data[j][i] - avg[i]) * (data[j][i] - avg[i]);
		for (int i = 0; i < ft + 1; ++i) sig[i] = sqrt (sig[i] / dn); 
		for (int i = 0; i < ft + 1; ++i) for (int j = 0; j < dn; ++j)
			data[j][i] = (data[j][i] - avg[i]) / sig[i];
		for (int cnt = 0; cnt < epoch; ++cnt) for (int test = 0; test < dn; ++test)
			desc (data[test], data[test][ft], eta); }
	double predict (double *x) {
		for (int i = 0; i < ft; ++i) x[i] = (x[i] - avg[i]) / sig[i];
		return compute (x) * sig[ft] + avg[ft]; }
	std::string to_string () {
		std::ostringstream os; os << std::fixed << std::setprecision (16);
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < (i ? m : ft); ++k)
			os << wp[i][j][k] << " ";
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) os << bp[i][j] << " ";
		for (int i = 0; i < m; ++i) os << w[i] << " "; os << b << " ";
		for (int i = 0; i < ft + 1; ++i) os << avg[i] << " ";
		for (int i = 0; i < ft + 1; ++i) os << sig[i] << " ";
		return os.str (); }
	void read (const std::string &str) {
		std::istringstream is (str);
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < (i ? m : ft); ++k)
			is >> wp[i][j][k];
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) is >> bp[i][j];
		for (int i = 0; i < m; ++i) is >> w[i]; is >> b;
		for (int i = 0; i < ft + 1; ++i) is >> avg[i];
		for (int i = 0; i < ft + 1; ++i) is >> sig[i]; } };

