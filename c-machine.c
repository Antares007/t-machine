/* The c-machine is a discrete mathematical–linguistic construct defined in a 
   hardware-oriented computational model:
   https://github.com/Antares007/t-machine

   The machine uses:
     * `int o[]` — a single tape that stores both the grammar and the machine’s 
                   operational state. Grammar rules live at the start of the tape and 
                   are encoded using meta-opcodes 1, 2, and 3. A `0` marks the end 
                   of the grammar section.

     * `int a` — a pointer used to store backtracking information. This makes 
                 incremental and asynchronous parsing possible.

     * `int s` — a pointer marking the lower boundary of tape space reserved for 
                 recording the branching (ray) chain during descent.

     * `int r` — the current branching ray chain associated with the active symbol.

*/

// clang-format off
#define N(argo) void argo(int b, int *o, int t, int a, int r, int s)
#define S(argo) __attribute__((noinline)) static N(argo) 
#define C b, o, t, a, r, s
enum color_index { Pink = 0, Blue = 1, Green = 2, Yellow = 3, Red = 4 };
enum opcode_meanings_in_books { Dot_0 = 0, Dot_1 = 1, Block = 2, Tword = 3 };
N(anchor) {}
S(and                                         ) { int os = o[s++]; (anchor + os)(C); }
S(or                                          ) { int oa = o[--a]; (anchor + oa)(C); }
S(Green_walk); S(Red_walk); S(Blue_walk);
S(Red_ascend                                  ) { t = o[r + 1], r = o[r],   Red_walk(C); }
S(Blue_ascend                                 ) { t = o[r + 1], r = o[r],  Blue_walk(C); }
S(Green_ascend                                ) { t = o[r + 1], r = o[r], Green_walk(C); }
S(Red_book_of_ascending                       ) { static N((*nars[])) = { [Pink  ] = or,
                                                                          [Blue  ] = Blue_ascend,
                                                                          [Green ] = Green_ascend,
                                                                          [Yellow] = 0,
                                                                          [Red   ] = Red_ascend};
                                                  nars[o[r + 2]](C); };

S(choose                                      ) { s = o[--a];
                                                  r = o[--a];
                                                  t = o[--a];
                                                  b = o[--a],
                                                  or(C); }

S(choice                                      ) { int n = o[s++];
                                                  o[a++] = b,
                                                  o[a++] = t,
                                                  o[a++] = r,
                                                  o[a++] = s,
                                                  o[a++] = choose - anchor,
                                                  (n + anchor)(C); }

S(Yellow_descend);
S(cursor_Yellow_descend_Green_ascend          ) { o[--s] = Green_ascend - anchor,
                                                  o[a++] = Yellow_descend - anchor,
                                                  choice(C); };
S(cursor_Yellow_descend_Blue_ascend           ) { o[--s] =  Blue_ascend - anchor,
                                                  o[a++] = Yellow_descend - anchor,
                                                  choice(C); };
S(Blue_book_of_ascending                      ) { static N((*nars[])) = { [Pink  ] = Yellow_descend,
                                                                          [Blue  ] = cursor_Yellow_descend_Blue_ascend,
                                                                          [Green ] = cursor_Yellow_descend_Green_ascend,
                                                                          [Yellow] = Blue_ascend,
                                                                          [Red   ] = cursor_Yellow_descend_Green_ascend};
                                                  nars[o[r + 2]](C); };
S(Green_book_of_ascending                     ) { static N((*nars[])) = { [Pink  ] = Yellow_descend,
                                                                          [Blue  ] = cursor_Yellow_descend_Blue_ascend,
                                                                          [Green ] = cursor_Yellow_descend_Green_ascend,
                                                                          [Yellow] = 0,
                                                                          [Red   ] = cursor_Yellow_descend_Green_ascend};
                                                  nars[o[r + 2]](C); };
