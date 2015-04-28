// ===========================================================================
// read_input.cpp
// Author:  Ben Lindsay
// Date:    April 2015
// Reads values listed in input file of name <nm> passed to this function.
// Sets global variables to associated values.
// ===========================================================================

#include "globals.h"

void read_input(char *nm) {

  FILE *inp;
  // Open file of name nm
  inp = fopen(nm, "r");

  if (inp==NULL) { 
    printf("Failed to open input file %s", nm);
    exit(1);
  }

  char tt[80];

  // Read Parameters
  fscanf(inp, "%d", &Dim);             fgets(tt, 80, inp);
  fscanf(inp, "%d", &N);               fgets(tt, 80, inp);
  fscanf(inp, "%lf", &eps);            fgets(tt, 80, inp);
  fscanf(inp, "%d", &cut);             fgets(tt, 80, inp);
  fscanf(inp, "%d", &conf_freq);       fgets(tt, 80, inp);
  fscanf(inp, "%d", &data_freq);       fgets(tt, 80, inp);
  fscanf(inp, "%d", &max_buff_length); fgets(tt, 80, inp);
  fscanf(inp, "%d", &nit);             fgets(tt, 80, inp);
  fscanf(inp, "%d", &du_speedup_on);   fgets(tt, 80, inp);
}
