//$ set name debug

/// using type_traits stuff to print based on capabilities
/// if this is only local, can do this a lot better with c++20, but have
/// to worry about other code potentially not working. maybe c++17
/// and enable feature flag locally

#if __cplusplus >= 201703L and defined LOCAL
#include <experimental/type_traits>

namespace debug {
tcT using is_iterator = decltype(declval<T>().begin());
tcT using is_printable = decltype(cerr << declval<T>());
tcT using is_tuple = decltype(get<0>(declval<T>()));
tcT using is_custom = decltype(declval<T>().print_by());

tcT struct ptr {
	T* r;
	auto print_by() { return *r; }
};

tcT void print(const T& t) {
	if constexpr (experimental::is_detected_v<is_printable, T>) cerr << t;
	else if constexpr (experimental::is_detected_v<is_custom, T>) print(t.print_by());
	else if constexpr (experimental::is_detected_v<is_iterator, T>) {
		string sep; cerr << "{";
		for (const auto& v : t) cerr << sep, sep = ", ", print(v);
		cerr << "}";
	} else if constexpr (experimental::is_detected_v<is_tuple, T>) {
		apply([&](const auto&... ts) {
			string sep; cerr << "{";
			((cerr << sep, sep = ", ", print(ts)), ...);
			cerr << "}";
		}, t);
	} else cerr << "[??]";
}

/// at some point i should get this to work with things that are not copyable
#undef dbg
#define dbg(...) do { \
	cerr << __LINE__ << ": [" << #__VA_ARGS__ << "] = "; \
	debug::print(make_tuple(__VA_ARGS__)); \
	cerr << endl; \
	} while (0)


}
#endif
