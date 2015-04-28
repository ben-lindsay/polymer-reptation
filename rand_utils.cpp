// ===========================================================================
// rand_utils.cpp
// Author:  Ben Lindsay
// Date:    April 2015
// Contains rand_int and rand_dbl
// ===========================================================================

#include "globals.h"

// Returns random int in range [0,n)
int rand_int(int n) {
  double a = double(rand()) / RAND_MAX;
  return int(a*double(n));
}

// Returns random double in range [0,1)
double rand_dbl(void) {
  return double(rand()) / RAND_MAX;
}
