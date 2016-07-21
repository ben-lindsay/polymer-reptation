// ===========================================================================
// main.cpp
// Author:  Ben Lindsay
// Date:    April 2015
// One pass through the main method attempts <nit> reptation moves on a
// polymer chain of <N> monomers. The average end-to-end distance is output
// a the end.
// ===========================================================================

#define MAIN
#include "globals.h"

int main(int argc, char **argv) {

  int done = 0;

  FILE *otp ;
  // Create R.dat file. Overwrite R.dat if one exists
  otp = fopen("R.dat", "w");
  fclose(otp);

  if (argc > 1) {
    // If an argument is passed in, open the file with that name
    read_input(argv[1]);
  }
  else {
    // If no arguments are passed, open the file with default name param.inp
    read_input("param.inp");
  }

  printf("Dim = %d\nN = %d\n# of iterations = %d\n", Dim, N, nit);

  init(); // Initialize variables and allocate arrays

  while (!done) {
    if (rand_int(2)) {
      // Switch head and tail with 50/50 chance (same as randomly picking one)
      head = tail;
      incr = -incr;
      tail = (head+incr+N) % N;
    }
    // Randomly choose one of the directions available to the head
    choice(c);
    // Accept or reject move based on energy
    if (calc_du(c)) { // calc_du updates du, returns 1 if no intersection
      // Accept move if lower energy
      if (du < 0) accept(c);
      // Accept move with exp(-du) probability if higher energy
      else if (rand_dbl() < exp(-du)) accept(c);
    }
    if (++it % conf_freq == 0) {
      printf("Completed iteration %d\n", it);
      // Write file with current conformation every conf_freq iterations
      write_state();
    }
    // Do data calculation and update every data_freq iterations
    if (it % data_freq == 0) {
      calc_r(); // Calculate R and R^2
      data_to_buffer(); // Add R and R^2 to next slot in buffer arrays
      if (++buff_length==max_buff_length) {
        // If buffer arrays are full, ouput data to file and clear buffers
        buffer_to_file();
        buff_length = 0;
      }
    }
    if (it >= nit) { // Exit loop after last iteration
      done = 1;
    }
  }

  if (buff_length > 0) {
    // Output data in buffer arrays to file if buffers aren't empty
    buffer_to_file();
    buff_length = 0;
  }

  // Print final average R^2
  printf("Simulation complete. Average R^2:\n%lf\n", avg_r2);

  return 0;
}
