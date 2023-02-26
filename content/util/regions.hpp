//$ set name regions
///
/// maintains a mapping from an ordered key space to values, where
/// operations can set a range, in which case we return all of the
/// overwritten values, or query for the value at a point
///
/// all operations in amortized O(log n) time on closed-open ivls
///
/// potential improvement: return more information about the
/// segments being removed?
///
/// implementation note: right (exclusive) endpoints are stored in the map
///
template<class K, class V> struct regions {
	map<K, optional<V>> m;
	regions() {}

	optional<V> query(K i) const {
		auto it = m.upper_bound(i);
		return it == m.end() ? optional<V>() : it->second;
	}

	// inclusive-exclusive
	struct ivl { K l, r; V v; };

	vector<ivl> set(K l, K r, optional<V> v) {
		vector<ivl> ret;
		auto it = m.upper_bound(l);
		/// should not insert if already exists
		m.emplace(l, it != m.end() ? it->second : optional<V>());

		for (; it != m.end() && it->first < r; it = m.erase(it)) {
			if (it->second) ret.push_back({l, it->first, *it->second});
			l = it->first;
		}
		if (it != m.end() && it->second) ret.push_back({l, r, *it->second});

		m.insert_or_assign(r, v);
		return ret;
	}
};
