template <unsigned MOD> struct mint {
  unsigned val;
  mint(LL v=0): val(normalize(v)) {}
  unsigned normalize(LL v) {
    if (v < 0) {
      v = v < -MOD ? v%MOD + MOD : v + MOD;
      return v == MOD ? 0 : v;
    }
    return v < MOD ? v : v < MOD<<1 ? v-MOD : v%MOD;
  }
  friend istream& operator >> (istream& in , mint& a) {
    LL v; in >> v; a.val = a.normalize(v); return in;
  }
  friend ostream& operator << (ostream& out, mint  a) { return out << a.val; }
  mint operator + (const mint a) { return mint(val + a.val); }
  mint operator - (const mint a) { return mint(val - a.val); }
  mint operator * (const mint a) { return mint(1LL*val*a.val); }
  mint operator / (const mint a) { return mint(1LL*val*bigmod(a.val, MOD-2, MOD)); }
  mint operator += (const mint a) { val = normalize(val + a.val); return *this; }
  mint operator -= (const mint a) { val = normalize(0LL+val - a.val); return *this; }
  mint operator *= (const mint a) { val = normalize(1LL*val*a.val); return *this; }
  mint operator /= (const mint a) {
    val = normalize(1LL*val*bigmod(a.val, MOD-2, MOD)); return *this;
  }
};
