// clang-format off
#include "machine.h"
S(ok) { (o[s] + anchor)(b, o, t, a, r, s + 1); }
S(accept) { P, ok(b, o, t, a, r, s); }

static const char *string = "bato";
S(term_o   ) { if (string[b] ==  'o') ok(b + 1, o, t, a, r, s); }
S(term_t   ) { if (string[b] ==  't') ok(b + 1, o, t, a, r, s); }
S(term_a   ) { if (string[b] ==  'a') ok(b + 1, o, t, a, r, s); }
S(term_b   ) { if (string[b] ==  'b') ok(b + 1, o, t, a, r, s); }
S(term_null) { if (string[b] == '\0') ok(b + 1, o, t, a, r, s); }

N(sa) {
  P;
  D('0'), T('S'), B(term_null), B(accept);
  D('S'), B(term_b);
  D('S'), T('S'), B(term_a);
  D('S'), T('S'), B(term_t);
  D('S'), T('S'), B(term_o);
  go(b, o, t, a, r, s);
}
