//$ set name tensor
///
/// standard tensor template for n-dim arrays without substantial overhead
///
template<class T, int D> struct tensor {
	array<int, D> dim; vector<T> data;
	int ind(array<int, D> a) const { int j = 0; rep(i,0,D) j = j * dim[i] + a[i]; return j; }
	template<class...Ts> tensor(T e, Ts...a) : dim({a...}), data((a * ... * 1), e) {}
	template<class...Ts> T& operator()(Ts...a) { return data[ind({a...})]; }
	template<class...Ts> const T& operator()(Ts...a) const { return data[ind({a...})]; }
};
/// not necessary if you declare the type
template<class T, class...Ts> tensor(T e, Ts...a) -> tensor<T,sizeof...(a)>;