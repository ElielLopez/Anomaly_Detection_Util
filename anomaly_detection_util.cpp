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
//    cout<<sum<<endl;
//    cout<<"check"<<endl;

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
// a = COV(x,y) / VAR(x)
// b = avgY - a * avgX
Line linear_reg(Point** points, int size){

    float a = 0, b = 0;
    float covarianceXY = 0;
    float varianceX = 0;
    float avgY = 0;
    float avgX = 0;
    float x[size];
    float y[size];

    for (int j = 0; j < size; j++) {
        x[j] = points[j]->x;
        y[j] = points[j]->y;
    }

    for(int i = 0; i < size; i++) {
        avgY += points[i]->y;
        avgX += points[i]->x;
    }
    avgY = avgY / size;
    avgX = avgX / size;

    covarianceXY = cov(x, y, size);
    varianceX = var(x, size);

    a = covarianceXY / varianceX;
    b = avgY - a * avgX;

    return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    // p = (4, 10)
    // 10 = a * 4 + b
    // line = y = a * x + b
    float deviation = 0;

    deviation = dev(p, linear_reg(points, size));

    return deviation;
}

// returns the deviation between point p and the line
// line y = a*x+b
// 9 = a * 4 + b
float dev(Point p,Line l){
    // (p.x, p.y)=(4, 10)     (4, 9)
    float deviation = 0;
    float px = 0;
    float py = 0;
    float lineX = 0;
    float lineY = 0;
    float a = 0;
    float b = 0;

    px = p.x;
    py = p.y;
    a = l.a;
    b = l.b;
    lineY = a * px + b;
    // | f(x) - y |
    deviation = fabs(lineY - py);

    return deviation;
}