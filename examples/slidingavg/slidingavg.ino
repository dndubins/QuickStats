// Example program for use with QuickStats.h 
// Report sliding average with slope

#include "QuickStats.h"

#define NUMREADINGS 10

byte vPin=A0;
float readings[NUMREADINGS];
float times[NUMREADINGS];
int idx=NUMREADINGS;
int count=0;

QuickStats stats; //initialize an instance of this class

void setup()
{
  Serial.begin(9600); 
  Serial.println("Reading, Sliding Average, Slope");
}
 
void loop()
{
  count++;
  idx++;
  if(idx>=NUMREADINGS){
    idx=0;
  }
  times[idx]=millis();
  readings[idx]=analogRead(vPin);
  if(count>NUMREADINGS){
    Serial.print(readings[idx]);
    Serial.print(", ");
    Serial.print(stats.average(readings,NUMREADINGS));
    Serial.print(", ");
    Serial.println(stats.slope(times,readings,NUMREADINGS),5);
  }
  delay(50);
}
