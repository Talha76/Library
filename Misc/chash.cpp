// Then which of Allah's favor will you deny?
// author: MushfiqTalha
// hash template: https://github.com/mochow13/competitive-programming-library/blob/master/Data%20Structures/GP%20Hash%20Table.cpp
#include "bits/stdc++.h"
#define all(v) begin(v), end(v)
using namespace std;
typedef long long LL;

unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
struct chash {
    int operator()(int x) const { return hash_f(x); }
};

int main() {
  cin.tie(NULL)->sync_with_stdio(false);


  return 0;
}

