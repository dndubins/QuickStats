/* QuickStats.cpp - Library for quick descriptive statistics of an array samples[] of size m
 *  Created by David Dubins, January 10th, 2016.
 *  Released into the public domain.
 *  Requires Arduino 1.6.6 or greater.
 *  http://pb435.pbworks/com
 */

#include "Arduino.h"
#include "QuickStats.h"
#include <math.h>

QuickStats::QuickStats(){/*nothing to construct*/}
QuickStats::~QuickStats(){/*nothing to destruct*/}

float QuickStats::average(float samples[],int m)
{
  float total1=0.0;
  for(int i=0;i<m;i++){
    total1=total1+samples[i];
  }
  return total1/(float)m;
}

float QuickStats::g_average(float samples[],int m)
{
  float total1=0.0;
  for(int i=0;i<m;i++){
    total1=total1+log(samples[i]);
  }
  return exp(total1/(float)m);
}

float QuickStats::minimum(float samples[],int m)
{
  float sorted[m];   //Define and initialize sorted array
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  return(sorted[0]); // first element is the minimum
}

float QuickStats::maximum(float samples[],int m)
{
  float sorted[m];   //Define and initialize sorted array
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  return(sorted[m-1]);   // last element is the maximum
}

float QuickStats::stdev(float samples[],int m)
{
  float avg=0.0;
  float total2=0.0;
  avg=average(samples,m);
  for(int i=0;i<m;i++){
    total2 = total2 + pow(samples[i] - avg,2);
  }
  return sqrt(total2/((float)m-1.0));
}

float QuickStats::stderror(float samples[],int m) {
  float temp1=0.0;
  temp1=stdev(samples,m);
  return (temp1/sqrt((float)m));
}

float QuickStats::CV(float samples[],int m)  //Coefficient of variation (%RSD, or relative stdev)
{
  float avg=0.0;
  float sd=0.0;
  avg=average(samples,m);
  sd=stdev(samples,m);
  return 100.0*sd/avg;
}

void QuickStats::bubbleSort(float A[],int len) {
  unsigned long newn;
  unsigned long n=len;
  float temp=0.0;
  do {
    newn=1;
    for(int p=1;p<len;p++){
      if(A[p-1]>A[p]){
        temp=A[p];           //swap places in array
        A[p]=A[p-1];
        A[p-1]=temp;
        newn=p;
      } //end if
    } //end for
    n=newn;
  } while(n>1);
}

float QuickStats::fabs(float sample) // calculate absolute value
{ 
  if(sample<0.f){
    return -sample;
  }else{
    return sample;
  }
}

float QuickStats::median(float samples[],int m) //calculate the median
{
  //First bubble sort the values: https://en.wikipedia.org/wiki/Bubble_sort
  float sorted[m];   //Define and initialize sorted array.
  float temp=0.0;      //Temporary float for swapping elements
  /*Serial.println("Before:");
  for(int j=0;j<m;j++){
    Serial.println(samples[j]);
  }*/
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  /*Serial.println("After:");
  for(int i=0;i<m;i++){
    Serial.println(sorted[i]);
  }*/
  if (bitRead(m,0)==1) {  //If the last bit of a number is 1, it's odd. This is equivalent to "TRUE". Also use if m%2!=0.
    return sorted[m/2]; //If the number of data points is odd, return middle number.
  } else {    
    return (sorted[(m/2)-1]+sorted[m/2])/2; //If the number of data points is even, return avg of the middle two numbers.
  }
}

float QuickStats::mode(float samples[],int m,float epsilon) //calculate the mode.
//epsilon is the tolerance for two measurements to be equivalent.
{
  //First bubble sort the values: https://en.wikipedia.org/wiki/Bubble_sort
  float sorted[m];   //Temporary array to sort values.
  float temp=0;      //Temporary float for swapping elements
  float unique[m];   //Temporary array to store unique values
  int uniquect[m]; //Temporary array to store unique counts
  /*Serial.println("Before:");
  for(int i=0;i<m;i++){
    Serial.println(samples[i]);
  }*/
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  /*Serial.println("Sorted:");
  for(int i=0;i<m;i++){
    Serial.println(sorted[i]);
  }*/
  // Now count the number of times each unique number appears in the sorted array.
  unique[0]=sorted[0];
  uniquect[0]=1;
  int p=0; // counter for # unique numbers
  int maxp=0;
  int maxidx=0;
  for(int i=1;i<m;i++){ 
    if(fabs(sorted[i]-sorted[i-1])<epsilon){
      uniquect[p]++;  //if same number again, add to count
      if(uniquect[p]>maxp){
        maxp=uniquect[p];
        maxidx=p;      
      }
    } else {
      p++;
      unique[p]=sorted[i];
      uniquect[p]=1;
    }
  }
  /*for(int i=0;i<p+1;i++){
    Serial.println("Num: " + (String)unique[i] +"   Count: " + (String)uniquect[i]);
  }*/  
  if (maxp>1) {    
    return unique[maxidx]; //If there is more than one mode, return the lowest one.
  } else {
    return 0.0; //If there is no mode, return a zero.
  }
}

