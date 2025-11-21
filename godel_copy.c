// clang-format off
void  H0(char *o, char s) {}
void  H1(char *o, char s) {}
void   H(char *o, char s) { static void (*narg[])(char *o, char s) = {H0, H1};
                            narg[o[s]](o, s); };
void  s5(char *o, char s);
void  s1(char *o, char s);
void s50(char *o, char s) { o[s] = 1, (s1)(o, s + 1); }
void s51(char *o, char s) { o[s] = 1, (s5)(o, s - 1); }
void  s5(char *o, char s) { static void (*narg[])(char *o, char s) = {s50, s51};
                            narg[o[s]](o, s); };
void  s4(char *o, char s);
void s40(char *o, char s) { o[s] = 0, (s5)(o, s - 1); }
void s41(char *o, char s) { o[s] = 1, (s4)(o, s - 1); }
void  s4(char *o, char s) { static void (*narg[])(char *o, char s) = {s40, s41};
                            narg[o[s]](o, s); };
void  s3(char *o, char s);
void s30(char *o, char s) { o[s] = 1, (s4)(o, s - 1); }
void s31(char *o, char s) { o[s] = 1, (s3)(o, s + 1); }
void  s3(char *o, char s) { static void (*narg[])(char *o, char s) = {s30, s31};
                            narg[o[s]](o, s); };
void  s2(char *o, char s);
void s20(char *o, char s) { o[s] = 0, (s3)(o, s + 1); }
void s21(char *o, char s) { o[s] = 1, (s2)(o, s + 1); }
void  s2(char *o, char s) { static void (*narg[])(char *o, char s) = {s20, s21};
                            narg[o[s]](o, s); };
void s10(char *o, char s) { (H)(o, s); }
void s11(char *o, char s) { o[s] = 0, (s2)(o, s + 1); }
void  s1(char *o, char s) { static void (*narg[])(char *o, char s) = {s10, s11};
                            narg[o[s]](o, s); };
int main(               ) { char o[1024], s = 0;
                            o[s++] = 1, o[s++] = 1, o[s++] = 0, s1(o, 0); }
