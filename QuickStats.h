/*  QuickStats.h version 1.2.3 - Library for quick descriptive statistics of an array samples[] of size m,
 *  assuming a normal distribution.
 *  Created by David Dubins, January 10th, 2016.
 *  Last edited 25-Dec-21.
 *  https://github.com/dndubins/QuickStats/
 *  Released into the public domain.
 */

#ifndef QuickStats_h
#define QuickStats_h

#include <Arduino.h>

class QuickStats {
  public:
    QuickStats();
    ~QuickStats();
    float average(float samples[],int m);
    float g_average(float samples[],int m);
    float minimum(float samples[],int m);
    float maximum(float samples[],int m);	
    float stdev(float samples[],int m);
    float stderror(float samples[],int m);
    float CV(float samples[],int m);
    void bubbleSort(float A[],int len);
    float fabs(float sample);
    float median(float samples[],int m);
    float mode(float samples[],int m,float epsilon);
    float gmdn(float samples[],int m,float epsilon);
    float slope(float x[],float samples[],int m);
    float intercept(float x[],float samples[],int m);
    float rsq(float x[],float samples[],int m);
    float rsq_adj(float x[],float samples[],int m);
    void filternan(float samples[],int &m);
    void f_round(float samples[], int m, int p);
};

#endif
