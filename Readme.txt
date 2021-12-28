Readme file for Arduino QuickStats Library

QuickStats is a library that provides simple descriptive statistics for elements in float arrays, in Arduino.

This library was originally created for a data smoothing strategy for float variables. Using a median or mode filtering strategy (opposed to mean filtering) is better at removing spikes from aberrant readings. The other functions (stdev, CV, etc.) were included for fun.

The example sketch, "statistics.ino" illustrates how to call each function. A bubble sort algorithm is also included, which was required for calculation of median and mode. Each function takes a float array, and dimension of the float array, as inputs.

The functions available in the library include:

average(samples[],m);     // the average of elements in samples[m]
g_average(samples[],m);   // the geometric mean of elements in samples[m]

minimum(samples[],m);      // the minimum value in samples[m]
maximum(samples[],m);      // the maximum value in samples[m]
stdev(samples[],m);        // the sample standard deviation of elements in samples[m]
stderror(samples[],m);     // the standard error of elements in samples[m] calculated as stdev/sqrt(m)
CV(samples[],m);           // the coefficient of variation in samples[m] in percent, calculated as 100*stdev/average
bubbleSort(samples[],m);   // a sorting algorithm to arrange the elements in samples[m] in ascending order
fabs(sample);              // absolute value of float
median(samples[],m);       // the median of elements in samples[m]
mode(samples[],m,epsilon); // the mode of elements in samples[m]. This function returns a zero if there is no mode.
                           // epsilon is the tolerance of accepting measurements as being equal.
gmdn(samples[],m,epsilon); // the geothmetic meandian of elements in samples[m]. See: https://xkcd.com/2435/
                           // epsilon is the tolerance of accepting measurements as being equal.                           
slope(x[],samples[],m);	   // slope of linear regression dsamples/dx
intercept(x[],samples[],m);// intercept of linear regression dsamples/dx
filternan(samples[],m);    // filter nan and inf values out of a 1-dimensional array (destructive void function)
f_round(samples[],m,p);    // overwrites samples[m] with values rounded to p decimals

To use the library, copy the download to the Library directory.
 
Technical notes:
-The bubble sort algorithm will re-order the input array.
-The library only currently works on float arrays.
