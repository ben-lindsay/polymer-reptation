// ===========================================================================
// move_utils.cpp
// Author:  Ben Lindsay
// Date:    April 2015
// Contains choice, calc_du, accept, and shift, which do most of the work
// related to moving the polymer. choice() chooses a direction for the head to
// move. calc_du() determines the energy difference between the current state
// and the proposed state. accept() moves the tail monomer to the proposed
// move direction to simulate reptation in that direction. shift() moves the
// polymer back to the origin when called to prevent excessive drift.
// ===========================================================================

#include "globals.h"

// Choose a direction to try to move the polymer
void choice(int *cvec) {
  int i, j, hm, r, dum, move_dim, count;

  // Zero the entries of the direction vector
  for (i=0; i<ndir; i++) {
    for (j=0; j<Dim; j++) {
      direction[i][j] = 0;
    }
  }

  // Get the index of the monomer connected to the head
  hm = (head-incr+N) % N;

  // Set direction[0] to the vector pointing straight ahead
  for (i=0; i<Dim; i++) {
    dum = polymer[head][i] - polymer[hm][i]; // dum = +/- 1 or 0
    if (dum != 0) move_dim = i;
    direction[0][i] = dum;
  }

  // Set remaining direction[k]'s
  count = 1;
  for (i=0; i<Dim; i++) {
    // the direction[k]'s point +/- 1 in directions other than straight ahead
    if (i==move_dim) continue;
    direction[count][i] = 1;
    count++;
    direction[count][i] = -1;
    count++;
  }
  if (count != ndir) {
    printf("Something went wrong with setting the direction vectors.\n");
    printf("count = %d\n", count);
    exit(1);
  }

  // Choose one of the directions randomly and assign cvec
  r = rand_int(ndir);
  for (i=0; i<Dim; i++) {
    cvec[i] = direction[r][i];
  }
}

// Returns 0 if tested direction is occupied, 1 if available and du is
// calculated.
int calc_du(int *cvec) {

  int i, j, tm;
  int d_head, d_tail, d_new_head, d_new_tail;
  int nn_head, nn_tail, nn_new_head, nn_new_tail;

  // Get the index of the monomer connected to the tail
  tm = (tail+incr+N) % N;

  // Set number of neighbors variables to 0
  nn_head = nn_tail = nn_new_head = nn_new_tail = 0;
    
  // Loop over all monomers
  for (i=0; i<N; i++) {

    // Set accumulative distances to 0
    d_head = d_tail = d_new_head = d_new_tail = 0;

    // Loop over all dimensions
    for (j=0; j<Dim; j++) {
      // Increment accumulative distances with distances in each dimension
      d_head += abs( polymer[i][j] - polymer[head][j] );
      d_tail += abs( polymer[i][j] - polymer[tail][j] );
      d_new_head += abs( polymer[i][j] - ( polymer[head][j] + cvec[j] ) );
      d_new_tail += abs( polymer[i][j] - polymer[tm][j] );
    } // j loop (0 to Dim)

    // If the proposed site to move to is occupies, exit and return 0
    if (d_new_head == 0) return 0;
    // Otherwise, increment neighbor variables if applicable
    else if (d_new_head == 1) nn_new_head++;
    if (d_new_tail == 1) nn_new_tail++;
    if (d_head == 1) nn_head++;
    if (d_tail == 1) nn_tail++;

    // If du speedup mode is set and monomer is far enough from head and tail
    // monomoers, skip evaluation of monomers that don't matter
    if (du_speedup_on && d_head>3 && d_tail>3) i += min(d_head,d_tail) - 3;

  } // i loop (0 to N)

  // Evaluate du by multiplying the energy per neighbor by the difference in
  // total neighbors between proposed state and current state
  du = eps * (nn_new_head + nn_new_tail - nn_head - nn_tail);

  // If we got here without returning, there's no intersection
  return 1;
}

// Move polymer by moving the monomer at the tail to the newly accepted
// position.
void accept (int *cvec) {
  int hp, i;

  hp = (head + incr + N) % N;
  for (i=0; i<Dim; i++) {
    polymer[hp][i] = cvec[i] + polymer[head][i];
  }
  head = hp;
  tail = (head + incr + N) % N;
  for (i=0; i<Dim; i++) {
    // Shift polymer back to origin if out of bounds
    if ( abs(polymer[head][i]) > 2*N ) {
      shift();
    }
  }
}

// Shift polymer so that head is at origin
void shift(void) {
  int i, j;
  int tmp[Dim];

  // Get current position of head
  for (i=0; i<Dim; i++) {
    tmp[i] = polymer[head][i];
  }

  // Shift polymer so the head is at the origin.
  for (i=0; i<N; i++) {
    for (j=0; j<Dim; j++) {
        polymer[i][j] -= tmp[j];
    }
  }
}
