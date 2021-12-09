/*************************************************************
 * Quick Statistics for Float Arrays, by David Dubins
 * 02-Dec-2020
 * Last Updated: 08-Dec-21
 * https://github.com/dndubins/QuickStats/edit/master/standalone/Quickstats.h
 * For a more functional version of this library, visit:
 * https://github.com/dndubins/QuickStats
 *************************************************************/
#include <math.h>

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

float minimum(float samples[],int m)
{
  float sorted[m];   //Define and initialize sorted array
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  return(sorted[0]); // first element is the minimum
}

float maximum(float samples[],int m)
{
  float sorted[m];   //Define and initialize sorted array
  for(int i=0;i<m;i++){
    sorted[i]=samples[i];
  }
  bubbleSort(sorted,m);  // Sort the values
  return(sorted[m-1]);   // last element is the maximum
}

float stdev(float samples[],int m)
{
  float avg=0.0;
  float total2=0.0;
  avg=average(samples,m);
  for(int i=0;i<m;i++){
    total2 = total2 + pow(samples[i] - avg,2);
  }
  return sqrt(total2/((float)m-1.0));
}

float stderror(float samples[],int m)
{
  float temp1=0.0;
  temp1=stdev(samples,m);
  return (temp1/sqrt((float)m));
}

float CV(float samples[],int m)  //Coefficient of variation (%RSD, or relative stdev)
{
  float avg=0.0;
  float sd=0.0;
  avg=average(samples,m);
  sd=stdev(samples,m);
  return 100.0*sd/avg;
}

float fabs(float sample) // calculate absolute value
{ 
  if(sample<0.f){
    return -sample;
  }else{
    return sample;
  }
}

float median(float samples[],int m) //calculate the median
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

float mode(float samples[],int m,float epsilon) //calculate the mode.
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
  unique[0]=sorted[0]; // first unique number is the first number
  uniquect[0]=1;       // first count is 1
  int p=0; // array index for last unique number
  int maxp=0;
  int maxidx=0;
  for(int i=1;i<m;i++){
    if(fabs(sorted[i]-unique[p])<epsilon){ // if number same within tolerance
      uniquect[p]++;         // add to count of this number
      if(uniquect[p]>maxp){  // if this exceeds the largest frequency
        maxp=uniquect[p];    // record this number, it's the new mode
        maxidx=p;            // store the index of the number with the highest freq
      }
    } else {
      p++;  // found a new unique number      
      unique[p]=sorted[i];
      uniquect[p]=1;
    }
  }
  /*for(int i=0;i<p+1;i++){ //uncomment this section for debugging
    Serial.print("Num: "); 
    Serial.print(unique[i],4);
    Serial.print(" Count: "); 
    Serial.println(uniquect[i]);
  }*/
  if (maxp>1) {    
    return unique[maxidx]; //If there is more than one mode, return the lowest one.
  } else {
    return 0.0; //If there is no mode, return a zero.
  }
}


float slope(float x[],float samples[],int m)  //calculate the slope (dsamples/dx)
{
  float xavg=average(x,m);
  float yavg=average(samples,m);
  float numerator = 0.0;
  float denominator = 0.0;
  for(int i=0;i<m;i++){
    if(x[i]-xavg!=0.0){ // protect against dividing by zero
      numerator = numerator + (x[i]-xavg)*(samples[i]-yavg);
      denominator = denominator + ((x[i]-xavg)*(x[i]-xavg));
    }
  }
  return numerator/denominator;  
}

float intercept(float x[],float samples[],int m)  //calculate the intercept (dsamples/dx)
{
  float xavg=average(x,m);
  float yavg=average(samples,m);
  float beta=slope(x,samples,m);
  return yavg-(beta*xavg);
}

float rsq(float x[],float samples[],int m)  //calculate the rsq value
{
  float yavg=average(samples,m); // get average of samples
  float s=slope(x,samples,m);    // get slope (dsamples/dx)
  float b=intercept(x,samples,m); // get intercept
  float fi[m];                    // to hold model values of samples
  float j[m];                     // to hold (y-fi)^2 values
  float k[m];                     // to hold (y=yavg)^2 values
  float SSres=0.0;                // to hold sum of squares of residuals
  float SStot=0.0;                // to hold total sum of squares
  for(int i=0;i<m;i++){
    fi[i]=s*x[i]+b;
    j[m]=pow(samples[i]-fi[i],2);
    SSres+=j[m];
    k[m]=pow(samples[i]-yavg,2);
    SStot+=k[m];
  }
  return 1.0-(SSres/SStot);         // calculate and return the rsq value
}

float rsq_adj(float x[],float samples[],int m)  //calculate the adjusted rsq value
{
  float a=rsq(x,samples,m);
  return 1.0-(1.0-a)*(m-1.0)/(m-2.0);  // calculate and return the adjusted rsq value
}

void filternan(float samples[],int &m)  //removes nan values and returns size of filtered matrix (destructive)
{
  int duds=0; //keep track of #nans
  int nums=0; //keep track of numbers
  float filtered[m];
  for(int i=0;i<m;i++){
    if(isnan(samples[i])||isinf(samples[i])){
      duds++; // found a nan
    }else{
      filtered[nums]=samples[i];
      nums++;  // found a number
    }
  }
  for(int i=0;i<nums;i++){
    samples[i]=filtered[i]; //overwrite sample matrix with filtered matrix 
  }
  m=nums; //overwrite matrix size
}

void f_round(float samples[], int m, int p)  //round float variable to a given # decimals, p
{
  float precision=pow(10.0,p);
  for(int i=0;i<m;i++){
    samples[i]=round(samples[i]*precision)/precision;
  }
}
