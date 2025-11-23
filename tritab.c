#include "machine.h"
S(ok) { (o[s] + anchor)(b, o, t, a, r, s + 1); }
S(accept) { P, ok(b, o, t, a, r, s); }

static const char *string = "bat";
S(term_t) {
  if (string[b] == 't')
    ok(b + 1, o, t, a, r, s);
}
S(term_a) {
  if (string[b] == 'a')
    ok(b + 1, o, t, a, r, s);
}
S(term_b) {
  if (string[b] == 'b')
    ok(b + 1, o, t, a, r, s);
}
S(term_null) {
  if (string[b] == '\0')
    ok(b + 1, o, t, a, r, s);
}

N(tritab) {
  P;
  D('0'), T('3'), B(term_null), B(accept);
  D('3'), T('T'), T('T'), T('T');
  D('T'), B(term_t);
  D('T'), B(term_a);
  D('T'), B(term_b);
  go(b, o, t, a, r, s);
}
