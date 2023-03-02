//$ set name z-function
///
vi z_function(const vi& s) {
	int n = s.size(), l = 0, r = 0; vi z(n);
	rep(i,1,n) {
		if (i < r) z[i] = min(r-i, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
		if (i+z[i] > r) l = i, r = i+z[i];
	}
	return z;
}