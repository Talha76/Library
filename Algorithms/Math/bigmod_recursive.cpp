// Then which of Allah's favor will you deny?
// author: Mushfiq_Talha
#ifdef MUSHFIQ_DEBUG
#include "dbg.h"
#else
#define dbg(...) {}
#endif
#include "bits/stdc++.h"
#define all(v) v.begin(), v.end()
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int mod = 1e9 + 7;

LL bigmod(LL a, LL p) {
  if(p == 0) return 1;
  LL ret = bigmod(a, p/2);
  ret = (ret * ret) % mod;
  if(p & 1) ret = (ret * a) % mod;
  return ret;
}

LL invmod(LL a) { return bigmod(a, mod - 2); }

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int a, p;
  cin >> a >> p;
  cout << bigmod(a, p);

  return 0;
}

