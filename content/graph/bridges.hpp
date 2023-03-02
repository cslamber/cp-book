//$ set name bridges
///
/// find all bridgeless components
/// handles multi-edges, self-loops
///
struct bridges {
	vector<vi> comps, edge; vi comp_of;
	bridges(vector<vi> g) : comp_of(g.size()) {
		int n = g.size(), timer = 1, stop = 0;
		vi tin(n), low(n), stk(n);
		auto dfs = [&](auto rec, int i, int b) -> void {
			stk[stop++] = i;
			tin[i] = low[i] = timer++;
			for (int x : g[i]) if (x != b) {
				if (!tin[x]) rec(rec, x, i);
				low[i] = min(low[i], tin[x]);
			}
			if (tin[i] == low[i]) {
				int u; comps.emplace_back();
				do {
					u = stk[--stop];
					comp_of[u] = comps.size()-1;
					comps.back().push_back(u);
				} while (u != x);
			}
		};
		rep(i,0,g.size()) if (!tin[i]) dfs(dfs, i, -1);
		/// maybe this can be shortened into the above?
		edge.resize(comps.size());
		rep(i,0,g.size()) for (int j : g[i]) {
			int ii = comp_of[i], jj = comp_of[j];
			if (ii != jj) edge[ii].push_back(jj);
		}
	}
};