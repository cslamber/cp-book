//$ set name mo queries
///
/// a generic interface for mo queries
///
// Upd : (a/b 0/1, change is +-1, original a, original b) -> void
// Get : () -> T
// bucket size is S, returns vector<T>
template<class Upd, class Get> auto mo_queries(
		int S, int a, int b,
		vector<array<int,2>> qs,
		const Upd& upd, const Get& get) {
	struct query { int a, b, i; };
	vector<query> Q; rep(i,0,qs.size()) Q.push_back({qs[i][0], qs[i][1], i});
	sort(all(Q), [S](auto x, auto y) { return make_pair(x.a / S, x.b) < make_pair(y.a / S, y.b); });
	vector<decltype(get())> ans(Q.size());
	for (query q : Q) {
		while (a < q.a) upd(0,1,a++,b);
		while (b < q.b) upd(1,1,a,b++);
		while (a > q.a) upd(0,-1,a--,b);
		while (b > q.b) upd(1,-1,a,b--);
		ans[q.i] = get();
	}
	return ans;
}