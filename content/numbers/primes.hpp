//$ set name primes
///
/// linear time prime sieve, factoring, and mobius function
///
static struct {
	/// p = list of primes
	/// q = largest prime factor
	/// m = mobius function
	vi p, q(1), m(1);
	void calc(int n) {
		if (n++ < q.size()) return;
		m = q = vi(n*=2);
		rep(i,2,n) {
			if (!q[i]) q[i] = i, m[i] = -1, p.push_back(i);
			for (int j = 0; j < p.size() && p[j] <= q[i] && i*p[j] < n; j++)
				q[i*p[j]] = p[j], m[i*p[j]] = p[j] < q[i] ? -m[i] : 0;
		}
	}
	bool is(int n) { calc(n); return q[n] == n; }
	int nth(int n) { while (p.size() < n) calc(q.size()); return p[n]; }
	int mobius(int n) { calc(n); return m[n]; }
	// O(sqrt n)
	auto factor(int n) {
		vector<array<int, 2>> r;
		for (int i = 2; i*i <= n; i++) {
			int m = 0; while (n % i == 0) m++, n /= i;
			r.push_back({i, m});
		}
		if (n > 1) r.push_back({n, 1});
		return r;
	}
} primes;
