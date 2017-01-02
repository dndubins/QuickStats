// Example program for use with QuickStats.h 

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
}
 
void loop()
{
}
