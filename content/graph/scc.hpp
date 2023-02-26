//$ set name strongly connected components
///
///
///
struct scc {
	vector<vi> comps; vi comp_of;
	scc(vector<vi> g) : comp_of(g.size()) {
		vector<vi> g2(g.size());
		rep(i,0,g.size()) for (int x : g[i]) g2[x].push_back(i);
		vector<char> v(g.size()); vi o;
		auto dfs = [&](auto rec, int i) -> void {
			if (v[i]) return; v[i] = 1;
			for (int x : g[i]) rec(rec, x);
			o.push_back(i);
		};
		rep(i,0,g.size()) dfs(dfs, i);
		reverse(all(o));
		auto dfs2 = [&](auto rec, int i) -> void {
			comp_of[i] = comps.size()-1;
			comps.back().push_back(i);
			v[i] = 2;
			for (int x : g2[i]) if (v[x]<2) rec(rec, x);
		};
		for (int x : o) if (v[x]<2) comps.emplace_back(), dfs2(dfs2, x);
	}
};
