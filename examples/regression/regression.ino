// Example program for use with QuickStats.h 
// Simple linear regression (y=ax+b)
/* Expected Results:
Linear Regression
Slope: 8.12
Intercept: 1.85
r^2: 0.8972
Adjusted r^2: 0.8629
*/

#include "QuickStats.h"
 
int numreadings = 5;
float readings[]={2.15, 3.25, 2.55, 4.64, 7.43};
float times[]={0.00, 0.10, 0.20, 0.41, 0.62};
 
QuickStats stats; //initialize an instance of this class

void setup()
{
  Serial.begin(9600); 
  Serial.println("Linear Regression");
  Serial.print("Slope: ");
  Serial.println(stats.slope(times,readings,numreadings));
  Serial.print("Intercept: ");
  Serial.println(stats.intercept(times,readings,numreadings));
  Serial.print("r^2: ");
  Serial.println(stats.rsq(times,readings,numreadings),4);
  Serial.print("Adjusted r^2: ");
  Serial.println(stats.rsq_adj(times,readings,numreadings),4);
}
 
void loop()
{
}
