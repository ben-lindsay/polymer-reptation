// ===========================================================================
// globals.h - Declares global variables and functions
// ===========================================================================

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define min(a,b) (((a)<(b))?(a):(b))

#ifndef MAIN
extern
#endif
int **direction, **polymer, *c, *it_buff;

#ifndef MAIN
extern
#endif
int Dim, N, cut, conf_freq, data_freq, nit,
      wall, Lx, ndir, head, tail, incr, it, n_accum, du_speedup_on,
      buff_length, max_buff_length;

#ifndef MAIN
extern
#endif
double r, r2, avg_r2, *r_buff, *r2_buff, du, eps;

void read_input(char*);
void init(void);
void choice(int*);
int calc_du(int*);
void accept(int*);
void shift(void);
int rand_int(int);
double rand_dbl(void);
void write_state(void);
void data_to_buffer(void);
void buffer_to_file(void);
void accum_avgs(void);
void calc_r(void);
