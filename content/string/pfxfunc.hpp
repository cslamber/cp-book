//$ set name prefix function
///
vi prefix_function(const vi& s) {
	int n = s.size(); vi pi(n);
	rep(i,1,n) {
		int j = pi[i-1];
		while (j && s[i] != s[j]) j = pi[j-1];
		pi[i] = j + (s[i] == s[j]);
	}
	return pi;
}