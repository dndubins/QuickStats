/*************************************************************
 * Quick Statistics for Float Arrays, by David Dubins
 * 02-Dec-2020
 * http://pb860.pbworks.com
 * For a more functional version of this library, visit:
 * https://github.com/dndubins/QuickStats
 *************************************************************/
#include <math.h>
//#define DEBUG

float average(float samples[],int m)
{
  float avg1=0.0;
  for(int i=0;i<m;i++){ 
    avg1+=(samples[i]-avg1)/(i+1); // iterative mean calculated here
  }
  return avg1;
}

float g_average(float samples[],int m)
{
  float avg1=0.0;
  for(int i=0;i<m;i++){
    avg1+=(log(samples[i])-avg1)/(i+1); // iterative geometric mean calculated here
  }
  return exp(avg1);
}

float stdev(float samples[],int m)
{
  float avg=0.0;
  float total2=0.0;
  avg=average(samples,m);
  for(int i=0;i<m;i++){
    total2 = total2 + pow(samples[i] - avg,2);
  }
  return sqrt(total2/((float)(m-1)));
}

float CV(float samples[],int m)  //Coefficient of variation (%RSD, or relative stdev)
{
  float avg=0.0;
  float sd=0.0;
  avg=average(samples,m);
  sd=stdev(samples,m);
  return 100.0*sd/avg;
}

void bubbleSort(float A[],int len)
{
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

float median(float samples[],int m) //calculate the median
{
  //First bubble sort the values: https://en.wikipedia.org/wiki/Bubble_sort
  float sorted[m];   //Define and initialize sorted array.
  float temp=0.0;      //Temporary float for swapping elements
  #ifdef DEBUG
    Serial.println("Before:");
    for(int j=0;j<m;j++){
      Serial.println(samples[j]);
    }
  #endif
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  #ifdef DEBUG
    Serial.println("After:");
    for(int i=0;i<m;i++){
      Serial.println(sorted[i]);
    }
  #endif
  if (bitRead(m,0)) {  //If the last bit of a number is 1, it's odd. This is equivalent to "TRUE". Also use if m%2!=0.
    return sorted[m/2]; //If the number of data points is odd, return middle number.
  } else {    
    return (sorted[(m/2)-1]+sorted[m/2])/2.0; //If the number of data points is even, return avg of the middle two numbers.
  }
}

float mode(float samples[],int m) //calculate the mode. 
{
  //First bubble sort the values: https://en.wikipedia.org/wiki/Bubble_sort
  float sorted[m];   //Temporary array to sort values.
  float temp=0;      //Temporary float for swapping elements
  float unique[m];   //Temporary array to store unique values
  int uniquect[m];   //Temporary array to store unique counts
  #ifdef DEBUG
    Serial.println("Before:");
    for(int i=0;i<m;i++){
      Serial.println(samples[i]);
    }
  #endif
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  #ifdef DEBUG
    Serial.println("Sorted:");
    for(int i=0;i<m;i++){
      Serial.println(sorted[i]);
    }
  #endif
  // Now count the number of times each unique number appears in the sorted array.
  unique[0]=sorted[0];
  uniquect[0]=1;
  int p=0; // counter for # unique numbers
  int maxp=0;
  int maxidx=0;
  for(int i=1;i<m;i++){
    if(abs(sorted[i]-sorted[i-1])<0.0001){  // tolerance for two readings being the same. Set as needed.
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
  #ifdef DEBUG
    for(int i=0;i<p+1;i++){
      Serial.println("Num: " + (String)unique[i] +"   Count: " + (String)uniquect[i]);
    }
  #endif  
  if (maxp>1) {    
    return unique[maxidx]; //If there is more than one mode, return the lowest one.
  } else {
    return 0.0; //If there is no mode, return a zero.
  }
}
