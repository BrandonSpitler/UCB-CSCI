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
  int width, height, dim;
  int outputWidth, outputHeight;
  int divisor;
  int row, col, i, j, r, c;
  int value0 = 0, value1 = 0, value2 = 0, value3 = 0,
    value4 = 0, value5 = 0, value6 = 0, value7 = 0,
    value8 = 0,  value9 = 0, value10 = 0, value11 = 0,
    value12 = 0, value13 = 0, value14 = 0, value15 = 0,
    value16 = 0, value17 = 0, sum0 = 0, sum1 = 0, sum2 = 0, 
    sum3 = 0, sum4 = 0, sum5 = 0;
  
  cycStart = rdtscll();
  
  width = input -> width;
  height = input -> height;
  dim = filter -> getSize();
  
  output -> width = width;
  output -> height = height;
  
  divisor = filter->getDivisor();

  int filterGet[dim][dim];
  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      filterGet[i][j] = filter -> get(i, j);
    }
  }

  for(row = 1; row < height - 1 ; row = row + 2){
    for(col = 1; col < width - 1; col = col + 3) {

      for (i = 0; i < dim; i+=2) {
	r = row + i - 1;
        for (j = 0; j < dim-2; j+=3) {
	  c = col + j - 1;
	  value0 = value0 + input -> color[0][r][c] * filterGet[i][j];
	  value1 = value1 + input -> color[1][r][c] * filterGet[i][j];
	  value2 = value2 + input -> color[2][r][c] * filterGet[i][j];
	  value3 = value3 + input -> color[0][r][c+1] * filterGet[i][j+1];
	  value4 = value4 + input -> color[1][r][c+1] * filterGet[i][j+1];
	  value5 = value5 + input -> color[2][r][c+1] * filterGet[i][j+1];
	  value6 = value6 + input -> color[0][r][c+2] * filterGet[i][j+2];
	  value7 = value7 + input -> color[1][r][c+2] * filterGet[i][j+2];
	  value8 = value8 + input -> color[2][r][c+2] * filterGet[i][j+2];
	  
	  value9 = value9 + input -> color[0][r+1][c] * filterGet[i+1][j];
	  value10 = value10 + input -> color[1][r+1][c] * filterGet[i+1][j];
	  value11 = value11 + input -> color[2][r+1][c] * filterGet[i+1][j];
	  value12 = value12 + input -> color[0][r+1][c+1] * filterGet[i+1][j+1];
	  value13 = value13 + input -> color[1][r+1][c+1] * filterGet[i+1][j+1];
	  value14 = value14 + input -> color[2][r+1][c+1] * filterGet[i+1][j+1];
	  value15 = value15 + input -> color[0][r+1][c+2] * filterGet[i+1][j+2];
	  value16 = value16 + input -> color[1][r+1][c+2] * filterGet[i+1][j+2];
	  value17 = value17 + input -> color[2][r+1][c+2] * filterGet[i+1][j+2];
	  }
	for (; j < dim; j++) {
	  sum0 += input -> color[0][r][col+j-1] * filterGet[i][j];
	  sum1 += input -> color[1][r][col+j] * filterGet[i][j+1];
	}	
       for(; i < dim; i++) {
	  sum3 += input -> color[0][row+i-1][col+j-1] * filterGet[i+1][j];
	  sum3 += input -> color[0][row+1][col +j] * filterGet[i+1][j+1]; 
       }
       sum0 += value0 + value3 + value6;
       sum1 += value1 + value4 + value7;
       sum2 += value2 + value5 + value8;
      }
      sum3 += value9 + value12 + value15;
      sum4 += value10 + value13 + value16;
      sum5 += value11 + value14 + value17;

	sum0 = sum0 / divisor;
	sum1 = sum1 / divisor;
	sum2 = sum2 / divisor;
	sum3 = sum3 / divisor;
	sum4 = sum4 / divisor;
	sum5 = sum5 / divisor;
	
	sum0 = sum0 < 0 ? 0 : sum0;
	sum1 = sum1 < 0 ? 0 : sum1;
	sum2 = sum2 < 0 ? 0 : sum2;
	sum3 = sum3 < 0 ? 0 : sum3;
	sum4 = sum4 < 0 ? 0 : sum4;
	sum5 = sum5 < 0 ? 0 : sum5;

	sum0 = sum0 > 255 ? 255 : sum0;
	sum1 = sum1 > 255 ? 255 : sum1;
	sum2 = sum2 > 255 ? 255 : sum2;
	sum3 = sum3 > 255 ? 255 : sum3;
	sum4 = sum4 > 255 ? 255 : sum4;
	sum5 = sum5 > 255 ? 255 : sum5;

	output -> color[0][row][col] = sum0;
	output -> color[1][row][col+1] = sum1;
	output -> color[2][row][col+2] = sum2;
	output -> color[0][row+1][col] = sum3;
	output -> color[1][row+1][col+1] = sum4;
	output -> color[2][row+1][col+2] = sum5;
    }
   }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
