//$ set name augmented union find
///
/// tracks path sums between elements assuming sums are a group and
/// all added paths are relatively consistent (aka cocycles if ur conley)
///
template<class G> struct ufs_aug {
	using T = typename G::T;
	int s; vector<int> p; vector<T> d; G g;
	ufs_aug(int n, G g = G()) : s(n), p(n, -1), d(n, g.e()), g(g) {}

	T root(int& a) {
		if (p[a] < 0) return g.e();
		T x = g.op(d[a], root(p[a]));
		d[a] = x; a = p[a]; return x;
	}
	void _join(int a, int b, T t) { p[b] += p[a]; p[a] = b; d[a] = t; }
	void join(int a, int b, T t) {
		T aa = root(a), bb = root(b);
		if (a == b) return; s--;
		if (p[b] < p[a]) _join(b, a, g.op(g.inv(g.op(t, bb)), aa));
		else _join(a, b, g.op(g.inv(aa), g.op(t, bb)));
	}

	optional<T> relate(int a, int b) {
		T aa = root(a), bb = root(b);
		return a == b ? g.op(aa, g.inv(bb)) : optional<T>();
	}
};
