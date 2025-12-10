/* The c-machine is a discrete mathematical–linguistic construct defined directly within a
   hardware-oriented computational model:
   https://github.com/Antares007/t-machine

   The c-machine employs:
     * the C language’s call stack to support systematic backtracking;
     * an `int o[]` tape that encodes the grammar together with the machine’s operational state;
     * `int a` — a pointer marking the end of the grammar region on the tape;
              note: `a` may also be advanced beyond the grammar region to store backtracking information,
              enabling incremental parsing. This allows parsing in asynchronous scenarios.
     * `int s` — a pointer marking the lower boundary of the tape space used to record the branching
                 path (ray) chain during descent;
     * `int r` — the current branching ray chain associated with the active symbol.

   For a more advanced design in which the entire grammar and the full operational state of the machine —
   including the mechanisms for backtracking — are stored on a unified single tape (encompassing grammar,
   time, and space), see the JavaScript implementation:
   https://github.com/Antares007/s-machine
*/

// clang-format off

#define N(argo) void argo(const char*b, int *o, int t, int a, int r, int s)
#define S(argo) __attribute__((noinline)) static N(argo) 

N(anchor) {}
S(and                                         ) { (o[s] + anchor)(b, o, t, a, r, s + 1); }
S(or                                          ) { (void)"backtrack to choice"; }
S(Green_walk); S(Red_walk); S(Blue_walk);
S(Red_ascend                                  ) {   Red_walk(b, o, o[r + 1], a, o[r], s); }
S(Blue_ascend                                 ) {  Blue_walk(b, o, o[r + 1], a, o[r], s); }
S(Green_ascend                                ) { Green_walk(b, o, o[r + 1], a, o[r], s); }
S(Red_book_of_ascending                       ) { static N((*nars[])) = {or, Blue_ascend, Green_ascend, 0, Red_ascend};
                                                  nars[o[r + 2]](b, o, t, a, r, s); };
S(Yellow_descend);
S(cursor_Yellow_descend_Green_ascend          ) { (Green_ascend(b, o, t, a, r, s), Yellow_descend(b, o, t, a, r, s)); };
S(cursor_Yellow_descend_Blue_ascend           ) { ( Blue_ascend(b, o, t, a, r, s), Yellow_descend(b, o, t, a, r, s)); };
S(Blue_book_of_ascending                      ) { static N((*nars[])) = {Yellow_descend,
                                                                         cursor_Yellow_descend_Blue_ascend,
                                                                         cursor_Yellow_descend_Green_ascend,
                                                                         Blue_ascend,
                                                                         cursor_Yellow_descend_Green_ascend};
                                                  nars[o[r + 2]](b, o, t, a, r, s); };
S(Green_book_of_ascending                     ) { static N((*nars[])) = {Yellow_descend,
                                                                         cursor_Yellow_descend_Blue_ascend,
                                                                         cursor_Yellow_descend_Green_ascend,
                                                                         0,
                                                                         cursor_Yellow_descend_Green_ascend};
                                                  nars[o[r + 2]](b, o, t, a, r, s); };
S(Green_branch_Red_descend);
S(Green_book_of_walk);
S(Green_dispatch                              ) { o[--s] = Green_walk - anchor, (o[t + 1] + anchor)(b, o, t, a, r, s); }
S(Green_book_of_walk                          ) { static N((*nars[])) = {Green_book_of_ascending,
                                                                         Green_book_of_ascending,
                                                                         Green_dispatch,
                                                                         Green_branch_Red_descend};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Green_walk                                  ) { Green_book_of_walk(b, o, t + 2, a, r, s); }
S(Red_branch_Red_descend);
S(reTurn_else_Red_branch_Red_descend          ) { if (o[o[r + 1] + 1] == o[t + 1]) or(b, o, t, a, r,    s);
                                                  else             Red_branch_Red_descend(b, o, t, a, o[s], s + 1); }
