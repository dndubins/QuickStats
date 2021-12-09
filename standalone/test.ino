// Example sketch for use with QuickStats.h standalone library
// Author: D. Dubins
// Date: 08-Dec-21
// Copy QuickStats.h into the same directory as this sketch.
// The program results should be as follows:
/*
Descriptive Statistics
Average: 3.62
Geometric mean: 3.11
Minimum: 1.00
Maximum: 7.00
Standard Deviation: 2.00
Standard Error: 0.67
Coefficient of Variation (%): 55.23
Median: 3.30
Mode: 2.20
*/

#include "Quickstats.h"
 
int numreadings = 9;
float readings[]={1.0,2.2,4.8,3.3,6.1,2.2,3.8,7.0,2.2};
 
void setup()
{
  Serial.begin(9600); 
  Serial.println("Descriptive Statistics");
  Serial.print("Average: ");
  Serial.println(average(readings,numreadings));
  Serial.print("Geometric mean: ");
  Serial.println(g_average(readings,numreadings));
  Serial.print("Minimum: ");
  Serial.println(minimum(readings,numreadings));
  Serial.print("Maximum: ");
  Serial.println(maximum(readings,numreadings));
  Serial.print("Standard Deviation: ");
  Serial.println(stdev(readings,numreadings));
  Serial.print("Standard Error: ");
  Serial.println(stderror(readings,numreadings));
  Serial.print("Coefficient of Variation (%): ");
  Serial.println(CV(readings,numreadings));
  Serial.print("Median: ");
  Serial.println(median(readings,numreadings));
  Serial.print("Mode: ");
  Serial.println(mode(readings,numreadings,0.00001));
}
 
void loop()
{
}
