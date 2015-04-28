// ===========================================================================
// init.cpp
// Author:  Ben Lindsay
// Date:    April 2015
// Initializes global variables and allocates global arrays
// ===========================================================================

#include "globals.h"

void init(void) {
  int i, j;

  srand( time(0) ); // Seed random number generator
  ndir = Dim*2 - 1; // # of directions head could move. Dim=2->3, Dim=3->5
  direction = (int**) calloc( ndir , sizeof(int*) );
  for (i=0; i<ndir; i++) {
    direction[i] = (int*) calloc( Dim, sizeof(int) );
  }
  polymer = (int**) calloc( N, sizeof(int*) );
  for (i=0; i<N; i++) {
    polymer[i] = (int*) calloc( Dim, sizeof(int) );
  }
  c = (int*) calloc( Dim, sizeof(int) );
  it_buff = (int*) calloc( max_buff_length, sizeof(int) );
  r_buff = (double*) calloc( max_buff_length, sizeof(double) );
  r2_buff = (double*) calloc( max_buff_length, sizeof(double) );
  buff_length = 0;

  tail = 0; // index 0 starts as tail
  head = N-1; // index N-1 starts as head
  incr = 1; // +1 if moving in increasing index direction, -1 otherwise
  it = 0; // set current iteration to 0
  avg_r2 = 0; // average R^2
  n_accum = 0; // number of times accum_avgs has been called
  du = 0;

  // Initialize polymer chain with straight chain configuration
  for (i=0; i<N; i++) {
    polymer[i][0] = i - N/2;
    for (j=1; j<Dim; j++) {
      polymer[i][j] = 0; 
    }
  }
}
