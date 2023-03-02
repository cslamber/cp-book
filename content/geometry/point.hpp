//$ set name point
///
/// only impl the stuff you need on contest obv
///
template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T> struct point {
	T x, y;
	point(T x = 0, T y = 0) : x(x), y(y) {}
	using p2 = point;

	struct rat {
		T p, q;
		rat(T p = 0, T q = 1) : p(p), q(q) { if (q < 0) p = -p, q = -q; }
		bool operator==(rat o) const { return p*o.q == o.p*q; }
		bool operator<(rat o) const { return p*o.q < o.p*q; }
		operator double() const { return double(p) / q; }
	};

	bool operator<(p2 o) const { return tie(x, y) < tie(o.x, o.y); }
	bool operator==(p2 o) const { return tie(x, y) == tie(o.x, o.y); }
	auto print_by() const { return make_pair(x, y); }
	p2 operator+(p2 a) const { return {x+a.x,y+a.y}; }
	p2 operator-(p2 a) const { return {x-a.x,y-a.y}; }
	p2 operator*(T a) const { return {x*a,y*a}; }
	p2 operator/(T a) const { return {x/a,y/a}; }

	T dot(p2 a) const { return x*a.x + y*a.y; }
	T cross(p2 a) const { return x*a.y - y*a.x; }
	T dot(p2 a, p2 b) const { return (a-*this).dot(b-*this); }
	T cross(p2 a, p2 b) const { return (a-*this).cross(b-*this); }
	p2 perp() const { return {-y, x}; }
	T dist2() const { return dot(*this); }
	double dist() const { return sqrt(dist2()); }
	double angle() const { return atan2(y, x); }
	/// returns a point whose angle is the same as the difference between
	/// the angles of o and this
	p2 angleto(p2 o) const { return {dot(o), cross(o)}; }
	rat tanspace(p2 a, p2 b) const { return (a-*this).tanspace(b-*this); }
	/// s is range
	/// 0 -> [-pi, pi]
	/// >0 -> [0, 2pi]
	/// <0 -> [-2pi, 0]
	double angle(p2 a, p2 b, int s) const {
		double c = atan2(cross(a,b), dot(a,b));
		if (s > 0 && c < 0) c += 2*acos(-1);
		if (s < 0 && c > 0) c -= 2*acos(-1);
		return c;
	}
	p2 unit() const { return *this/dist(); }
	p2 rotate(double a) const { return {x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)}; }
	point<double> fp() const { return {x, y}; }
	double slope() const { return double(y) / x; }

	/// exact order by angle about origin
	bool angle_less(p2 o) const {
		auto sec = [](p2 p) { return p.x < 0 ? 1 : 2*(p.y < 0); };
		return make_tuple(sec(*this), T(0)) < make_tuple(sec(o), cross(o));
	}

	struct seg {
		p2 a, b;
		auto print_by() const { return make_pair(a, b); }

		point<double> at(double t) const { return a.fp()*(1-t) + b.fp()*t; }
		p2 d() const { return b-a; }

		/// magnitudes are O(x^2)
		rat isect(seg o) const { return {o.a.cross(o.b)+o.b.cross(a)+a.cross(o.a), d().cross(o.d()) }; }
		rat closest(p2 o) const { return {dot(o), dist2()}; }

		// returns the interval for which these intersect
		pair<rat, rat> isect_r(seg o) {
			if (d().cross(o.d())) return 
		}

		/// if the union of two (closed) segments is itself a segment, returns that
		optional<seg> union_(seg o) const {
			if (d().cross(o.d()) || d().cross(o.a-a)) return {};
			auto cmp = [&](p2 x, p2 y) { return a.dot(b,x) < a.dot(b,y); };
			if (cmp(b,o.a) && cmp(b,o.b) || cmp(o.a,a) && cmp(o.b,a)) return {};
			return {{ min({a,o.a,o.b},cmp), max({b,o.a,o.b},cmp) }};
		}

	};
	seg to(p2 o) const { return {*this, o}; }
};
