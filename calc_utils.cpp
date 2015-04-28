// ===========================================================================
// calc_utils.cpp
// Author:  Ben Lindsay
// Date:    April 2015
// calc_r() calculates r (end-to-end distance R) and r2 (R^2)
// ===========================================================================

#include "globals.h"

// Calculate r and r2
void calc_r(void) {
  int i;
  double dum;

  // Zero out dum, r, and r2
  dum = r = r2 = 0;
  // Calculate r2
  for (i=0; i<Dim; i++) {
    dum = polymer[head][i] - polymer[tail][i];
    r2 += dum * dum;
  }
  // Take sqrt to get r
  r = sqrt(r2);
  
  // Make sure r2 is reasonable. If not, exit simulation
  if (r2 > (N-1)*(N-1)) {
    printf("R^2 is too big at iteration %d\n", it);
    write_state();
    exit(1);
  }

  // Update average r2 if we're past the equilibration cutoff
  if (it > cut) {
    n_accum++;
    avg_r2 = double(n_accum-1)/n_accum * avg_r2 + r2/n_accum;
  }
}
