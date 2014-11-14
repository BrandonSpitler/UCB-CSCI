#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;
  int width, height, dim, divisor, i, j, row, col;
  int rsub1, r1, r2, r3, r4, r5, r6, csub1, c1, c2, c3;
  int value0, value1, value2, value3, value4, value5,
      value6, value7, value8, value9, value10, value11, 
      value12, value13, value14, value15, value16, 
      value17, value18, value19, value20, value21, 
      value22, value23, value24, value25, value26, 
      value27, value28, value29, value30, value31, 
      value32, value33, value34, value35, value36, 
      value37, value38, value39, value40, value41, 
      value42, value43, value44, value45, value46, 
      value47, value48, value49, value50, value51,
      value52, value53;

  cycStart = rdtscll();
  
  width = input -> width - 1;
  height = input -> height - 1;
  dim = filter -> getSize();
  divisor = filter -> getDivisor();
  
  output -> width = width;
  output -> height = height;

  int filter_get[dim][dim];

  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      filter_get[i][j] = filter -> get(i, j);
    }
  }

  for(row = 1; row < height; row += 6) {
    for(col = 1; col < width; col += 3) {
      value0 = 0;
      value1 = 0;
      value2 = 0;
      value3 = 0; 
      value4 = 0;
      value5 = 0;
      value6 = 0; 
      value7 = 0;
      value8 = 0;
      value9 = 0;
      value10 = 0;
      value11 = 0;
      value12 = 0; 
      value13 = 0;
      value14 = 0;
      value15 = 0; 
      value16 = 0;
      value17 = 0;
      value18 = 0;
      value19 = 0;
      value20 = 0;
      value21 = 0; 
      value22 = 0;
      value23 = 0;
      value24 = 0; 
      value25 = 0;
      value26 = 0;
      value27 = 0;
      value28 = 0;
      value29 = 0;
      value30 = 0; 
      value31 = 0;
      value32 = 0;
      value33 = 0; 
      value34 = 0;
      value35 = 0;
      value36 = 0;
      value37 = 0;
      value38 = 0;
      value39 = 0; 
      value40 = 0;
      value41 = 0;
      value42 = 0; 
      value43 = 0;
      value44 = 0;
      value45 = 0;
      value46 = 0;
      value47 = 0;
      value48 = 0; 
      value49 = 0;
      value50 = 0;
      value51 = 0; 
      value52 = 0;
      value53 = 0;

	rsub1 = row - 1;
	r1 = row + 1;
	r2 = row + 2;
	r3 = row + 3;
	r4 = row + 4;
	r5 = row + 5;
	r6 = row + 6;

	csub1 = col - 1;
	c1 = col + 1;
	c2 = col + 2;
	c3 = col + 3;

	  value0 += input -> color[0][rsub1][csub1] * filter_get[0][0]
		    + input -> color[0][row][csub1] * filter_get[1][0]
		    + input -> color[0][r1][csub1] * filter_get[2][0]
		    + input -> color[0][rsub1][col] * filter_get[0][1]
		    + input -> color[0][row][col] * filter_get[1][1]
		    + input -> color[0][r1][col] * filter_get[2][1]
		    + input -> color[0][rsub1][c1] * filter_get[0][2]
		    + input -> color[0][row][c1] * filter_get[1][2]
		    + input -> color[0][r1][c1] * filter_get[2][2];
	  value1 += input -> color[0][row][csub1] * filter_get[0][0]
		    + input -> color[0][r1][csub1] * filter_get[1][0]
		    + input -> color[0][r2][csub1] * filter_get[2][0]
		    + input -> color[0][row][col] * filter_get[0][1]
		    + input -> color[0][r1][col] * filter_get[1][1]
		    + input -> color[0][r2][col] * filter_get[2][1]
		    + input -> color[0][row][c1] * filter_get[0][2]
		    + input -> color[0][r1][c1] * filter_get[1][2]
		    + input -> color[0][r2][c1] * filter_get[2][2];
	  value2 += input -> color[0][r1][csub1] * filter_get[0][0]
		    + input -> color[0][r2][csub1] * filter_get[1][0]
		    + input -> color[0][r3][csub1] * filter_get[2][0]
		    + input -> color[0][r1][col] * filter_get[0][1]
		    + input -> color[0][r2][col] * filter_get[1][1]
		    + input -> color[0][r3][col] * filter_get[2][1]
		    + input -> color[0][r1][c1] * filter_get[0][2]
		    + input -> color[0][r2][c1] * filter_get[1][2]
		    + input -> color[0][r3][c1] * filter_get[2][2];
	  value3 += input -> color[1][rsub1][csub1] * filter_get[0][0]
		    + input -> color[1][row][csub1] * filter_get[1][0]
		    + input -> color[1][r1][csub1] * filter_get[2][0]
		    + input -> color[1][rsub1][col] * filter_get[0][1]
		    + input -> color[1][row][col] * filter_get[1][1]
		    + input -> color[1][r1][col] * filter_get[2][1]
		    + input -> color[1][rsub1][c1] * filter_get[0][2]
		    + input -> color[1][row][c1] * filter_get[1][2]
		    + input -> color[1][r1][c1] * filter_get[2][2];
	  value4 += input -> color[1][row][csub1] * filter_get[0][0]
		    + input -> color[1][r1][csub1] * filter_get[1][0]
		    + input -> color[1][r2][csub1] * filter_get[2][0]
		    + input -> color[1][row][col] * filter_get[0][1]
		    + input -> color[1][r1][col] * filter_get[1][1]
		    + input -> color[1][r2][col] * filter_get[2][1]
		    + input -> color[1][row][c1] * filter_get[0][2]
		    + input -> color[1][r1][c1] * filter_get[1][2]
		    + input -> color[1][r2][c1] * filter_get[2][2];
	  value5 += input -> color[1][r1][csub1] * filter_get[0][0]
		    + input -> color[1][r2][csub1] * filter_get[1][0]
		    + input -> color[1][r3][csub1] * filter_get[2][0]
		    + input -> color[1][r1][col] * filter_get[0][1]
		    + input -> color[1][r2][col] * filter_get[1][1]
		    + input -> color[1][r3][col] * filter_get[2][1]
		    + input -> color[1][r1][c1] * filter_get[0][2]
		    + input -> color[1][r2][c1] * filter_get[1][2]
		    + input -> color[1][r3][c1] * filter_get[2][2];
	  value6 += input -> color[2][rsub1][csub1] * filter_get[0][0]
		    + input -> color[2][row][csub1] * filter_get[1][0]
		    + input -> color[2][r1][csub1] * filter_get[2][0]
		    + input -> color[2][rsub1][col] * filter_get[0][1]
		    + input -> color[2][row][col] * filter_get[1][1]
		    + input -> color[2][r1][col] * filter_get[2][1]
		    + input -> color[2][rsub1][c1] * filter_get[0][2]
		    + input -> color[2][row][c1] * filter_get[1][2]
		    + input -> color[2][r1][c1] * filter_get[2][2];
	  value7 += input -> color[2][row][csub1] * filter_get[0][0]
		    + input -> color[2][r1][csub1] * filter_get[1][0]
		    + input -> color[2][r2][csub1] * filter_get[2][0]
		    + input -> color[2][row][col] * filter_get[0][1]
		    + input -> color[2][r1][col] * filter_get[1][1]
		    + input -> color[2][r2][col] * filter_get[2][1]
		    + input -> color[2][row][c1] * filter_get[0][2]
		    + input -> color[2][r1][c1] * filter_get[1][2]
		    + input -> color[2][r2][c1] * filter_get[2][2];
	  value8 += input -> color[2][r1][csub1] * filter_get[0][0]
		    + input -> color[2][r2][csub1] * filter_get[1][0]
		    + input -> color[2][r3][csub1] * filter_get[2][0]
		    + input -> color[2][r1][col] * filter_get[0][1]
		    + input -> color[2][r2][col] * filter_get[1][1]
		    + input -> color[2][r3][col] * filter_get[2][1]
		    + input -> color[2][r1][c1] * filter_get[0][2]
		    + input -> color[2][r2][c1] * filter_get[1][2]
		    + input -> color[2][r3][c1] * filter_get[2][2];
	  value9 += input -> color[0][rsub1][col] * filter_get[0][0]
		    + input -> color[0][row][col] * filter_get[1][0]
		    + input -> color[0][r1][col] * filter_get[2][0]
		    + input -> color[0][rsub1][c1] * filter_get[0][1]
		    + input -> color[0][row][c1] * filter_get[1][1]
		    + input -> color[0][r1][c1] * filter_get[2][1]
		    + input -> color[0][rsub1][c2] * filter_get[0][2]
		    + input -> color[0][row][c2] * filter_get[1][2]
		    + input -> color[0][r1][c2] * filter_get[2][2];
	  value10 += input -> color[0][row][col] * filter_get[0][0]
		    + input -> color[0][r1][col] * filter_get[1][0]
		    + input -> color[0][r2][col] * filter_get[2][0]
		    + input -> color[0][row][c1] * filter_get[0][1]
		    + input -> color[0][r1][c1] * filter_get[1][1]
		    + input -> color[0][r2][c1] * filter_get[2][1]
		    + input -> color[0][row][c2] * filter_get[0][2]
		    + input -> color[0][r1][c2] * filter_get[1][2]
		    + input -> color[0][r2][c2] * filter_get[2][2];
	  value11 += input -> color[0][r1][col] * filter_get[0][0]
		    + input -> color[0][r2][col] * filter_get[1][0]
		    + input -> color[0][r3][col] * filter_get[2][0]
		    + input -> color[0][r1][c1] * filter_get[0][1]
		    + input -> color[0][r2][c1] * filter_get[1][1]
		    + input -> color[0][r3][c1] * filter_get[2][1]
		    + input -> color[0][r1][c2] * filter_get[0][2]
		    + input -> color[0][r2][c2] * filter_get[1][2]
		    + input -> color[0][r3][c2] * filter_get[2][2];
	  value12 += input -> color[1][rsub1][col] * filter_get[0][0]
		    + input -> color[1][row][col] * filter_get[1][0]
		    + input -> color[1][r1][col] * filter_get[2][0]
		    + input -> color[1][rsub1][c1] * filter_get[0][1]
		    + input -> color[1][row][c1] * filter_get[1][1]
		    + input -> color[1][r1][c1] * filter_get[2][1]
		    + input -> color[1][rsub1][c2] * filter_get[0][2]
		    + input -> color[1][row][c2] * filter_get[1][2]
		    + input -> color[1][r1][c2] * filter_get[2][2];
	  value13 += input -> color[1][row][col] * filter_get[0][0]
		    + input -> color[1][r1][col] * filter_get[1][0]
		    + input -> color[1][r2][col] * filter_get[2][0]
		    + input -> color[1][row][c1] * filter_get[0][1]
		    + input -> color[1][r1][c1] * filter_get[1][1]
		    + input -> color[1][r2][c1] * filter_get[2][1]
		    + input -> color[1][row][c2] * filter_get[0][2]
		    + input -> color[1][r1][c2] * filter_get[1][2]
		    + input -> color[1][r2][c2] * filter_get[2][2];
	  //value14 += input -> color[1][r+2][c+1]
	  value14 += input -> color[1][r1][col] * filter_get[0][0]
		    + input -> color[1][r2][col] * filter_get[1][0]
		    + input -> color[1][r3][col] * filter_get[2][0]
		    + input -> color[1][r1][c1] * filter_get[0][1]
		    + input -> color[1][r2][c1] * filter_get[1][1]
		    + input -> color[1][r3][c1] * filter_get[2][1]
		    + input -> color[1][r1][c2] * filter_get[0][2]
		    + input -> color[1][r2][c2] * filter_get[1][2]
		    + input -> color[1][r3][c2] * filter_get[2][2];
	  value15 += input -> color[2][rsub1][col] * filter_get[0][0]
		    + input -> color[2][row][col] * filter_get[1][0]
		    + input -> color[2][r1][col] * filter_get[2][0]
		    + input -> color[2][rsub1][c1] * filter_get[0][1]
		    + input -> color[2][row][c1] * filter_get[1][1]
		    + input -> color[2][r1][c1] * filter_get[2][1]
		    + input -> color[2][rsub1][c2] * filter_get[0][2]
		    + input -> color[2][row][c2] * filter_get[1][2]
		    + input -> color[2][r1][c2] * filter_get[2][2];
	  value16 += input -> color[2][row][col] * filter_get[0][0]
		    + input -> color[2][r1][col] * filter_get[1][0]
		    + input -> color[2][r2][col] * filter_get[2][0]
		    + input -> color[2][row][c1] * filter_get[0][1]
		    + input -> color[2][r1][c1] * filter_get[1][1]
		    + input -> color[2][r2][c1] * filter_get[2][1]
		    + input -> color[2][row][c2] * filter_get[0][2]
		    + input -> color[2][r1][c2] * filter_get[1][2]
		    + input -> color[2][r2][c2] * filter_get[2][2];
	  value17 += input -> color[2][r1][col] * filter_get[0][0]
		    + input -> color[2][r2][col] * filter_get[1][0]
		    + input -> color[2][r3][col] * filter_get[2][0]
		    + input -> color[2][r1][c1] * filter_get[0][1]
		    + input -> color[2][r2][c1] * filter_get[1][1]
		    + input -> color[2][r3][c1] * filter_get[2][1]
		    + input -> color[2][r1][c2] * filter_get[0][2]
		    + input -> color[2][r2][c2] * filter_get[1][2]
		    + input -> color[2][r3][c2] * filter_get[2][2];
	  value18 += input -> color[0][rsub1][c1] * filter_get[0][0]
		    + input -> color[0][row][c1] * filter_get[1][0]
		    + input -> color[0][r1][c1] * filter_get[2][0]
		    + input -> color[0][rsub1][c2] * filter_get[0][1]
		    + input -> color[0][row][c2] * filter_get[1][1]
		    + input -> color[0][r1][c2] * filter_get[2][1]
		    + input -> color[0][rsub1][c3] * filter_get[0][2]
		    + input -> color[0][row][c3] * filter_get[1][2]
		    + input -> color[0][r1][c3] * filter_get[2][2];
	  value19 += input -> color[0][row][c1] * filter_get[0][0]
		    + input -> color[0][r1][c1] * filter_get[1][0]
		    + input -> color[0][r2][c1] * filter_get[2][0]
		    + input -> color[0][row][c2] * filter_get[0][1]
		    + input -> color[0][r1][c2] * filter_get[1][1]
		    + input -> color[0][r2][c2] * filter_get[2][1]
		    + input -> color[0][row][c3] * filter_get[0][2]
		    + input -> color[0][r1][c3] * filter_get[1][2]
		    + input -> color[0][r2][c3] * filter_get[2][2];
	  value20 += input -> color[0][r1][c1] * filter_get[0][0]
		    + input -> color[0][r2][c1] * filter_get[1][0]
		    + input -> color[0][r3][c1] * filter_get[2][0]
		    + input -> color[0][r1][c2] * filter_get[0][1]
		    + input -> color[0][r2][c2] * filter_get[1][1]
		    + input -> color[0][r3][c2] * filter_get[2][1]
		    + input -> color[0][r1][c3] * filter_get[0][2]
		    + input -> color[0][r2][c3] * filter_get[1][2]
		    + input -> color[0][r3][c3] * filter_get[2][2];
	  value21 += input -> color[1][rsub1][c1] * filter_get[0][0]
		    + input -> color[1][row][c1] * filter_get[1][0]
		    + input -> color[1][r1][c1] * filter_get[2][0]
		    + input -> color[1][rsub1][c2] * filter_get[0][1]
		    + input -> color[1][row][c2] * filter_get[1][1]
		    + input -> color[1][r1][c2] * filter_get[2][1]
		    + input -> color[1][rsub1][c3] * filter_get[0][2]
		    + input -> color[1][row][c3] * filter_get[1][2]
		    + input -> color[1][r1][c3] * filter_get[2][2];
	  value22 += input -> color[1][row][c1] * filter_get[0][0]
		    + input -> color[1][r1][c1] * filter_get[1][0]
		    + input -> color[1][r2][c1] * filter_get[2][0]
		    + input -> color[1][row][c2] * filter_get[0][1]
		    + input -> color[1][r1][c2] * filter_get[1][1]
		    + input -> color[1][r2][c2] * filter_get[2][1]
		    + input -> color[1][row][c3] * filter_get[0][2]
		    + input -> color[1][r1][c3] * filter_get[1][2]
		    + input -> color[1][r2][c3] * filter_get[2][2];
	  value23 += input -> color[1][r1][c1] * filter_get[0][0]
		    + input -> color[1][r2][c1] * filter_get[1][0]
		    + input -> color[1][r3][c1] * filter_get[2][0]
		    + input -> color[1][r1][c2] * filter_get[0][1]
		    + input -> color[1][r2][c2] * filter_get[1][1]
		    + input -> color[1][r3][c2] * filter_get[2][1]
		    + input -> color[1][r1][c3] * filter_get[0][2]
		    + input -> color[1][r2][c3] * filter_get[1][2]
		    + input -> color[1][r3][c3] * filter_get[2][2];
	  value24 += input -> color[2][rsub1][c1] * filter_get[0][0]
		    + input -> color[2][row][c1] * filter_get[1][0]
		    + input -> color[2][r1][c1] * filter_get[2][0]
		    + input -> color[2][rsub1][c2] * filter_get[0][1]
		    + input -> color[2][row][c2] * filter_get[1][1]
		    + input -> color[2][r1][c2] * filter_get[2][1]
		    + input -> color[2][rsub1][c3] * filter_get[0][2]
		    + input -> color[2][row][c3] * filter_get[1][2]
		    + input -> color[2][r1][c3] * filter_get[2][2];
	  value25 += input -> color[2][row][c1] * filter_get[0][0]
		    + input -> color[2][r1][c1] * filter_get[1][0]
		    + input -> color[2][r2][c1] * filter_get[2][0]
		    + input -> color[2][row][c2] * filter_get[0][1]
		    + input -> color[2][r1][c2] * filter_get[1][1]
		    + input -> color[2][r2][c2] * filter_get[2][1]
		    + input -> color[2][row][c3] * filter_get[0][2]
		    + input -> color[2][r1][c3] * filter_get[1][2]
		    + input -> color[2][r2][c3] * filter_get[2][2];
	  value26 += input -> color[2][r1][c1] * filter_get[0][0]
		    + input -> color[2][r2][c1] * filter_get[1][0]
		    + input -> color[2][r3][c1] * filter_get[2][0]
		    + input -> color[2][r1][c2] * filter_get[0][1]
		    + input -> color[2][r2][c2] * filter_get[1][1]
		    + input -> color[2][r3][c2] * filter_get[2][1]
		    + input -> color[2][r1][c3] * filter_get[0][2]
		    + input -> color[2][r2][c3] * filter_get[1][2]
		    + input -> color[2][r3][c3] * filter_get[2][2];
	  value27 += input -> color[0][r2][csub1] * filter_get[0][0]
		    + input -> color[0][r3][csub1] * filter_get[1][0]
		    + input -> color[0][r4][csub1] * filter_get[2][0]
		    + input -> color[0][r2][col] * filter_get[0][1]
		    + input -> color[0][r3][col] * filter_get[1][1]
		    + input -> color[0][r4][col] * filter_get[2][1]
		    + input -> color[0][r2][c1] * filter_get[0][2]
		    + input -> color[0][r3][c1] * filter_get[1][2]
		    + input -> color[0][r4][c1] * filter_get[2][2];
	  value28 += input -> color[0][r3][csub1] * filter_get[0][0]
		    + input -> color[0][r4][csub1] * filter_get[1][0]
		    + input -> color[0][r5][csub1] * filter_get[2][0]
		    + input -> color[0][r3][col] * filter_get[0][1]
		    + input -> color[0][r4][col] * filter_get[1][1]
		    + input -> color[0][r5][col] * filter_get[2][1]
		    + input -> color[0][r3][c1] * filter_get[0][2]
		    + input -> color[0][r4][c1] * filter_get[1][2]
		    + input -> color[0][r5][c1] * filter_get[2][2];
	  value29 += input -> color[0][r4][csub1] * filter_get[0][0]
		    + input -> color[0][r5][csub1] * filter_get[1][0]
		    + input -> color[0][r6][csub1] * filter_get[2][0]
		    + input -> color[0][r4][col] * filter_get[0][1]
		    + input -> color[0][r5][col] * filter_get[1][1]
		    + input -> color[0][r6][col] * filter_get[2][1]
		    + input -> color[0][r4][c1] * filter_get[0][2]
		    + input -> color[0][r5][c1] * filter_get[1][2]
		    + input -> color[0][r6][c1] * filter_get[2][2];
	  value30 += input -> color[1][r2][csub1] * filter_get[0][0]
		    + input -> color[1][r3][csub1] * filter_get[1][0]
		    + input -> color[1][r4][csub1] * filter_get[2][0]
		    + input -> color[1][r2][col] * filter_get[0][1]
		    + input -> color[1][r3][col] * filter_get[1][1]
		    + input -> color[1][r4][col] * filter_get[2][1]
		    + input -> color[1][r2][c1] * filter_get[0][2]
		    + input -> color[1][r3][c1] * filter_get[1][2]
		    + input -> color[1][r4][c1] * filter_get[2][2];
	  value31 += input -> color[1][r3][csub1] * filter_get[0][0]
		    + input -> color[1][r4][csub1] * filter_get[1][0]
		    + input -> color[1][r5][csub1] * filter_get[2][0]
		    + input -> color[1][r3][col] * filter_get[0][1]
		    + input -> color[1][r4][col] * filter_get[1][1]
		    + input -> color[1][r5][col] * filter_get[2][1]
		    + input -> color[1][r3][c1] * filter_get[0][2]
		    + input -> color[1][r4][c1] * filter_get[1][2]
		    + input -> color[1][r5][c1] * filter_get[2][2];
	  value32 += input -> color[1][r4][csub1] * filter_get[0][0]
		    + input -> color[1][r5][csub1] * filter_get[1][0]
		    + input -> color[1][r6][csub1] * filter_get[2][0]
		    + input -> color[1][r4][col] * filter_get[0][1]
		    + input -> color[1][r5][col] * filter_get[1][1]
		    + input -> color[1][r6][col] * filter_get[2][1]
		    + input -> color[1][r4][c1] * filter_get[0][2]
		    + input -> color[1][r5][c1] * filter_get[1][2]
		    + input -> color[1][r6][c1] * filter_get[2][2];
	  value33 += input -> color[2][r2][csub1] * filter_get[0][0]
		    + input -> color[2][r3][csub1] * filter_get[1][0]
		    + input -> color[2][r4][csub1] * filter_get[2][0]
		    + input -> color[2][r2][col] * filter_get[0][1]
		    + input -> color[2][r3][col] * filter_get[1][1]
		    + input -> color[2][r4][col] * filter_get[2][1]
		    + input -> color[2][r2][c1] * filter_get[0][2]
		    + input -> color[2][r3][c1] * filter_get[1][2]
		    + input -> color[2][r4][c1] * filter_get[2][2];
	  value34 += input -> color[2][r3][csub1] * filter_get[0][0]
		    + input -> color[2][r4][csub1] * filter_get[1][0]
		    + input -> color[2][r5][csub1] * filter_get[2][0]
		    + input -> color[2][r3][col] * filter_get[0][1]
		    + input -> color[2][r4][col] * filter_get[1][1]
		    + input -> color[2][r5][col] * filter_get[2][1]
		    + input -> color[2][r3][c1] * filter_get[0][2]
		    + input -> color[2][r4][c1] * filter_get[1][2]
		    + input -> color[2][r5][c1] * filter_get[2][2];
	  value35 += input -> color[2][r4][csub1] * filter_get[0][0]
		    + input -> color[2][r5][csub1] * filter_get[1][0]
		    + input -> color[2][r6][csub1] * filter_get[2][0]
		    + input -> color[2][r4][col] * filter_get[0][1]
		    + input -> color[2][r5][col] * filter_get[1][1]
		    + input -> color[2][r6][col] * filter_get[2][1]
		    + input -> color[2][r4][c1] * filter_get[0][2]
		    + input -> color[2][r5][c1] * filter_get[1][2]
		    + input -> color[2][r6][c1] * filter_get[2][2];
	  value36 += input -> color[0][r2][col] * filter_get[0][0]
		    + input -> color[0][r3][col] * filter_get[1][0]
		    + input -> color[0][r4][col] * filter_get[2][0]
		    + input -> color[0][r2][c1] * filter_get[0][1]
		    + input -> color[0][r3][c1] * filter_get[1][1]
		    + input -> color[0][r4][c1] * filter_get[2][1]
		    + input -> color[0][r2][c2] * filter_get[0][2]
		    + input -> color[0][r3][c2] * filter_get[1][2]
		    + input -> color[0][r4][c2] * filter_get[2][2];
	  value37 += input -> color[0][r3][col] * filter_get[0][0]
		    + input -> color[0][r4][col] * filter_get[1][0]
		    + input -> color[0][r5][col] * filter_get[2][0]
		    + input -> color[0][r3][c1] * filter_get[0][1]
		    + input -> color[0][r4][c1] * filter_get[1][1]
		    + input -> color[0][r5][c1] * filter_get[2][1]
		    + input -> color[0][r3][c2] * filter_get[0][2]
		    + input -> color[0][r4][c2] * filter_get[1][2]
		    + input -> color[0][r5][c2] * filter_get[2][2];
	  value38 += input -> color[0][r4][col] * filter_get[0][0]
		    + input -> color[0][r5][col] * filter_get[1][0]
		    + input -> color[0][r6][col] * filter_get[2][0]
		    + input -> color[0][r4][c1] * filter_get[0][1]
		    + input -> color[0][r5][c1] * filter_get[1][1]
		    + input -> color[0][r6][c1] * filter_get[2][1]
		    + input -> color[0][r4][c2] * filter_get[0][2]
		    + input -> color[0][r5][c2] * filter_get[1][2]
		    + input -> color[0][r6][c2] * filter_get[2][2];
	  value39 += input -> color[1][r2][col] * filter_get[0][0]
		    + input -> color[1][r3][col] * filter_get[1][0]
		    + input -> color[1][r4][col] * filter_get[2][0]
		    + input -> color[1][r2][c1] * filter_get[0][1]
		    + input -> color[1][r3][c1] * filter_get[1][1]
		    + input -> color[1][r4][c1] * filter_get[2][1]
		    + input -> color[1][r2][c2] * filter_get[0][2]
		    + input -> color[1][r3][c2] * filter_get[1][2]
		    + input -> color[1][r4][c2] * filter_get[2][2];
	  value40 += input -> color[1][r3][col] * filter_get[0][0]
		    + input -> color[1][r4][col] * filter_get[1][0]
		    + input -> color[1][r5][col] * filter_get[2][0]
		    + input -> color[1][r3][c1] * filter_get[0][1]
		    + input -> color[1][r4][c1] * filter_get[1][1]
		    + input -> color[1][r5][c1] * filter_get[2][1]
		    + input -> color[1][r3][c2] * filter_get[0][2]
		    + input -> color[1][r4][c2] * filter_get[1][2]
		    + input -> color[1][r5][c2] * filter_get[2][2];
	  value41 += input -> color[1][r4][col] * filter_get[0][0]
		    + input -> color[1][r5][col] * filter_get[1][0]
		    + input -> color[1][r6][col] * filter_get[2][0]
		    + input -> color[1][r4][c1] * filter_get[0][1]
		    + input -> color[1][r5][c1] * filter_get[1][1]
		    + input -> color[1][r6][c1] * filter_get[2][1]
		    + input -> color[1][r4][c2] * filter_get[0][2]
		    + input -> color[1][r5][c2] * filter_get[1][2]
		    + input -> color[1][r6][c2] * filter_get[2][2];
	  value42 += input -> color[2][r2][col] * filter_get[0][0]
		    + input -> color[2][r3][col] * filter_get[1][0]
		    + input -> color[2][r4][col] * filter_get[2][0]
		    + input -> color[2][r2][c1] * filter_get[0][1]
		    + input -> color[2][r3][c1] * filter_get[1][1]
		    + input -> color[2][r4][c1] * filter_get[2][1]
		    + input -> color[2][r2][c2] * filter_get[0][2]
		    + input -> color[2][r3][c2] * filter_get[1][2]
		    + input -> color[2][r4][c2] * filter_get[2][2];
	  value43 += input -> color[2][r3][col] * filter_get[0][0]
		    + input -> color[2][r4][col] * filter_get[1][0]
		    + input -> color[2][r5][col] * filter_get[2][0]
		    + input -> color[2][r3][c1] * filter_get[0][1]
		    + input -> color[2][r4][c1] * filter_get[1][1]
		    + input -> color[2][r5][c1] * filter_get[2][1]
		    + input -> color[2][r3][c2] * filter_get[0][2]
		    + input -> color[2][r4][c2] * filter_get[1][2]
		    + input -> color[2][r5][c2] * filter_get[2][2];
	  value44 += input -> color[2][r4][col] * filter_get[0][0]
		    + input -> color[2][r5][col] * filter_get[1][0]
		    + input -> color[2][r6][col] * filter_get[2][0]
		    + input -> color[2][r4][c1] * filter_get[0][1]
		    + input -> color[2][r5][c1] * filter_get[1][1]
		    + input -> color[2][r6][c1] * filter_get[2][1]
		    + input -> color[2][r4][c2] * filter_get[0][2]
		    + input -> color[2][r5][c2] * filter_get[1][2]
		    + input -> color[2][r6][c2] * filter_get[2][2];
	  value45 += input -> color[0][r2][c1] * filter_get[0][0]
		    + input -> color[0][r3][c1] * filter_get[1][0]
		    + input -> color[0][r4][c1] * filter_get[2][0]
		    + input -> color[0][r2][c2] * filter_get[0][1]
		    + input -> color[0][r3][c2] * filter_get[1][1]
		    + input -> color[0][r4][c2] * filter_get[2][1]
		    + input -> color[0][r2][c3] * filter_get[0][2]
		    + input -> color[0][r3][c3] * filter_get[1][2]
		    + input -> color[0][r4][c3] * filter_get[2][2];
	  value46 += input -> color[0][r3][c1] * filter_get[0][0]
		    + input -> color[0][r4][c1] * filter_get[1][0]
		    + input -> color[0][r5][c1] * filter_get[2][0]
		    + input -> color[0][r3][c2] * filter_get[0][1]
		    + input -> color[0][r4][c2] * filter_get[1][1]
		    + input -> color[0][r5][c2] * filter_get[2][1]
		    + input -> color[0][r3][c3] * filter_get[0][2]
		    + input -> color[0][r4][c3] * filter_get[1][2]
		    + input -> color[0][r5][c3] * filter_get[2][2];
	  value47 += input -> color[0][r4][c1] * filter_get[0][0]
		    + input -> color[0][r5][c1] * filter_get[1][0]
		    + input -> color[0][r6][c1] * filter_get[2][0]
		    + input -> color[0][r4][c2] * filter_get[0][1]
		    + input -> color[0][r5][c2] * filter_get[1][1]
		    + input -> color[0][r6][c2] * filter_get[2][1]
		    + input -> color[0][r4][c3] * filter_get[0][2]
		    + input -> color[0][r5][c3] * filter_get[1][2]
		    + input -> color[0][r6][c3] * filter_get[2][2];
	  value48 += input -> color[1][r2][c1] * filter_get[0][0]
		    + input -> color[1][r3][c1] * filter_get[1][0]
		    + input -> color[1][r4][c1] * filter_get[2][0]
		    + input -> color[1][r2][c2] * filter_get[0][1]
		    + input -> color[1][r3][c2] * filter_get[1][1]
		    + input -> color[1][r4][c2] * filter_get[2][1]
		    + input -> color[1][r2][c3] * filter_get[0][2]
		    + input -> color[1][r3][c3] * filter_get[1][2]
		    + input -> color[1][r4][c3] * filter_get[2][2];
	  value49 += input -> color[1][r3][c1] * filter_get[0][0]
		    + input -> color[1][r4][c1] * filter_get[1][0]
		    + input -> color[1][r5][c1] * filter_get[2][0]
		    + input -> color[1][r3][c2] * filter_get[0][1]
		    + input -> color[1][r4][c2] * filter_get[1][1]
		    + input -> color[1][r5][c2] * filter_get[2][1]
		    + input -> color[1][r3][c3] * filter_get[0][2]
		    + input -> color[1][r4][c3] * filter_get[1][2]
		    + input -> color[1][r5][c3] * filter_get[2][2];
	  value50 += input -> color[1][r4][c1] * filter_get[0][0]
		    + input -> color[1][r5][c1] * filter_get[1][0]
		    + input -> color[1][r6][c1] * filter_get[2][0]
		    + input -> color[1][r4][c2] * filter_get[0][1]
		    + input -> color[1][r5][c2] * filter_get[1][1]
		    + input -> color[1][r6][c2] * filter_get[2][1]
		    + input -> color[1][r4][c3] * filter_get[0][2]
		    + input -> color[1][r5][c3] * filter_get[1][2]
		    + input -> color[1][r6][c3] * filter_get[2][2];
	  value51 += input -> color[2][r2][c1] * filter_get[0][0]
		    + input -> color[2][r3][c1] * filter_get[1][0]
		    + input -> color[2][r4][c1] * filter_get[2][0]
		    + input -> color[2][r2][c2] * filter_get[0][1]
		    + input -> color[2][r3][c2] * filter_get[1][1]
		    + input -> color[2][r4][c2] * filter_get[2][1]
		    + input -> color[2][r2][c3] * filter_get[0][2]
		    + input -> color[2][r3][c3] * filter_get[1][2]
		    + input -> color[2][r4][c3] * filter_get[2][2];
	  value52 += input -> color[2][r3][c1] * filter_get[0][0]
		    + input -> color[2][r4][c1] * filter_get[1][0]
		    + input -> color[2][r5][c1] * filter_get[2][0]
		    + input -> color[2][r3][c2] * filter_get[0][1]
		    + input -> color[2][r4][c2] * filter_get[1][1]
		    + input -> color[2][r5][c2] * filter_get[2][1]
		    + input -> color[2][r3][c3] * filter_get[0][2]
		    + input -> color[2][r4][c3] * filter_get[1][2]
		    + input -> color[2][r5][c3] * filter_get[2][2];
	  value53 += input -> color[2][r4][c1] * filter_get[0][0]
		    + input -> color[2][r5][c1] * filter_get[1][0]
		    + input -> color[2][r6][c1] * filter_get[2][0]
		    + input -> color[2][r4][c2] * filter_get[0][1]
		    + input -> color[2][r5][c2] * filter_get[1][1]
		    + input -> color[2][r6][c2] * filter_get[2][1]
		    + input -> color[2][r4][c3] * filter_get[0][2]
		    + input -> color[2][r5][c3] * filter_get[1][2]
		    + input -> color[2][r6][c3] * filter_get[2][2];

      if (divisor != 1) {
         value0 /= divisor;
         value1 /= divisor;
         value2 /= divisor;
         value3 /= divisor;
         value4 /= divisor;
         value5 /= divisor;
         value6 /= divisor;
         value7 /= divisor;
         value8 /= divisor;
         value9 /= divisor;
         value10 /= divisor;
         value11 /= divisor;
         value12 /= divisor;
         value13 /= divisor;
         value14 /= divisor;
         value15 /= divisor;
         value16 /= divisor;
         value17 /= divisor;
         value18 /= divisor;
         value19 /= divisor;
         value20 /= divisor;
         value21 /= divisor;
         value22 /= divisor;
         value23 /= divisor;
         value24 /= divisor;
         value25 /= divisor;
         value26 /= divisor;
         value27 /= divisor;
         value28 /= divisor;
         value29 /= divisor;
         value30 /= divisor;
         value31 /= divisor;
         value32 /= divisor;
         value33 /= divisor;
         value34 /= divisor;
         value35 /= divisor;
         value36 /= divisor;
         value37 /= divisor;
         value38 /= divisor;
         value39 /= divisor;
         value40 /= divisor;
         value41 /= divisor;
         value42 /= divisor;
         value43 /= divisor;
         value44 /= divisor;
         value45 /= divisor;
         value46 /= divisor;
         value47 /= divisor;
         value48 /= divisor;
         value49 /= divisor;
         value50 /= divisor;
         value51 /= divisor;
         value52 /= divisor;
         value53 /= divisor;
      }
      
      value0 = value0 < 0 ? 0 : value0;
      value1 = value1 < 0 ? 0 : value1;
      value2 = value2 < 0 ? 0 : value2;
      value3 = value3 < 0 ? 0 : value3;
      value4 = value4 < 0 ? 0 : value4;
      value5 = value5 < 0 ? 0 : value5;
      value6 = value6 < 0 ? 0 : value6;
      value7 = value7 < 0 ? 0 : value7;
      value8 = value8 < 0 ? 0 : value8;
      value9 = value9 < 0 ? 0 : value9;
      value10 = value10 < 0 ? 0 : value10;
      value11 = value11 < 0 ? 0 : value11;
      value12 = value12 < 0 ? 0 : value12;
      value13 = value13 < 0 ? 0 : value13;
      value14 = value14 < 0 ? 0 : value14;
      value15 = value15 < 0 ? 0 : value15;
      value16 = value16 < 0 ? 0 : value16;
      value17 = value17 < 0 ? 0 : value17;
      value18 = value18 < 0 ? 0 : value18;
      value19 = value19 < 0 ? 0 : value19;
      value20 = value20 < 0 ? 0 : value20;
      value21 = value21 < 0 ? 0 : value21;
      value22 = value22 < 0 ? 0 : value22;
      value23 = value23 < 0 ? 0 : value23;
      value24 = value24 < 0 ? 0 : value24;
      value25 = value25 < 0 ? 0 : value25;
      value26 = value26 < 0 ? 0 : value26;
      value27 = value27 < 0 ? 0 : value27;
      value28 = value28 < 0 ? 0 : value28;
      value29 = value29 < 0 ? 0 : value29;
      value30 = value30 < 0 ? 0 : value30;
      value31 = value31 < 0 ? 0 : value31;
      value32 = value32 < 0 ? 0 : value32;
      value33 = value33 < 0 ? 0 : value33;
      value34 = value34 < 0 ? 0 : value34;
      value35 = value35 < 0 ? 0 : value35;
      value36 = value36 < 0 ? 0 : value36;
      value37 = value37 < 0 ? 0 : value37;
      value38 = value38 < 0 ? 0 : value38;
      value39 = value39 < 0 ? 0 : value39;
      value40 = value40 < 0 ? 0 : value40;
      value41 = value41 < 0 ? 0 : value41;
      value42 = value42 < 0 ? 0 : value42;
      value43 = value43 < 0 ? 0 : value43;
      value44 = value44 < 0 ? 0 : value44;
      value45 = value45 < 0 ? 0 : value45;
      value46 = value46 < 0 ? 0 : value46;
      value47 = value47 < 0 ? 0 : value47;
      value48 = value48 < 0 ? 0 : value48;
      value49 = value49 < 0 ? 0 : value49;
      value50 = value50 < 0 ? 0 : value50;
      value51 = value51 < 0 ? 0 : value51;
      value52 = value52 < 0 ? 0 : value52;
      value53 = value53 < 0 ? 0 : value53;

      value0 = value0 > 255 ? 255 : value0;
      value1 = value1 > 255 ? 255 : value1;
      value2 = value2 > 255 ? 255 : value2;      
      value3 = value3 > 255 ? 255 : value3;
      value4 = value4 > 255 ? 255 : value4;
      value5 = value5 > 255 ? 255 : value5;      
      value6 = value6 > 255 ? 255 : value6;
      value7 = value7 > 255 ? 255 : value7;
      value8 = value8 > 255 ? 255 : value8;
      value9 = value9 > 255 ? 255 : value9;
      value10 = value10 > 255 ? 255 : value10;
      value11 = value11 > 255 ? 255 : value11;
      value12 = value12 > 255 ? 255 : value12;
      value13 = value13 > 255 ? 255 : value13;
      value14 = value14 > 255 ? 255 : value14;
      value15 = value15 > 255 ? 255 : value15;
      value16 = value16 > 255 ? 255 : value16;
      value17 = value17 > 255 ? 255 : value17;
      value18 = value18 > 255 ? 255 : value18;
      value19 = value19 > 255 ? 255 : value19;
      value20 = value20 > 255 ? 255 : value20;
      value21 = value21 > 255 ? 255 : value21;
      value22 = value22 > 255 ? 255 : value22;
      value23 = value23 > 255 ? 255 : value23;
      value24 = value24 > 255 ? 255 : value24;
      value25 = value25 > 255 ? 255 : value25;
      value26 = value26 > 255 ? 255 : value26;
      value27 = value27 > 255 ? 255 : value27;
      value28 = value28 > 255 ? 255 : value28;
      value29 = value29 > 255 ? 255 : value29;
      value30 = value30 > 255 ? 255 : value30;
      value31 = value31 > 255 ? 255 : value31;
      value32 = value32 > 255 ? 255 : value32;
      value33 = value33 > 255 ? 255 : value33;
      value34 = value34 > 255 ? 255 : value34;
      value35 = value35 > 255 ? 255 : value35;
      value36 = value36 > 255 ? 255 : value36;
      value37 = value37 > 255 ? 255 : value37;
      value38 = value38 > 255 ? 255 : value38;
      value39 = value39 > 255 ? 255 : value39;
      value40 = value40 > 255 ? 255 : value40;
      value41 = value41 > 255 ? 255 : value41;
      value42 = value42 > 255 ? 255 : value42;
      value43 = value43 > 255 ? 255 : value43;
      value44 = value44 > 255 ? 255 : value44;
      value45 = value45 > 255 ? 255 : value45;
      value46 = value46 > 255 ? 255 : value46;
      value47 = value47 > 255 ? 255 : value47;
      value48 = value48 > 255 ? 255 : value48;
      value49 = value49 > 255 ? 255 : value49;
      value50 = value50 > 255 ? 255 : value50;
      value51 = value51 > 255 ? 255 : value51;
      value52 = value52 > 255 ? 255 : value52;
      value53 = value53 > 255 ? 255 : value53;

      output -> color[0][row][col] = value0;
      output -> color[0][row+1][col] = value1;
      output -> color[0][row+2][col] = value2;
      output -> color[1][row][col] = value3;
      output -> color[1][row+1][col] = value4;
      output -> color[1][row+2][col] = value5;
      output -> color[2][row][col] = value6;
      output -> color[2][row+1][col] = value7;
      output -> color[2][row+2][col] = value8;

      output -> color[0][row][col+1] = value9;
      output -> color[0][row+1][col+1] = value10;
      output -> color[0][row+2][col+1] = value11;
      output -> color[1][row][col+1] = value12;
      output -> color[1][row+1][col+1] = value13;
      output -> color[1][row+2][col+1] = value14;
      output -> color[2][row][col+1] = value15;
      output -> color[2][row+1][col+1] = value16;
      output -> color[2][row+2][col+1] = value17;

      output -> color[0][row][col+2] = value18;
      output -> color[0][row+1][col+2] = value19;
      output -> color[0][row+2][col+2] = value20;
      output -> color[1][row][col+2] = value21;
      output -> color[1][row+1][col+2] = value22;
      output -> color[1][row+2][col+2] = value23;
      output -> color[2][row][col+2] = value24;
      output -> color[2][row+1][col+2] = value25;
      output -> color[2][row+2][col+2] = value26;

      output -> color[0][row+3][col] = value27;
      output -> color[0][row+4][col] = value28;
      output -> color[0][row+5][col] = value29;
      output -> color[1][row+3][col] = value30;
      output -> color[1][row+4][col] = value31;
      output -> color[1][row+5][col] = value32;
      output -> color[2][row+3][col] = value33;
      output -> color[2][row+4][col] = value34;
      output -> color[2][row+5][col] = value35;

      output -> color[0][row+3][col+1] = value36;
      output -> color[0][row+4][col+1] = value37;
      output -> color[0][row+5][col+1] = value38;
      output -> color[1][row+3][col+1] = value39;
      output -> color[1][row+4][col+1] = value40;
      output -> color[1][row+5][col+1] = value41;
      output -> color[2][row+3][col+1] = value42;
      output -> color[2][row+4][col+1] = value43;
      output -> color[2][row+5][col+1] = value44;

      output -> color[0][row+3][col+2] = value45;
      output -> color[0][row+4][col+2] = value46;
      output -> color[0][row+5][col+2] = value47;
      output -> color[1][row+3][col+2] = value48;
      output -> color[1][row+4][col+2] = value49;
      output -> color[1][row+5][col+2] = value50;
      output -> color[2][row+3][col+2] = value51;
      output -> color[2][row+4][col+2] = value52;
      output -> color[2][row+5][col+2] = value53;
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
