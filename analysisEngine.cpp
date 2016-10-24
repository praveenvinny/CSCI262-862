/*
 * File:   analysisEngine.cpp
 * Author: Praveen
 *
 * Created on 24 October 2016, 2:11 PM
 */
#include <cmath>
#include "analysisEngine.h"

using namespace std;

double AnalysisEngine::calculateSpeedMean(vector<float> array) {
    double value = 0.0;
    for(unsigned int i=0; i<array.size(); i++) {
        value = value + array.at(i);
    }

    value = value/array.size();
    return value;
}

double AnalysisEngine::calculateSpeedSD(vector<float> array, double mean) {
    double value = 0.0;
    for(unsigned int i=0; i<array.size(); i++) {
        value = value + ((mean-array.at(i))*(mean-array.at(i)));
    }
    value = sqrt(value/array.size());
    return value;
}

double AnalysisEngine::getMean() {
    return this->speedMean;
}

double AnalysisEngine::getSD() {
    return this->speedSD;
}

void AnalysisEngine::setMean(vector<float> array) {
    this->speedMean = calculateSpeedMean(array);
}

void AnalysisEngine::setSD(vector<float> array, double mean) {
    this->speedSD = calculateSpeedSD(array, mean);
}

