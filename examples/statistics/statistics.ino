// Example program for use with QuickStats.h 
// Author: D. Dubins
// Date: 08-Dec-21
/* Expected Results:
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
GMDN: 3.33
*/

#include "QuickStats.h"
 
int numreadings = 9;
float readings[]={1.0,2.2,4.8,3.3,6.1,2.2,3.8,7.0,2.2};
 
QuickStats stats; //initialize an instance of this class

void setup()
{
  Serial.begin(9600); 
  Serial.println("Descriptive Statistics");
  Serial.print("Average: ");
  Serial.println(stats.average(readings,numreadings));
  Serial.print("Geometric mean: ");
  Serial.println(stats.g_average(readings,numreadings));
  Serial.print("Minimum: ");
  Serial.println(stats.minimum(readings,numreadings));
  Serial.print("Maximum: ");
  Serial.println(stats.maximum(readings,numreadings));
  Serial.print("Standard Deviation: ");
  Serial.println(stats.stdev(readings,numreadings));
  Serial.print("Standard Error: ");
  Serial.println(stats.stderror(readings,numreadings));
  Serial.print("Coefficient of Variation (%): ");
  Serial.println(stats.CV(readings,numreadings));
  Serial.print("Median: ");
  Serial.println(stats.median(readings,numreadings));
  Serial.print("Mode: ");
  Serial.println(stats.mode(readings,numreadings,0.00001));
  Serial.print("Geothmetic Meandian: ");
  Serial.println(stats.gmdn(readings,numreadings,0.00001));
}
 
void loop()
{
}
