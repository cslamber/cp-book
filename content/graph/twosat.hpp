//$ set name 2-sat
///
//$ require scc
///
struct twosat {
	vector<vi> cs;
	twosat(int n) : cs(2*n) {}
	void add_clause(int a, bool av, int b, bool bv) {
		cs[2*a+!av].push_back(2*b+bv);
		cs[2*b+!bv].push_back(2*a+av);
	}
	optional<vector<char>> solve() const {
		scc s(cs); int n = cs.size() / 2;
		rep(i,0,n) if (s.comp_of[2*i] == s.comp_of[2*i+1]) return {};
		vector<char> sol(n);
		rep(i,0,n) sol[i] = s.comp_of[2*i] < s.comp_of[2*i+1];
		return sol;
	}
};
