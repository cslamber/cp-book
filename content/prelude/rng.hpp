//$ set name rng
///
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
ll randint(ll lo, ll hi) { return uniform_int_distribution<ll>(lo,hi)(rng); }
