//$ set name counting helpers
///
///
///
template<class T> struct counting_helpers {
	void reset() { *this = counting_helpers(); }

	vector<T> fact_, ifact_, inv_;

	void compute_facts(int n) {
		if (fact_.size() >= ++n) return; 
		fact_.resize(n *= 2); ifact_.resize(n); inv_.resize(n);
		fact_[0] = 1; rep(i,1,n) fact_[i] = fact_[i-1] * i;
		ifact_[n-1] = fact_[n-1].inv(); rep(i,1,n) ifact_[n-i-1] = ifact_[n-i] * (n-i);
		rep(i,1,n) inv_[i] = ifact_[i] * fact_[i-1];
	}

	T fact(int n) { return n < 0 ? 0 : (compute_facts(n), fact_[n]); }
	T ifact(int n) { return n < 0 ? 0 : (compute_facts(n), ifact_[n]); }
	T c(int n, int r) { return fact(n) * ifact(r) * ifact(n-r); }
};
