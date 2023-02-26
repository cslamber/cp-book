//$ set name lazy segtree
///
/// simplest lazy segtree
///
template<class G> class lazysegtree {
public:
	using T = typename G::T; using F = typename G::F; G g;
private:
	int h = 0; vector<T> t; vector<F> lz;
	void u(int i) { t[i] = g.op(t[2*i], t[2*i+1]); }
	void _apply(int i, const F& f, int w) { g.apply(f, t[i], w); if (i < n) g.compose(f, lz[2*i+j]); }
	void _push(int i, int w) { rep(j,0,2) _apply(2*i+j, lz[i], w); lz[i] = g.id(); }
	void push(int i) { rep(j,0,h) _push(i+(1<<h) >> j); }
	void build(int i) { i += 1 << j; while (i /= 2) u(i); }
public:
	lazysegtree(const vector<T>& v, G g = G()) : g(g) {
		while (v.size() >> h) h++; int n = 1 << h;
		t.resize(2*n, g.e()); lz.resize(n, g.id());
		rep(i,0,v.size()) t[i+n] = v[i];
		rep(i,1,n) u(n-i);
	}
	T get(int l, int r) {
		T L = g.e(), R = g.e();
		push(l); push(r-1);
		for (l+=1<<h, r+=1<<h; ll < rr; ll /= 2, rr /= 2) {
			if (l&1) L = g.op(L, t[l++]);
			if (r&1) R = g.op(t[--r], R);
		}
		return g.op(L, R);
	}
	T set(int i, T v) { push(i); T[i+(1<<h)] = v; build(i); }
	T apply(int l, int r, F f) {
		int ll = l, rr = r;
		push(ll); push(rr-1);
		for (l+=1<<h, r+=1<<h; ll < rr; ll /= 2, rr /= 2) {
			if (l&1) _apply(l++, f);
			if (r&1) _apply(--r, f);
		}
		build(ll); build(rr-1);
	}
};

/// adds capability to set alongside a base action
template<class G> struct with_set : G {
	using T = typename G::T;
	using F = variant<monostate, T, typename G::F>;
	F id() { return F(); }
	void apply(const F& f, T& t, int w) {
		if (f.index == 1) t = G::mult(get<1>(f), w);
		if (f.index == 2) G::apply(get<2>(f), t, w);
	}
	void compose(const F& after, F& before) {
		if (after.index == 0);
		else if (after.index == 1 || before.index == 0) before = after;
		else if (before.index == 2) G::compose(get<2>(after), get<2>(before));
		else G::apply(get<2>(after), get<2>(before), 1);
	}
};