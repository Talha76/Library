// hash template: https://github.com/mochow13/competitive-programming-library/blob/master/Data%20Structures/GP%20Hash%20Table.cpp
unsigned hash_f(unsigned a, unsigned b) {
  return a*31 + b;
}
struct chash {
  int operator()(pair<int, int> a) const { return hash_f(a.first, a.second); }
};
