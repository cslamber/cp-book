//$ set name floor sum
///
/// simpler version of ACL floor sum
///
// sum (x = 1 to a) floor((b + cx) / d)
ll floor_sum(ll a, ll b, ll c, ll d) {
	if (a <= 0) return 0;
	if (c == 0) return div_floor(b,d)*a;
	if (b/d || c/d) return floor_sum(a,b%d,c%d,d) + c/d*a*(a+1)/2 + b/d*a;
	if (b<0 || c<0) return floor_sum(a,b+d,c+d,d) - a*(a+3)/2;
	/// justification: flip about x = y and do algebra
	return (a*c+b)/d*a - floor_sum((a*c+b)/d,-b-1,d,c);
}
