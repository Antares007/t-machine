// clang-format off
// α-machine
#define N(argo) void argo(int b, int *o, int t, int a, int r, int s)
#define S(argo) static N(argo)
typedef enum { Pink, Blue, Green, Yellow, Red } Walk_book_colors;
N(anchor) {}
S(reTurn) {}
S(Green_walk); S(Red_walk); S(Blue_walk);
S(Red_ascend                                  ) {   Red_walk(b, o, o[r + 1], a, o[r], s); }
S(Blue_ascend                                 ) {  Blue_walk(b, o, o[r + 1], a, o[r], s); }
S(Green_ascend                                ) { Green_walk(b, o, o[r + 1], a, o[r], s); }
S(Red_book_of_ascending                       ) { static N((*nars[])) = {reTurn, Blue_ascend, Green_ascend, 0, Red_ascend};
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
S(reTurn_else_Red_branch_Red_descend          ) { if (o[o[r + 1] + 1] == o[t + 1]) reTurn(b, o, t, a, r,    s);
                                                  else             Red_branch_Red_descend(b, o, t, a, o[s], s + 1); }
S(Red_book_of_clr);
S(reTurn_or_Red_book_of_clr                   ) { if (o[o[r + 1] + 1] == o[t + 1]) reTurn(b, o, t, a, r,    s);
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
S(reTurn_or_Yellow_book_of_clr                ) { if (o[o[r + 1] + 1] == o[t + 1]) reTurn(b, o, t, a, r,    s);
                                                  else                 Yellow_book_of_clr(b, o, t, a, o[r], s); }
N(Yellow_book_of_clr                          ) { static N((*nars[])) = {Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                         Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                         Blue_walk_else_Yellow_branch_Yellow_descend,
                                                                         reTurn_or_Yellow_book_of_clr,
                                                                         Blue_walk_else_Yellow_branch_Yellow_descend};
                                                  nars[o[r + 2]](b, o, t, a, r, s); };
S(Yellow_clr                                  ) { o[--s] = r, Yellow_book_of_clr(b, o, t, a, r, s); }
S(Yellow_book_of_walk                         ) { static N((*nars[])) = {reTurn, reTurn, reTurn, Yellow_clr};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Yellow_walk                                 ) { Yellow_book_of_walk(b, o, t + 2, a, r, s); }
S(Red_book_of_descending);
S(Red_descend                                 ) { Red_book_of_descending(b, o, 0, a, r, s); }
S(Red_next_dword                              ) { Red_book_of_descending(b, o, t + 2, a, r, s); }
S(Red_match_definition                        ) { if (o[o[r + 1] + 1] == o[t + 1]) (Red_walk(b, o, t, a, r, s), Red_next_dword(b, o, t, a, r, s));
                                                  else                        Red_next_dword(b, o, t, a, r, s); }
N(Red_book_of_descending                      ) { static N((*nars[])) = {reTurn,
                                                                         Red_match_definition,
                                                                         Red_next_dword,
                                                                         Red_next_dword};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Yellow_book_of_descending);
S(Yellow_descend                              ) { Yellow_book_of_descending(b, o, 0, a, r, s); }
S(Yellow_next_dword                           ) { Yellow_book_of_descending(b, o, t + 2, a, r, s); }
S(Yellow_match_definition                     ) { if (o[o[r + 1] + 1] == o[t + 1]) (Yellow_walk(b, o, t, a, r, s), Yellow_next_dword(b, o, t, a, r, s));
                                                  else                        Yellow_next_dword(b, o, t, a, r, s); }
N(Yellow_book_of_descending                   ) { static N((*nars[])) = {reTurn, Yellow_match_definition, Yellow_next_dword, Yellow_next_dword};
                                                  nars[o[t]](b, o, t, a, r, s); };
S(Pink_branch_Red_descend                     ) { o[--s] = Pink,    o[--s] = t, o[--s] = r,    Red_descend(b, o, t, a, s, s); }
S(Blue_branch_Red_descend                     ) { o[--s] = Blue,    o[--s] = t, o[--s] = r,    Red_descend(b, o, t, a, s, s); }
S(Green_branch_Red_descend                    ) { o[--s] = Green,   o[--s] = t, o[--s] = r,    Red_descend(b, o, t, a, s, s); }
S(Red_branch_Red_descend                      ) { o[--s] = Red,     o[--s] = t, o[--s] = r,    Red_descend(b, o, t, a, s, s); }
S(Yellow_branch_Yellow_descend                ) { o[--s] = Yellow,  o[--s] = t, o[--s] = r, Yellow_descend(b, o, t, a, s, s); }
N(go                                          ) { o[a++] = 0,                      Pink_branch_Red_descend(b, o, t, a, r, s); }

N(sa);
N(tritab);
N(math_expr);
int main() {
  int b = 0;
  int o[1024];
  int t = 0;
  int a = 0;
  int r = 0;
  int s = sizeof(o) / sizeof(*o);
  sa(b, o, t, a, r, s);
  tritab(b, o, t, a, r, s);
  math_expr(b, o, t, a, r, s);
}
