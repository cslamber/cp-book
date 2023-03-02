//$ set name bridges
///
/// find all bridgeless components
/// handles multi-edges, self-loops
///
struct bridges {
	vector<vi> comps, edge; vi comp_of;
	bridges(vector<vi> g) : comp_of(g.size()) {
		int n = g.size(), timer = 1;
		vi tin(n), low(n), stk;
		auto dfs = [&](auto rec, int i, int b) -> void {
			stk.push_back(i); int bc = 0;
			tin[i] = low[i] = timer++;
			for (int x : g[i]) if (x != b || bc++) {
				if (!tin[x]) rec(rec, x, i);
				low[i] = min(low[i], tin[x]);
			}
			if (tin[i] == low[i]) {
				int u, v = comps.size(); comps.emplace_back();
				do {
					u = stk.back(); stk.pop_back();
					if (u < 0) edges[v].push_back(~u), edges[~u].push_back(v);
					else comp_of[u] = v, comps[v].push_back(u);
				} while (u != i);
				stk.push_back(~v);
			}
		};
		rep(i,0,g.size()) if (!tin[i]) dfs(dfs, i, -1);
	}
};
