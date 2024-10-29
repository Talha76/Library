const int mod = 1e9 + 7;
const int lim = 5002;

// iterative combi. O(n^2)
vector <vector <int>> nCr(lim, vector <int> (lim, 0));
void combi() {
  for (int i = 1; i < lim; i++) {
    nCr[i - 1][0] = nCr[i][0] = 1;
    for (int j = 1; j <= i; j++)
      nCr[i][j] = (nCr[i - 1][j] + nCr[i - 1][j - 1]) % mod;
  }
}

// combi using Fermat's little thm. O(n*log(n))
int bigmod(int a, int p) {
  for(int ret = 1; ; p >>= 1, a = (1ll*a*a) % mod) {
    if(p == 0) return ret;
    if(p & 1) ret = (1ll*ret*a) % mod;
  }
}

int invmod(LL a) { return bigmod(a, mod - 2); }

vector <int> fact(lim, 1), inv(lim, 1);
void pre_compute() {
  for (int i = 1; i < lim; i++) {
    fact[i] = (1ll * fact[i - 1] * i) % mod;
    inv[i]  = invmod(fact[i]);
  }
}

int C(int n, int r) {
  if (r < 0 or r > n) return 0;
  int denom = (1ll*inv[r]*inv[n - r]) % mod;
  return (1ll*fact[n]*denom) % mod;
}
