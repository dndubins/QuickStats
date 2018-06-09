// Example program for use with QuickStats.h 
// Filter out nan and inf values from a 1-dimensional matrix
// Warning: the filternan function overwrites the original matrix and adjusts the matrix size integer 
// (destructive)

#include "QuickStats.h"

QuickStats stats; //initialize an instance of this class
int NUMSAMPLES=10;  // size of matrix
//create a 1D array with a nan and inf value in it:
float measurements[10]={1.0, 2.0, sqrt(-1), 4.0, 5.0/0.0, 6.0, 7.0, 8.0, 9.0, 10.0};

void setup()
{
  Serial.begin(9600); 
  stats.filternan(measurements,NUMSAMPLES); // filter out nan and inf values
  Serial.print(stats.average(measurements,NUMSAMPLES)); //calculate and print the average
}
 
void loop()
{
}