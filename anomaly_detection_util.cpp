/*
 * anomaly_detection_util.cpp
 *
 * Author: 309288777 Eliel Lopez
 */

#include <math.h>
#include "anomaly_detection_util.h"

using namespace std;

float avg(float* x, int size){

    float average;
    float sum = 0;

    for(int i = 0; i < size; i++) {
        sum += x[i];
    }

    average = sum / size;
    cout<<sum<<endl;

    return average;
}

// returns the variance of X and Y
float var(float* x, int size){

    float variance = 0;
    float average = 0;
    float powAverage = 0;
    float sumXPow = 0;
    float sumXPowAverage = 0;

    for(int i = 0; i < size; i++) {
        sumXPow += pow(x[i],2);
    }

    sumXPowAverage = sumXPow / size;
    average = avg(x, size);
    powAverage = pow(average, 2);
    variance = sumXPowAverage - powAverage;

    return variance;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){

    float covariance = 0;
    float xAvg = 0;
    float yAvg = 0;
    float xyAvg = 0;
    float xySum = 0;

    for(int i = 0; i < size; i++) {
        xySum += x[i] * y[i];
    }

    xAvg = avg(x, size);
    yAvg = avg(y, size);
    xyAvg = xySum / size;
    covariance = xyAvg - xAvg*yAvg;

    return covariance;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){

    float pearsonCoefficient = 0;
    float covariance = 0;
    float devX = 0;
    float devY = 0;

    covariance = cov(x, y, size);
    devX = sqrt(var(x, size));
    devY = sqrt(var(y, size));
    pearsonCoefficient = covariance / devX * devY;

    return pearsonCoefficient;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){

    return Line(0,0);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    return 0;
}