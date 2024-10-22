template <unsigned MOD> struct mod_int {
  unsigned val;
  mod_int(LL v=0): val(v) {}
  friend ostream& operator << (ostream& out, mod_int  a) { return out << a.val; }
  mod_int operator = (const int a) { return val = a % MOD; }
  mod_int operator = (const LL a)  { return val = a % MOD; }
  mod_int operator = (const unsigned a)  { return val = a % MOD; }
  mod_int operator + (const mod_int a) { return val + a.val - (val + a.val < MOD ? 0 : MOD); }
  mod_int operator - (const mod_int a) { return val < a.val ? val + MOD - a.val : val - a.val; }
  mod_int operator * (const mod_int a) { return 1LL*val*a.val % MOD; }
  mod_int operator / (const mod_int a) { return 1LL*val*bigmod(a.val, MOD-2, MOD) % MOD; }
  mod_int operator += (const mod_int a) { return val += a.val - (val + a.val < MOD ? 0 : MOD); }
  mod_int operator -= (const mod_int a) { return val = val < a.val ? val + MOD - a.val : val - a.val; }
  mod_int operator *= (const mod_int a) { return val = 1LL*val*a.val % MOD; }
  mod_int operator /= (const mod_int a) { return val = 1LL*val*bigmod(a.val, MOD-2, MOD) % MOD; }
};
