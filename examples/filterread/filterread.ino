// The following program is an example of data smoothing using the QuickStats.h library in Arduino.
// This program filters out NaN values, and rejects measurements outside mean +/- 1.645*sd.
// (~90% of measurements should be within 1.645*sd of mean if the data are normally distributed)

#include "QuickStats.h"

#define NUMSAMPLES 100 // number of measurements to make per data point
byte sensorPin = A1;   // declaring the analog input to be Pin A1 of Arduino board.
float v = 0.0;  // variable to store analog reading

QuickStats stats; //initialize an instance of this class

void setup()
{
  Serial.begin(9600); // Start the serial monitor
}

void loop()
{
  v=getMes(NUMSAMPLES); // get a measurement
  Serial.println(v,3);    // Print smoothed value to serial monitor
  delay(250); // Change (or remove) this delay to alter the time between readings.
}

float getMes(int samples) { // routine that takes #samples, filters out NaN values, drops values outside 1.645*standard deviations of mean
  float mData[NUMSAMPLES]; // to hold measured data from thermocouple
  int cCount=0; // number actually collected
  for(int i=0;i<samples;i++){ //Collect #samples measurements
    float measured=analogRead(sensorPin); // take a single reading
    measured=measured*5.0/1023.0; // convert to a voltage
    if(isnan(measured)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
      mData[cCount]=measured; //record measurement to mData array
      cCount++;
    }
  }
  float avg=stats.average(mData,cCount); // get average of measured data
  float sd=stats.stdev(mData,cCount); // get standard deviation of measured data
  int oCount=0; // counter for filtered reads
  for(int i=0;i<cCount;i++){ //Remmove outliers from the data points:
    if(abs(avg-mData[i])<1.645*sd){  // filter out readings more than 1.645*sd from the mean 
      mData[oCount]=mData[i]; // overwrite original array with filtered data
      oCount++;
    }
  }
  //uncomment to see how much filtering is going on, and how the average was affected:
  //Serial.println("Avg: "+(String)avg+" SD: "+(String)sd+"cCount: "+(String)cCount+" oCount: "+(String)oCount);
  if(sd==0){
    return avg; // protects against a zero standard deviation
  } else {
    return stats.average(mData,oCount); // average filter
  }
}
