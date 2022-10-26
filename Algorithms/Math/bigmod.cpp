// Then which of Allah's favor will you deny?
// problem-url: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=310
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

int mod;

// Recursive
LL bigmod(LL a, LL p) {
  if(p == 0) return 1;
  LL ret = bigmod(a, p/2);
  ret = (ret * ret) % mod;
  if(p & 1) ret = (ret * a) % mod;
  return ret;
}

// Iterative
LL bigmod(LL a, LL p) {
  for(LL ret = 1; ; p >>= 1, a = (a*a) % mod) {
    if(p == 0) return ret;
    if(p & 1) ret = (ret * a) % mod;
  }
}

LL invmod(LL a) { return bigmod(a, mod - 2); }

signed main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int a, p;
  while(cin >> a >> p >> mod) {
    cout << bigmod(a, p) << "\n";
  }

  return 0;
}

