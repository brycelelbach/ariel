#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>

struct _0 { };
struct _1 { };
struct _2 { };
struct _3 { };
struct _4 { };
struct _5 { };
struct _6 { };

struct _a { };
struct _b { };
struct _c { };
struct _d { };
struct _e { };
struct _f { };
struct _g { };

int main (void) {
  typedef nt2::meta::set<_0, _1, _2, _3, _4, _5, _6> numbers;
  typedef nt2::meta::set<_a, _b, _c, _d, _e, _f, _g> letters;

  using namespace nt2::meta;

  if (!has_key<numbers, _2>::value) return 1;
  if (!has_key<letters, _d>::value) return 1;
 
  if (has_key<numbers, _f>::value) return 1;
  if (has_key<letters, _0>::value) return 1;
}
