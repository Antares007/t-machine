#pragma once

#define N(argo) void argo(int b, int *o, int t, int a, int r, int s)
/*
 o — tape, divided into int-sized cells
 t — text index representing the machine-head position
 a — advanced interpretation time
 r — ray; a branched, linked chain representing the current descent
     o[r+0] = upper-branch position in space
     o[r+1] = text index of the branched T-word
     o[r+2] = walk-book color at the moment the T-word was branched
 s — branching space and continuation stack of the books
*/
#define SN(argo) static N(argo)

#define P printf("%10s %d %d %d %d %d\n", __func__, b, t, a, r, s)
extern int printf(const char *__restrict __format, ...);
N(go);
N(anchor);

// start of definition; left-hand side of the grammar rule
#define D(symbol) o[a++] = 1, o[a++] = symbol
// block of axiomatic code, i.e., a terminal
#define B(narrative) o[a++] = 2, o[a++] = narrative - anchor
// reference to a definition, i.e., a left-hand-side symbol
#define T(symbol) o[a++] = 3, o[a++] = symbol
// NOTE: grammar rules are written in double-edged words.
