//$ set name bridges
///
/// find all bridgeless components
/// handles multi-edges, self-loops
///
struct bridges {
	vector<vi> comps, edge; vi comp_of;
	bridges(vector<vi> g) : comp_of(g.size(), -1) {
		vi h(g.size()), isbridge(g.size());
		auto dfs2 = [&](auto rec, int i, int prev) -> void {
			if (comp_of[i] != -1 || isbridge[i]) return;
			comp_of[i] = comps.size() - 1; comps.back().push_back(i);
			for (int x : g[i]) if (x != prev) rec(rec, x, i);
		};
		auto dfs = [&](auto rec, int i, int prev, int ch) -> int {
			h[i] = ch; int back = 0, cprev = 0;
			for (int x : g[i]) if (x != prev || cprev++) {
				int b = h[x] ? max(0, ch - h[x]) : rec(rec, x, i, ch+1) - 1;
				back = max(back, b);
			}
			if (!back) {
				comps.emplace_back();
				dfs2(dfs2, i, prev);
				isbridge[i] = true;
			}
			isbridge[i] = !back;
			return back;
		};
		rep(i,0,g.size()) if (!h[i]) dfs(dfs, i, -1, 1);
		/// potentially can inline this above in the future
		edge.resize(comps.size());
		rep(i,0,g.size()) for (int j : g[i]) {
			int ii = comp_of[i], jj = comp_of[j];
			if (ii != jj) edge[ii].push_back(jj);
		}
	}
};