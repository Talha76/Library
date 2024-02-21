#include <bits/stdc++.h>
using namespace std;
/*
  O(|S| + |alphabet|) Suffix Array
  LIM := max{s[i]} + 2
  Author: AlphaQ

  - Call getSuffixArray(s) to get the suffix array of string s
  - Call getLCParray(s, SA, rank) to get the LCP array of string s
  - Don't use '$' as delimiter. Use '%' instead
*/
namespace SuffixArray {
  void inducedSort (const vector <int> &vec, int val_range, vector <int> &SA, const vector <int> &sl, const vector <int> &lms_idx) {
    vector <int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) {
      ++r[c]; if (c + 1 < val_range) ++l[c + 1];
    }
    partial_sum(l.begin(), l.end(), l.begin());
    partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i) SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA) if (i > 0 and sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1;
    fill(r.begin(), r.end(), 0);
    for (int c : vec) ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k; --k, i = SA[k]) {
      if (i and !sl[i - 1]) SA[--r[vec[i - 1]]] = i - 1;
    }
  }

  vector <int> suffixArray (const vector <int> &vec, int val_range) {
    const int n = vec.size();
    vector <int> sl(n), SA(n), lms_idx;
    for (int i = n - 2; i >= 0; --i) {
      sl[i] = vec[i] > vec[i + 1] or (vec[i] == vec[i + 1] and sl[i + 1]);
      if (sl[i] and !sl[i + 1]) lms_idx.emplace_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end());
    inducedSort(vec, val_range, SA, sl, lms_idx);
    vector <int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i) {
      if (SA[i] > 0 and !sl[SA[i]] and sl[SA[i] - 1]) new_lms_idx[k++] = SA[i];
    }
    int cur = 0; SA[n - 1] = 0;
    for (int k = 1; k < new_lms_idx.size(); ++k) {
      int i = new_lms_idx[k - 1], j = new_lms_idx[k];
      if (vec[i] ^ vec[j]) {
        SA[j] = ++cur; continue;
      }
      bool flag = 0;
      for (int a = i + 1, b = j + 1; ; ++a, ++b) {
        if (vec[a] ^ vec[b]) {
          flag = 1; break;
        }
        if ((!sl[a] and sl[a - 1]) or (!sl[b] and sl[b - 1])) {
          flag = !(!sl[a] and sl[a - 1] and !sl[b] and sl[b - 1]); break;
        }
      }
      SA[j] = flag ? ++cur : cur;
    }
    for (int i = 0; i < lms_idx.size(); ++i) lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < lms_idx.size()) {
      auto lms_SA = suffixArray(lms_vec, cur + 1);
      for (int i = 0; i < lms_idx.size(); ++i) new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
    inducedSort(vec, val_range, SA, sl, new_lms_idx); return SA;
  }

  vector <int> getSuffixArray (const string &s, const int LIM = 128) {
    vector <int> vec(s.size() + 1);
    copy(begin(s), end(s), begin(vec)); vec.back() = '$';
    auto ret = suffixArray(vec, LIM);
    ret.erase(ret.begin()); return ret;
  }

  // build RMQ on it to get LCP of any two suffix
  vector <int> getLCParray (const string &s, const vector <int> &SA, vector<int> &rank) {
    int n = s.size(), k = 0;
    rank.assign(n, 0);
    vector <int> lcp(n);
    for (int i = 0; i < n; ++i) rank[SA[i]] = i;
    for (int i = 0; i < n; ++i, k ? --k : 0) {
      if (rank[i] == n - 1) {
        k = 0; continue;
      }
      int j = SA[rank[i] + 1];
      while (i + k < n and j + k < n and s[i + k] == s[j + k]) ++k;
      lcp[rank[i]] = k;
    }
    lcp[n - 1] = 0; return lcp;
  }
}
using namespace SuffixArray;

int main() {
  int n;
  cin >> n;
  string s;
  for (int i = 0; i < n; i++) {
    string x;
    cin >> x;
    s += x + '%';
  }
  auto sa = getSuffixArray(s);
  vector<int> rank;
  auto lcp = getLCParray(s, sa, rank);
  printf("Suffix Array: ");
  for (const int i : sa) printf("%d ", i);
  printf("\nRank Array: ");
  for (const int i : rank) printf("%d ", i);
  printf("\nLCP Array: ");
  for (const int i : lcp) printf("%d ", i);
  puts("");
  return 0;
}