S(Green_branch_Red_descend);
S(Green_book_of_walk);
S(Green_dispatch                              ) { o[--s] = Green_walk - anchor, (o[t + 1] + anchor)(C); }
S(Green_book_of_walk                          ) { static N((*nars[])) = { [Dot_0] = Green_book_of_ascending,
                                                                          [Dot_1] = Green_book_of_ascending,
                                                                          [Block] = Green_dispatch,
                                                                          [Tword] = Green_branch_Red_descend};
                                                  nars[o[t]](C); };
S(Green_walk                                  ) { t += 2, Green_book_of_walk(C); }
S(Red_branch_Red_descend);
S(reTurn_else_Red_branch_Red_descend          ) { if (o[o[r + 1] + 1] == o[t + 1]) or(C);
                                                  else r = o[s++], Red_branch_Red_descend(C); }
S(Red_book_of_clr);
S(reTurn_or_Red_book_of_clr                   ) { if (o[o[r + 1] + 1] == o[t + 1]) or(C);
                                                  else r = o[r], Red_book_of_clr(C); }
S(Red_book_of_clr                             ) { static N((*nars[])) = { [Pink  ] = reTurn_else_Red_branch_Red_descend,
                                                                          [Blue  ] = reTurn_else_Red_branch_Red_descend,
                                                                          [Green ] = reTurn_else_Red_branch_Red_descend,
                                                                          [Yellow] = 0,
                                                                          [Red   ] = reTurn_or_Red_book_of_clr};
                                                  nars[o[r + 2]](C); };
S(Red_clr                                     ) { o[--s] = r, Red_book_of_clr(C); }
S(Red_book_of_walk                            ) { static N((*nars[])) = { [Dot_0] = Red_book_of_ascending,
                                                                          [Dot_1] = Red_book_of_ascending,
                                                                          [Block] = Green_dispatch,
                                                                          [Tword] = Red_clr};
                                                  nars[o[t]](C); };
S(Red_walk                                    ) { t += 2, Red_book_of_walk(C); }
S(Blue_book_of_walk);
S(Blue_dispatch                               ) { o[--s] = Blue_walk - anchor, (o[t + 1] + anchor)(C); }
S(Blue_walk                                   ) { t += 2, Blue_book_of_walk(C); }
S(Blue_branch_Red_descend);
S(Blue_book_of_walk                           ) { static N((*nars[])) = { [Dot_0] = Blue_book_of_ascending,
                                                                          [Dot_1] = Blue_book_of_ascending,
                                                                          [Block] = Blue_dispatch,
                                                                          [Tword] = Blue_branch_Red_descend};
                                                  nars[o[t]](C); };
S(Yellow_branch_Yellow_descend);
S(Blue_walk_else_Yellow_branch_Yellow_descend ) { if (o[o[r + 1] + 1] == o[t + 1]) r = o[s++], Blue_walk(C);
                                                  else r = o[s++], Yellow_branch_Yellow_descend(C); }
S(Yellow_book_of_clr);
S(reTurn_or_Yellow_book_of_clr                ) { if (o[o[r + 1] + 1] == o[t + 1]) or(C);
                                                  else r = o[r], Yellow_book_of_clr(C); }
S(Yellow_book_of_clr                          ) { static N((*nars[])) = { [Pink  ] = Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                          [Blue  ] = Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                          [Green ] = Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                          [Yellow] = reTurn_or_Yellow_book_of_clr,
                                                                          [Red   ] = Blue_walk_else_Yellow_branch_Yellow_descend};
                                                  nars[o[r + 2]](C); };
S(Yellow_clr                                  ) { o[--s] = r, Yellow_book_of_clr(C); }
S(Yellow_book_of_walk                         ) { static N((*nars[])) = { [Dot_0] = or,
                                                                          [Dot_1] = or,
                                                                          [Block] = or,
                                                                          [Tword] = Yellow_clr};
                                                  nars[o[t]](C); };
