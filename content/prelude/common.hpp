//$ set name common
///
/// from http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
/// can be replaced just by calling a lambda with itself as argument
template<class F> struct y_combinator_result {
	F f; tcT explicit y_combinator_result(T&&f) : f(forward<T>(f)) {}
	template<class...Ts> decltype(auto) operator()(Ts&&...ts) {
		return f(ref(*this), forward<Ts>(ts)...); }
};
template<class F> decltype(auto) yc(F&&f) {
	return y_combinator_result<decay_t<F>>(forward<F>(f)); }

/// f(lo) = 0, f(hi) = 1 (f only called strictly between lo and hi)
/// returns x where f(x) = 0, f(x+1) = 1
tcT ll bsearch(ll lo, ll hi, T f) {
	while (hi - lo > 1) {
		ll m = lo + hi >> 1;
		(f(m) ? hi : lo) = m;
	} return lo;
}

/// turn a key function into a less-than comparator
template<class T> auto cmp_key(T&& f) {
	return [f = move(f)](const auto& a, const auto& b) { return f(a) < f(b); };
}

/// what division should be
ll div_floor(ll n, ll d) { return n<0?~(~n/d):n/d; }

/// exponentiation by squaring
template<class T, class Op = multiplies<T>>
T Pow(T b, ull e, T o = 1, Op op = Op()) {
	for (; e; e >>= 1) {
		if (e&1) o = op(o, b);
		b = op(b, b);
	} return o;
}
