struct crt {
	long long fix (const long long &a, const long long &b) { return (a % b + b) % b; }
	bool solve (const std::vector <std::pair <long long, long long>> &in, std::pair <long long, long long> &out) {
		out = std::make_pair (1LL, 1LL);
		for (int i = 0; i < (int) in.size (); ++i) {
			long long n, u;
			euclid (out.second, in[i].second, n, u);
			long long divisor = std::__gcd (out.second, in[i].second);
			if ((in[i].first - out.first) % divisor) return false;
			n *= (in[i].first - out.first) / divisor;
			n = fix (n, in[i].second);
			out.first += out.second * n;
			out.second *= in[i].second / divisor;
			out.first = fix (out.first, out.second); }
		return true; } };

