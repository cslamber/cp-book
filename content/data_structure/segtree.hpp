//$ set name segtree
///
/// the simplest segtree out there
///
template<class G> struct segtree {
	using T = typename G::T;
	G g; int n = 1; vector<T> t;
	segtree(const vector<T>& v, G g = G()) : g(g) {
		while (n < v.size()) n *= 2;
		t.resize(2*n, g.e());
		rep(i,0,v.size()) t[i+n] = v[i];
		for (int i = n; --i;) t[i] = g.op(t[2*i],t[2*i+1]);
	}
	segtree(int n, G g = G()) : segtree(vector<T>(n, g.e()), g) {}
	T get(int l, int r) {
		T L = g.e(), R = g.e();
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l&1) L = g.op(L, t[l++]);
			if (r&1) R = g.op(t[--r], R);
		}
		return g.op(L, R);
	}
	void set(int i, T v) {
		t[i += n] = v;
		while (i /= 2) t[i] = g.op(t[2*i],t[2*i+1]);
	}
};