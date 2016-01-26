// The following program is an example of data smoothing using the QuickStats.h library in Arduino.

#include "QuickStats.h"

byte sensorPin = A1;              // declaring the analog input to be Pin A1 of Arduino board.
int v = 0;                        // variable to store analog reading
int NUMSAMPLES=100;               // Number of samples to take for data smoothing 
float measurements[100];          // Variable for holding raw measurements
float smoothed;                   // Variable for holding filtered measurement
float smoothedCV;                  // Variable for holding CV of measurements

QuickStats stats; //initialize an instance of this class

void setup()
{
  Serial.begin(9600); 
  Serial.println("Reading, %CV");
}

void loop()
{
  //Collect the data points:
  for(int i=0;i<NUMSAMPLES;i++){
    v=analogRead(sensorPin);
    measurements[i]=(5.0*(float)v/1024.0); // convert to volts
    delay(10);  // Change (or remove) this delay value to alter the sampling time span.
  }  
  smoothed=stats.median(measurements,NUMSAMPLES); // Median filter (choose which filter to use)
  //smoothed=stats.average(measurements,NUMSAMPLES); // Mean filter 
  //smoothed=stats.mode(measurements,NUMSAMPLES); // Mode filter 
  
  smoothedCV=stats.CV(measurements,NUMSAMPLES); // CV of readings    
  Serial.print(smoothed,3);  // Print smoothed value to serial monitor
  Serial.print(", ");
  Serial.println(smoothedCV);  // Print CV to serial monitor
  delay(250); // Change (or remove) this delay to alter the time between readings.
}