S(Red_book_of_clr);
S(reTurn_or_Red_book_of_clr                   ) { if (o[o[r + 1] + 1] == o[t + 1]) or(b, o, t, a, r,    s);
                                                  else                    Red_book_of_clr(b, o, t, a, o[r], s); }
S(Red_book_of_clr                             ) { static N((*nars[])) = {reTurn_else_Red_branch_Red_descend,
                                                                         reTurn_else_Red_branch_Red_descend,
                                                                         reTurn_else_Red_branch_Red_descend,
                                                                         0,
                                                                         reTurn_or_Red_book_of_clr};
                                                  nars[o[r + 2]](b, o, t, a, r, s); };
S(Red_clr                                     ) { o[--s] = r, Red_book_of_clr(b, o, t, a, r, s); }
S(Red_book_of_walk                            ) { static N((*nars[])) = {Red_book_of_ascending,
                                                                         Red_book_of_ascending,
                                                                         Green_dispatch,
                                                                         Red_clr};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Red_walk                                    ) { Red_book_of_walk(b, o, t + 2, a, r, s); }
S(Blue_book_of_walk);
S(Blue_dispatch                               ) { o[--s] = Blue_walk - anchor, (o[t + 1] + anchor)(b, o, t, a, r, s); }
S(Blue_walk                                   ) { Blue_book_of_walk(b, o, t + 2, a, r, s); }
S(Blue_branch_Red_descend);
S(Blue_book_of_walk                           ) { static N((*nars[])) = {Blue_book_of_ascending,
                                                                         Blue_book_of_ascending,
                                                                         Blue_dispatch,
                                                                         Blue_branch_Red_descend};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Yellow_branch_Yellow_descend);
S(Blue_walk_else_Yellow_branch_Yellow_descend ) { if (o[o[r + 1] + 1] == o[t + 1]) Blue_walk(b, o, t, a, o[s], s + 1);
                                                  else          Yellow_branch_Yellow_descend(b, o, t, a, o[s], s + 1); }
S(Yellow_book_of_clr);
S(reTurn_or_Yellow_book_of_clr                ) { if (o[o[r + 1] + 1] == o[t + 1]) or(b, o, t, a, r,    s);
                                                  else                 Yellow_book_of_clr(b, o, t, a, o[r], s); }
S(Yellow_book_of_clr                          ) { static N((*nars[])) = {Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                         Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                         Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                         reTurn_or_Yellow_book_of_clr,
                                                                         Blue_walk_else_Yellow_branch_Yellow_descend};
                                                  nars[o[r + 2]](b, o, t, a, r, s); };
S(Yellow_clr                                  ) { o[--s] = r, Yellow_book_of_clr(b, o, t, a, r, s); }
S(Yellow_book_of_walk                         ) { static N((*nars[])) = {or, or, or, Yellow_clr};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Yellow_walk                                 ) { Yellow_book_of_walk(b, o, t + 2, a, r, s); }
S(Red_book_of_descending);
S(Red_descend                                 ) { Red_book_of_descending(b, o, 0, a, r, s); }
S(Red_next_dword                              ) { Red_book_of_descending(b, o, t + 2, a, r, s); }
S(Red_match_definition                        ) { if (o[o[r + 1] + 1] == o[t + 1]) (Red_walk(b, o, t, a, r, s), Red_next_dword(b, o, t, a, r, s));
                                                  else                        Red_next_dword(b, o, t, a, r, s); }
S(Red_book_of_descending                      ) { static N((*nars[])) = {or,
                                                                         Red_match_definition,
                                                                         Red_next_dword,
                                                                         Red_next_dword};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Yellow_book_of_descending);
S(Yellow_descend                              ) { Yellow_book_of_descending(b, o, 0, a, r, s); }
S(Yellow_next_dword                           ) { Yellow_book_of_descending(b, o, t + 2, a, r, s); }
S(Yellow_match_definition                     ) { if (o[o[r + 1] + 1] == o[t + 1]) (Yellow_walk(b, o, t, a, r, s), Yellow_next_dword(b, o, t, a, r, s));
                                                  else                        Yellow_next_dword(b, o, t, a, r, s); }
