/* 
 * File:   analysisEngine.h
 * Author: Praveen
 *
 * Created on 24 October 2016, 2:11 PM
 */

#ifndef ANALYSISENGINE_H
#define	ANALYSISENGINE_H

#include <vector>

class AnalysisEngine {
private:
    double speedMean;
    double speedSD;
public:
    double calculateSpeedMean(vector<float> array, double mean);
    double calculateSpeedSD(vector<float> array, double mean);
};


#endif	/* ANALYSISENGINE_H */

