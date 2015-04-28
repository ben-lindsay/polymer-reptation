// ===========================================================================
// io_utils.cpp
// Author:  Ben Lindsay
// Date:    April 2015
// Includes write_state, data_to_buffer, and buffer_to_file. write_state()
// writes a file with indices from tail to head and their corresponding
// (x,y[,z]) coordinates. data_to_buffer() saves it, r, and r2 to the next
// slot int the buffer arrays. buffer_to_file() writes the buffer array data
// to file and clears the data from the buffer arrays.
// ===========================================================================

#include "globals.h"

// Write state<iteration>.dat file showing current polymer configuration
void write_state(void) {
  int i, j, ind;
  char nm[20];
  FILE *otp;

  sprintf( nm, "state%d.dat", it);
  otp = fopen(nm, "w");

  for (i=0; i<N; i++) {
    // Write from tail to head
    ind = (tail + i*incr + N) % N;
    fprintf(otp, "%8d", ind);
    for (j=0; j<Dim; j++) {
      fprintf(otp, "%8d", polymer[ind][j]);
    }
    fprintf(otp, "\n");
  }

  fclose(otp);
}

// Write data to buffer arrays
void data_to_buffer(void) {
  it_buff[buff_length] = it;
  r_buff[buff_length] = r;
  r2_buff[buff_length] = r2;
}

// Add data from buffer arrays to R.dat file, clearing buffer along the way
void buffer_to_file(void) {
  char nm[20];
  FILE *otp;
  int i;

  sprintf( nm, "R.dat");
  otp = fopen(nm, "a");

  for (i=0; i<buff_length; i++) {
    // Write data from buffer arrays to output file
    fprintf(otp, "%8d %8lf %8lf\n", it_buff[i], r_buff[i], r2_buff[i]);
    // Clear buffer as it's printed
    it_buff[i] = 0;
    r_buff[i] = r2_buff[i] = 0;
  }
  fclose(otp);
}