S(Yellow_book_of_descending                   ) { static N((*nars[])) = {or, Yellow_match_definition, Yellow_next_dword, Yellow_next_dword};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Pink_branch_Red_descend                     ) { o[--s] = 0, o[--s] = t, o[--s] = r, r = s,    Red_descend(b, o, t, a, r, s); }
S(Blue_branch_Red_descend                     ) { o[--s] = 1, o[--s] = t, o[--s] = r, r = s,    Red_descend(b, o, t, a, r, s); }
S(Green_branch_Red_descend                    ) { o[--s] = 2, o[--s] = t, o[--s] = r, r = s,    Red_descend(b, o, t, a, r, s); }
S(Yellow_branch_Yellow_descend                ) { o[--s] = 3, o[--s] = t, o[--s] = r, r = s, Yellow_descend(b, o, t, a, r, s); }
S(Red_branch_Red_descend                      ) { o[--s] = 4, o[--s] = t, o[--s] = r, r = s,    Red_descend(b, o, t, a, r, s); }
S(go                                          ) { o[a++] = 0,                       Pink_branch_Red_descend(b, o, t, a, r, s); }

S(term_1     ) { (*b == '1' ? and : or)(b + 1, o, t, a, r, s); }
S(term_2     ) { (*b == '2' ? and : or)(b + 1, o, t, a, r, s); }
S(term_3     ) { (*b == '3' ? and : or)(b + 1, o, t, a, r, s); }
S(term_oparen) { (*b == '(' ? and : or)(b + 1, o, t, a, r, s); }
S(term_cparen) { (*b == ')' ? and : or)(b + 1, o, t, a, r, s); }
S(term_plus  ) { (*b == '+' ? and : or)(b + 1, o, t, a, r, s); }
S(term_minus ) { (*b == '-' ? and : or)(b + 1, o, t, a, r, s); }
S(term_bang  ) { (*b == '!' ? and : or)(b + 1, o, t, a, r, s); }
S(term_mul   ) { (*b == '*' ? and : or)(b + 1, o, t, a, r, s); }
S(term_div   ) { (*b == '/' ? and : or)(b + 1, o, t, a, r, s); }
S(term_null  ) { (*b == '\0'? and : or)(b + 1, o, t, a, r, s); }

#include<stdio.h>
S(accept     ) { printf("%s\n", __func__), and(b, o, t, a, r, s); }
int main() {
  int b = 0;
  int o[1024];
  int t = 0;
  int a = 0;
  int r = 0;
  int s = sizeof(o) / sizeof(*o);

enum symbols {
  S,
  expression,
  constant,
  primary,
  unary,
  multiplicative,
  additive,
};
// start of definition; left-hand side of the grammar rule
#define D(symbol) o[a++] = 1, o[a++] = symbol
// block of axiomatic code; terminal
#define B(block) o[a++] = 2, o[a++] = block - anchor
// reference to a definition
#define T(symbol) o[a++] = 3, o[a++] = symbol

  D(S), T(expression), B(term_null), B(accept);

  D(constant), B(term_1);
  D(constant), B(term_2);
  D(constant), B(term_3);

  D(primary), T(constant);
  D(primary), B(term_oparen), T(expression), B(term_cparen);

  D(unary), T(primary);
  D(unary), B(term_minus), T(unary);
  D(unary), B(term_bang), T(unary);

  D(multiplicative), T(unary);
  D(multiplicative), T(multiplicative), B(term_mul), T(unary);
  D(multiplicative), T(multiplicative), B(term_div), T(unary);

  D(additive), T(multiplicative);
  D(additive), T(additive), B(term_plus), T(multiplicative);
  D(additive), T(additive), B(term_minus), T(multiplicative);

  D(expression), T(additive);

  go("1+(2*3)", o, t, a, r, s);
  go("2+(2*3)", o, t, a, r, s);
  go("3+(2*3)", o, t, a, r, s);
}
