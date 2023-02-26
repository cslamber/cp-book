//$ set name bits
///
/// most of this stuff exists in c++20, also TODO idk how much of this is right
///
int countl_zero(ull x) { return x ? __builtin_clzll(x) : 64; }
int countr_zero(ull x) { return x ? __builtin_ctzll(x) : 64; }
int bit_width(ull x) { return 64 - countl_zero(x); }
ull sbit(int x) { return ull(1) << x; }
ull bit_ceil(ull x) { return x < 2 ? 1 : ull(1) << (64 - __builtin_clzll(x-1)); }
ull bit_floor(ull x) { return sbit(bit_width(x)-1); }
int popcount(ull x) { return __builtin_popcountll(x); }
