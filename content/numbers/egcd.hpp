//$ set name extended euclidean algorithm
//$ set author kactl
///
/// also includes CRTsince that tends to go alongside it
///
/// from kactl
ll egcd(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = egcd(b, a % b, y, x);
	return y -= a/b * x, d;
}
///
/// resulting modulus is always lcm of m1, m2. returns {0, 0} for invalid
///
ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}