# QuickStats
Descriptive statistics for Arduino float arrays

I developed this library to help quickly accomplish median and mode filtering when collecting sensor data. Functions in this library operate on an array of float variables, of dimension "m", and return the corresponding statistic. This library was originally created for a data smoothing strategy for float variables. Using a median or mode filtering strategy (opposed to mean filtering) is better at removing spikes from aberrant readings. The other functions (stdev, CV, etc.) were included for fun.

I have found this library useful, and so I've added to it over time. For instance, I was annoyed with the occasional nan value I was receiving from thermocouple readings, so I added the filternan() function, which also removes inf values. I needed a derivative for a sliding average reading, so I added slope() and intercept() functions.

A bubble sort algorithm is also contained in this library which was necessary to calculate median and mode.

The functions available in the library include:

 average(samples[],m);      // the average of elements in samples[m]\
 g_average(samples[],m);    // the geometric mean of elements in samples[m]\
 minimum(samples[],m);      // the minimum value in samples[m]\
 maximum(samples[],m);      // the maximum value in samples[m]\
 stdev(samples[],m);        // the sample standard deviation of elements in samples[m]\
 stderror(samples[],m);     // the standard error of elements in samples[m]\
 CV(samples[],m);           // the coefficient of variation in samples[m] in percent\
 bubbleSort(samples[],m);   // sorting algorithm to arrange the elements in samples[m]\
 fabs(sample);              // absolute value of a float, used in mode()\
 median(samples[],m);       // the median of elements in samples[m]\
 mode(samples[],m,epsilon); // the mode of elements in samples[m] (returns 0 if no mode)\
 slope(x[],samples[],m);	   // slope of linear regression dsamples/dx\
 intercept(x[],samples[],m); // intercept of linear regression dsamples/dx\
 filternan(samples[],m);     // filter nan and inf values out of a 1-dimensional array (destructive void function)
 f_round(samples[],m,p);     // round samples[m] to p decimal places
 
