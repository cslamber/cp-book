//$ set name union find
//$ set author kactl
///
/// union find + something else maybe eventually
///
struct UF {
	vi e; int cmps;
	UF(int n) : e(n, -1), cmps(n) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a; cmps--;
		return true;
	}
};
