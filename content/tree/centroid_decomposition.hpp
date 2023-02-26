//$ set name centroid decomposition
///
/// centroid decomposition apparently
///
// F : (centroid, parent or -1, active verts) -> void
template<class F> void centroid_decomposition(vector<vi> T, F f) {
	int n = sz(T);
	vector<char> on(n, 1);
	vi s(n);
	yc([&](auto rec, int par, int i) -> void {
		yc([&](auto rec, int i, int b) -> void {
			s[i] = 1;
			for (int j : T[i]) if (j != b && on[j])
				rec(j, i), s[i] += s[j];
		})(i, -1);
		int c = yc([&](auto rec, int j, int b) -> int {
			for (int k : T[j]) if (k != b && on[k] && s[k] * 2 > s[i])
				return rec(k, j);
			return j;
		})(i, -1);
		f(c, par, on);
		on[c] = 0;
		for (int j : T[c]) if (on[j]) rec(c, j);
	})(-1, 0);
}