S(Yellow_walk                                 ) { t += 2, Yellow_book_of_walk(C); }
S(Red_book_of_descending);
S(Red_descend                                 ) { t  = 0, Red_book_of_descending(C); }
S(Red_descend2                                ) { t += 2, Red_book_of_descending(C); }
S(Red_match_definition                        ) { if (o[o[r + 1] + 1] == o[t + 1])
                                                    o[--s] = Red_walk - anchor,
                                                    o[a++] = Red_descend2 - anchor,
                                                    choice(C);
                                                  else Red_descend2(C); }
S(Red_book_of_descending                      ) { static N((*nars[])) = { [Dot_0] = or,
                                                                          [Dot_1] = Red_match_definition,
                                                                          [Block] = Red_descend2,
                                                                          [Tword] = Red_descend2};
                                                  nars[o[t]](C); };
S(Yellow_book_of_descending);
S(Yellow_descend                              ) { t  = 0, Yellow_book_of_descending(C); }
S(Yellow_descend2                             ) { t += 2, Yellow_book_of_descending(C); }
S(Yellow_match_definition                     ) { if (o[o[r + 1] + 1] == o[t + 1])
                                                    o[--s] = Yellow_walk - anchor,
                                                    o[a++] = Yellow_descend2 - anchor,
                                                    choice(C);
                                                  else Yellow_descend2(C); }
S(Yellow_book_of_descending                   ) { static N((*nars[])) = { [Dot_0] = or,
                                                                          [Dot_1] = Yellow_match_definition,
                                                                          [Block] = Yellow_descend2,
                                                                          [Tword] = Yellow_descend2};
                                                  nars[o[t]](C); };
S(Pink_branch_Red_descend                     ) { o[--s] = Pink,   o[--s] = t, o[--s] = r, r = s,    Red_descend(C); }
S(Blue_branch_Red_descend                     ) { o[--s] = Blue,   o[--s] = t, o[--s] = r, r = s,    Red_descend(C); }
S(Green_branch_Red_descend                    ) { o[--s] = Green,  o[--s] = t, o[--s] = r, r = s,    Red_descend(C); }
S(Yellow_branch_Yellow_descend                ) { o[--s] = Yellow, o[--s] = t, o[--s] = r, r = s, Yellow_descend(C); }
S(Red_branch_Red_descend                      ) { o[--s] = Red,    o[--s] = t, o[--s] = r, r = s,    Red_descend(C); }
S(go                                          ) { o[a++] = 0,                            Pink_branch_Red_descend(C); }

static const char*in;
S(term_1     ) { (in[b] == '1' ? and : or)(b + 1, o, t, a, r, s); }
S(term_2     ) { (in[b] == '2' ? and : or)(b + 1, o, t, a, r, s); }
S(term_3     ) { (in[b] == '3' ? and : or)(b + 1, o, t, a, r, s); }
S(term_oparen) { (in[b] == '(' ? and : or)(b + 1, o, t, a, r, s); }
S(term_cparen) { (in[b] == ')' ? and : or)(b + 1, o, t, a, r, s); }
S(term_plus  ) { (in[b] == '+' ? and : or)(b + 1, o, t, a, r, s); }
S(term_minus ) { (in[b] == '-' ? and : or)(b + 1, o, t, a, r, s); }
S(term_bang  ) { (in[b] == '!' ? and : or)(b + 1, o, t, a, r, s); }
S(term_mul   ) { (in[b] == '*' ? and : or)(b + 1, o, t, a, r, s); }
S(term_div   ) { (in[b] == '/' ? and : or)(b + 1, o, t, a, r, s); }
S(term_null  ) { (in[b] == '\0'? and : or)(b + 1, o, t, a, r, s); }

#include<stdio.h>
S(accept     ) { printf("%s\n", __func__), and(C); }

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


  in = "1+(2*3)", go(C);
  in = "2+(2*3)", go(C);
  in = "3+(2*3)", go(C);
}
