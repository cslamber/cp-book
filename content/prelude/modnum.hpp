//$ set name modnum
///
/// this allows us to only conditionally require counting_helpers
template<class T> struct counting_helpers;

template<const uint32_t& MOD> struct modnum {
	using T = modnum; using u32 = uint32_t;
	u32 v;

	static u32 minv(u32 a, u32 m) {
		a %= m; assert(a);
		return a == 1 ? 1 : m - (uint64_t)minv(m, a) * m / a;
	}

	modnum() : v(0) {}
	modnum(ll _v) : v(_v % MOD) { if (_v < 0) v += MOD; }

	T inv() const { T r; r.v = minv(v, MOD); return r; }
	bool operator==(T o) const { return v == o.v; }

	T& operator+=(T o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
	T& operator-=(T o) { v = v - o.v + (v < o.v ? MOD : 0); return *this; }
	T& operator*=(T o) { v = (uint64_t)v * o.v % MOD; return *this; }
	T& operator/=(T o) { return *this *= o.inv(); }
	T operator+(T o) const { T r(*this); r += o; return r; }
	T operator-(T o) const { T r(*this); r -= o; return r; }
	T operator*(T o) const { T r(*this); r *= o; return r; }
	T operator/(T o) const { T r(*this); r /= o; return r; }

	T operator+() const { return T(*this); }
	T operator-() const { T r; r.v = v ? MOD-v : 0; return r; }

	explicit operator u32() const { return v; }
	friend ostream& operator<<(ostream& out, const T& n) {
		return out << u32(n); }
	friend istream& operator>>(istream& in, T& n) {
		ll v_; in >> v_; n = T(v_); return in; }

	/// counting helpers can be included if needed
	inline static counting_helpers<T> count;
};
