#include <stdint.h>
#include <stdio.h>
#define Narrative(go) void go(intptr_t *o, intptr_t s, intptr_t t)
#define BookOf(S)                                                              \
  Narrative(S) {                                                               \
    printf("%-5s %ld ", #S, o[t]);                                             \
    for (intptr_t i = 0; i < 10; i++)                                          \
      printf("%ld", o[i]);                                                     \
    static Narrative((*nars[])) = {S##0, S##1};                                \
    nars[o[t]](o, s, t);                                                       \
  }

/* https://en.wikipedia.org/wiki/Turing_machine_examples#A_copy_subroutine */

#define E printf(" E "), o[t] = 0
#define P1 printf(" P1"), o[t] = 1
#define R(c) printf(" R %s\n", #c), (c)(o, s, t + 1)
#define L(c) printf(" L %s\n", #c), (c)(o, s, t - 1)
#define N(c) printf(" N %s\n", #c), (c)(o, s, t)

Narrative(H0) {}
Narrative(H1) {}
BookOf(H);

Narrative(s5);
Narrative(s1);
Narrative(s50) { P1, R(s1); }
Narrative(s51) { P1, L(s5); }
BookOf(s5);

Narrative(s4);
Narrative(s40) { E, L(s5); }
Narrative(s41) { P1, L(s4); }
BookOf(s4);

Narrative(s3);
Narrative(s30) { P1, L(s4); }
Narrative(s31) { P1, R(s3); }
BookOf(s3);

Narrative(s2);
Narrative(s20) { E, R(s3); }
Narrative(s21) { P1, R(s2); }
BookOf(s2);

Narrative(s10) { N(H); }
Narrative(s11) { E, R(s2); }
BookOf(s1);

int main() {
  intptr_t o[1024] = {0};
  intptr_t s = 0;
  o[s++] = 1;
  o[s++] = 1;
  o[s++] = 0;
  s1(o, s, 0);
}
