//$ set name sweep events
///
/// random general sweepline / angle template. mostly just an example of
/// std::multiset custom comparators, and should be modified as needed
///
/// Cmp(a : int, b : int, time : K)
/// Cb(time : K, os : multiset<int>, it : multiset<int>::iterator, bool adding)
/// always must have start <= end
template<class K, class Cmp, class Cb> void sweep(vector<pair<K, K>> lifetime, const Cmp& cmp, const Cb& cb) {
	if (objs.empty()) return;
	struct event { K time; bool rem; int i; };
	vector<event> evs;
	rep(i,0,objs.size()) {
		auto& [s,e] = objs;
		evs.push_back({s, 0, i});
		evs.push_back({e, 1, i});
	}
	sort(all(evs), [](auto& a, auto& b){ return tie(a.time, a.rem) < tie(b.time, b.rem); });
	K time = evs[0].time;
	auto cc = [&time](const auto& a, const auto& b) { return cmp(a, b, time); };
	multiset<int, decltype(cc)> os(cc);
	vector<decltype(os)::iterator> where(objs.size());
	for (event& ev : evs) {
		time = ev.time;
		if (!ev.rem) where[ev.i] = os.insert(ev.i);
		cb(time, os, where[ev.i], !ev.rem);
		if (ev.rem) os.erase(where[ev.i]);
	}
}