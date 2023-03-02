//$ set name suffix array
///
struct suffixarray {
	int n; vi sa, lcp;
	tcT suffix_array(const vector<T>& s) : n(s.size()+1), sa(n), lcp(n-1) {
		/// coordinate compressession
		map<T,int> a; for (const T& e : s) a[e];
		int i = 1; for (auto& [k,v] : a) v = i++;
		vi cl(n); rep(i,0,n-1) cl[i] = a[s[i]];
		/// initialization
		auto cyc = [=](int a){ return a >= n ? a - n : a; };
		vi cnt(n), tmp(n), lcp(n); iota(all(sa), 0);
		/// main loop - start with j = 0 since we only have classes to start
		for (int j = 0; j < n; j = j ? 2*j : 1) {
			/// tmp stores sorted by cl[i+j]
			rep(i,0,n) tmp[i] = cyc(sa[i] + n - j);
			fill(all(cnt), 0); for (int c : cl) cnt[c]++;
			rep(i,1,n) cnt[i] += cnt[i-1];
			for (int i = n; i--;) sa[--cnt[cl[tmp[i]]]] = tmp[i];
			/// tmp stores old classes
			swap(cl, tmp); cl[sa[0]] = 0;
			rep(i,1,n) {
				int a = sa[i], b = sa[i-1];
				cl[a] = cl[b] + !(tmp[a] == tmp[b] && tmp[cyc(a+j)] == tmp[cyc(b+j)]);
			}
		}
		/// tmp stores rank
		int k = 0; rep(i,0,n) tmp[sa[i]] = i;
		rep(i,0,n-1) {
			int j = sa[tmp[i]-1];
			while (max(i,j)+k < n-1 && s[i+k] == s[j+k]) k++;
			lcp[tmp[i]] = k;
			if (k) k--;
		}
	}
};
