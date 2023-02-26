//$ set name tensor
///
/// standard tensor template for n-dim arrays without incuring overhead
///
template<class T, int D> struct tensor {
	using I = array<int, D>;
	vector<T> data; I dim;
	tensor(I dim, T e = T()) : dim(dim) {
		int s = 1; for (int x : dim) s *= x;
		data.resize(s, e);
	}
	
	int ind(I a) const { int j = 0; rep(i,0,D) j = j * dim[i] + a[i]; return j; }
	T& operator[](I a) { return data[ind(a)]; }
	const T& operator[](I a) const { return data[ind(a)]; }
};
