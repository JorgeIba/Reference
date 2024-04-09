// custom hashing
struct custom_hash { //* Safest
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

//* Safer but maybe add some *high_resolution_clock* random thing
unsigned hash_f(unsigned x) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x;
}
struct chash {
  int operator()(int x) const { return hash_f(x); }
};

// Safer and works better for fenwick tree or some based power of 2 data
// structure
struct chash {
  const int RANDOM =
      (long long)(make_unique<char>().get()) ^
      chrono::high_resolution_clock::now().time_since_epoch().count();
  static unsigned long long hash_f(unsigned long long x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
  int operator()(int x) const { return hash_f(x) ^ RANDOM; }
};
typedef gp_hash_table<int, int, chash> umapp

    //* Safe
    const int RANDOM =
        chrono::high_resolution_clock::now().time_since_epoch().count();
struct custom_hash {
  int operator()(int x) const { return x ^ RANDOM; }
};

// How to declare
unordered_map<lli, int, custom_hash> safe_map;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<lli, int, custom_hash> safe_hash_table; // va a madres

cc_hash_table<int, int, hash<int>> hash_table; // Este va más a madres