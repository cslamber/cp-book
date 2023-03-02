//$ set name small matrix
///
/// a short template for small matrices
///
template<int N, int M, class T> struct smat : array<array<T, M>, N> {
	smat(T diag = T()) { rep(i,0,N) rep(j,0,M) (*this)[i][j] = i == j ? diag : T(); }
	smat& operator+=(const smat& o) { rep(i,0,N) rep(j,0,M) (*this)[i][j] += o[i][j]; }
	smat operator+(const smat& o) const { return smat(*this) += o; }
	smat& operator*=(T x) { rep(i,0,N) rep(j,0,M) (*this)[i][j] *= x; return *this; }
	smat operator*(T x) const { return smat(*this) *= x; }
	template<int K> auto operator*(const smat<M, K, T>& o) const {
		smat<N, K, T> r;
		rep(i,0,N) rep(j,0,M) rep(k,0,K) r[i][k] = (*this)[i][j] * o[j][k];
		return r;
	}
	auto T() const { smat<M, N, T> r; rep(i,0,N) rep(j,0,M) r[j][i] = (*this)[i][j]; return r; }
};
