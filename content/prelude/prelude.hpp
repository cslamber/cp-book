//$ set name prelude
///
/// might want to exclude ext in future since it screws up clang?
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

/// works on most judges
#pragma GCC target ("avx2")

#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define tcT template<class T>

using ll = long long; using ull = unsigned long long;
using vi = vector<int>; using vl = vector<ll>;
using db = double;

void subcases();
signed main() {
	/// standard fast io
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(17);

	subcases();
}

/// dbg by default does nothing unless we define it in debug.hpp
#define dbg(...) do {} while (0)

tcT void setmax(T& d, T s) { if (d < s) d = s; }
tcT void setmin(T& d, T s) { if (s < d) d = s; }

//$ locally require debug
//$ require common
