/*
 * File:   analysisEngine.h
 * Author: Praveen
 *
 * Created on 24 October 2016, 2:11 PM
 */

#ifndef ANALYSISENGINE_H
#define ANALYSISENGINE_H

#include <vector>

using namespace std;

class AnalysisEngine {
private:
    double speedMean;
    double speedSD;
public:
    double calculateSpeedMean(vector<float> arr);
    double calculateSpeedSD(vector<float>, double mean);
    // Add in functions for computing mean and std dev of number of cars
    void setMean(vector<float>);
    void setSD(vector<float>, double mean);
    double getMean();
    double getSD();
};


#endif  /* ANALYSISENGINE_H */

