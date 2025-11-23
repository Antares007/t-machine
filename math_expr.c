// clang-format off
#include "machine.h"
S(ok) { (o[s] + anchor)(b, o, t, a, r, s + 1); }
S(accept) { P, ok(b, o, t, a, r, s); }

static const char *string = "!!3+(2*3)";
S(term_1     ) { if (string[b] ==  '1') ok(b + 1, o, t, a, r, s); }
S(term_2     ) { if (string[b] ==  '2') ok(b + 1, o, t, a, r, s); }
S(term_3     ) { if (string[b] ==  '3') ok(b + 1, o, t, a, r, s); }
S(term_oparen) { if (string[b] ==  '(') ok(b + 1, o, t, a, r, s); }
S(term_cparen) { if (string[b] ==  ')') ok(b + 1, o, t, a, r, s); }
S(term_plus  ) { if (string[b] ==  '+') ok(b + 1, o, t, a, r, s); }
S(term_minus ) { if (string[b] ==  '-') ok(b + 1, o, t, a, r, s); }
S(term_bang  ) { if (string[b] ==  '!') ok(b + 1, o, t, a, r, s); }
S(term_mul   ) { if (string[b] ==  '*') ok(b + 1, o, t, a, r, s); }
S(term_div   ) { if (string[b] ==  '/') ok(b + 1, o, t, a, r, s); }
S(term_null  ) { if (string[b] == '\0') ok(b + 1, o, t, a, r, s); }
enum symbols {
  expression,
  constant,
  primary_expression,
  unary_expression,
  multiplicative_expression,
  additive_expression,
};
N(math_expr) {
  P;
  // clang-format off
  D(0),                         T(expression), B(term_null), B(accept);

  D(constant),                  B(term_1);
  D(constant),                  B(term_2);
  D(constant),                  B(term_3);

  D(primary_expression),        T(constant);
  D(primary_expression),        B(term_oparen), T(expression), B(term_cparen);

  D(unary_expression),          T(primary_expression);
  D(unary_expression),          B(term_minus),  T(unary_expression);
  D(unary_expression),          B(term_bang),   T(unary_expression);

  D(multiplicative_expression), T(unary_expression);
  D(multiplicative_expression), T(multiplicative_expression), B(term_mul), T(unary_expression);
  D(multiplicative_expression), T(multiplicative_expression), B(term_div), T(unary_expression);

  D(additive_expression),       T(multiplicative_expression);
  D(additive_expression),       T(additive_expression),       B(term_plus), T(multiplicative_expression);
  D(additive_expression),       T(additive_expression),       B(term_minus), T(multiplicative_expression);

  D(expression),                T(additive_expression);

  go(b, o, t, a, r, s);
}
