//$ set name matrix
///
/// arbitrary sized matrices
///
//$ require tensor
template<class T> struct matrix : tensor<T, 2> {
	matrix(int N, int M, T diag = T()) : tensor<T, 2>(T(), N, M) {
		rep(i,0,min(N,M)) (*this)(i,i) = diag;
	}
	matrix& operator+=(const matrix& o) { rep(i,0,N) rep(j,0,M) (*this)(i,j) += o(i,j); }
	matrix operator+(const smat& o) const { return matrix(*this) += o; }
	matrix& operator*=(T x) { rep(i,0,N) rep(j,0,M) (*this)(i,j) *= x; return *this; }
	matrix operator*(T x) const { return smat(*this) *= x; }
	auto operator*(const matrix& o) const {
		matrix r;
		rep(i,0,N) rep(j,0,M) rep(k,0,K) r(i,k) = (*this)(i,j) * o(j,k);
		return r;
	}
	matrix T() const { matrix r(M, N); rep(i,0,N) rep(j,0,M) r(j,i) = (*this)(i,j); return r; }
};